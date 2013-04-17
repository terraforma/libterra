#include <libterra/Roadmap.h>

#include <libterra/XMLDocument.h>
#include <libterra/TypeConv.h>

#include <cstring>

#define max(x, y) ((x) > (y) ? (x) : (y))

namespace LibTerra {
	tfRoadmap::tfRoadmap(float width, float height) 
		: m_nextNodeId(0), m_width(width), m_height(height)
	{

	}
	tfRoadmap::tfRoadmap(std::string xml)
		: m_nextNodeId(0)
	{
		tfXMLDocument doc;
		bool success = doc.Parse(xml.c_str());
		if (!success)
		{
			throw tfException("xml document invalid");
		}
		tfXMLNode root = doc.Root();
		m_width = Convert<const char*, float>(root.Child("width").ChildValue());
		m_height = Convert<const char*, float>(root.Child("height").ChildValue());
		tfXMLNode nodes = root.Child("nodes");
		for (tfXMLNode node = nodes.FirstChild(); node.Valid(); node = node.NextSibling()) {
			int id = Convert<const char*, int>(node.Attribute("id").Value());
			m_nextNodeId = max(id, m_nextNodeId);
			float absX = Convert<const char*, float>(node.Attribute("absX").Value());
			float absY = Convert<const char*, float>(node.Attribute("absY").Value());
			float absZ = Convert<const char*, float>(node.Attribute("absZ").Value());
			m_nodes[id] = MakeVec3f(absX, absY, absZ);
		}
		tfXMLNode edges = root.Child("relations");
		for (tfXMLNode edge = edges.FirstChild(); edge.Valid(); edge = edge.NextSibling()) {
			int nodeA = Convert<const char*, int>(edge.Attribute("nodeA").Value());
			int nodeB = Convert<const char*, int>(edge.Attribute("nodeB").Value());
			AddEdge(nodeA, nodeB);
		}
	}
	tfRoadmap::~tfRoadmap() 
	{
 
	}
	int tfRoadmap::NodeMaxId()
	{
		return m_nextNodeId;
	}
	void tfRoadmap::Export(std::string xml) 
	{
		tfXMLDocument doc;
		tfXMLNode root = doc.CreateRoot("roadmap");
		root.AppendAttribute("version").SetValue("0.1.0");
		root.AppendChild("width").SetValue(Convert<float, const char*>(m_width));
		root.AppendChild("height").SetValue(Convert<float, const char*>(m_height));
		tfXMLNode nodes = root.AppendChild("nodes");
		for (std::map<int, tfVec3f>::iterator it = m_nodes.begin(); it != m_nodes.end(); ++it) {
			tfVec3f nodePos = it->second;
			tfXMLNode node = nodes.AppendChild("node");
			node.AppendAttribute("id").SetValue(Convert<int, const char*>(it->first));
			node.AppendAttribute("absX").SetValue(Convert<float, const char*>(nodePos.x));
			node.AppendAttribute("absY").SetValue(Convert<float, const char*>(nodePos.y));
			node.AppendAttribute("absZ").SetValue(Convert<float, const char*>(nodePos.z));
		}
		tfXMLNode relations = root.AppendChild("relations");
		// Nodes visited is a bitmap of nodes we know all edges have been printed for
		bool *nodesVisited = new bool[m_nextNodeId]; /* !_HACK__ [Alex Melbourne] : We should probably think of a better way to do this. Avoiding dynamic allocation is nice. */
		memset(nodesVisited, 0, m_nextNodeId);
		for (std::map<int, std::list<int> >::iterator it = m_edges.begin(); it != m_edges.end(); ++it) {
			int nodeId = it->first;
			std::list<int> edges = it->second;
			for (std::list<int>::iterator edgeIt = edges.begin(); edgeIt != edges.end(); ++edgeIt) {
				if (!nodesVisited[*edgeIt]) {
					tfXMLNode edge = relations.AppendChild("relation");
					edge.AppendAttribute("nodeA").SetValue(Convert<int, const char*>(nodeId));
					edge.AppendAttribute("nodeB").SetValue(Convert<int, const char*>(*edgeIt));
				}
			}
			nodesVisited[nodeId] = true;
		}
		delete[] nodesVisited;
		if (!doc.Write(xml.c_str())) {
			throw tfException("unable to write document");
		}
	}

	int tfRoadmap::AddNode(tfVec3f position)
	{
		int id = m_nextNodeId++;
		m_nodes[id] = position;
		return id;
	}
	int tfRoadmap::AddNode(float x, float y, float z)
	{
		tfVec3f vec = {x, y, z};
		return AddNode(vec);
	}
	void tfRoadmap::AddEdge(int nodeA, int nodeB)
	{
		if (!NodeExists(nodeA) || !NodeExists(nodeB)) {
			throw tfException("node doesn't exist");
		}
		// Insert the edge into m_edges from both sides
		m_edges[nodeA].push_back(nodeB);
		m_edges[nodeB].push_back(nodeA);
	}
	void tfRoadmap::RemoveNode(int nodeId)
	{
		if (!NodeExists(nodeId)) {
			throw tfException("node doesn't exist");
		}
		for (std::list<int>::iterator it = m_edges[nodeId].begin(); it != m_edges[nodeId].end(); ++it) {
			RemoveEdge(nodeId, *it);
		}
		m_edges.erase(nodeId);
		m_nodes.erase(nodeId);
	}
	void tfRoadmap::RemoveEdge(int nodeA, int nodeB)
	{
		if (!NodeExists(nodeA) || !NodeExists(nodeB)) {
			throw tfException("node doesn't exist");
		}
		if (!EdgeExists(nodeA, nodeB)) {
			throw tfException("edge doesn't exist");
		}
		for (std::list<int>::iterator it = m_edges[nodeA].begin(); it != m_edges[nodeA].end(); ++it) {
			if (*it == nodeB) {
				m_edges[nodeA].erase(it);
				break;
			}
		}
		for (std::list<int>::iterator it = m_edges[nodeB].begin(); it != m_edges[nodeB].end(); ++it) {
			if (*it == nodeA) {
				m_edges[nodeB].erase(it);
				break;
			}
		}
	}

	tfVec3f tfRoadmap::Node(int nodeId)
	{
		if (!NodeExists(nodeId)) {
			throw tfException("node doesn't exist");
		}
		return m_nodes[nodeId];
	}

	std::map<int, tfVec3f> tfRoadmap::Nodes()
	{
		return m_nodes;
	}

	std::map<int, std::list<int> > tfRoadmap::Edges()
	{
		return m_edges;
	}

	std::list<int> tfRoadmap::Edges(int nodeId)
	{
		if (!NodeExists(nodeId)) {
			throw tfException("node doesn't exist");
		}
		return m_edges[nodeId];
	}
	bool tfRoadmap::NodeExists(int nodeId)
	{
		if (m_nodes.find(nodeId) != m_nodes.end()) {
			return true;
		}
		return false;
	}
	bool tfRoadmap::EdgeExists(int nodeA, int nodeB)
	{
		if (!NodeExists(nodeA) || !NodeExists(nodeB)) {
			throw tfException("node doesn't exist");
		}
		std::list<int> edges = Edges(nodeA);
		for (std::list<int>::iterator it = edges.begin(); it != edges.end(); ++it) {
			if (*it == nodeB) {
				return true;
			}
		}
		return false;
	}
}
