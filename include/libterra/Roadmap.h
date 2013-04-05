#ifndef _INCLUDE_LIBTERRA_ROADMAP_H_
#define _INCLUDE_LIBTERRA_ROADMAP_H_

#include <libterra/Vector.h>
#include <libterra/Exception.h>

#include <map>
#include <list>
#include <string>

namespace LibTerra {
	class tfRoadmap {
	public:
		tfRoadmap(float width, float height);
		tfRoadmap(std::string xml);
		virtual ~tfRoadmap();

		void Export(std::string xml);

		int AddNode(tfVec3f position);
		int AddNode(float x, float y, float z);
		void AddEdge(int nodeA, int nodeB);
		void RemoveNode(int nodeId);
		void RemoveEdge(int nodeA, int nodeB);

		tfVec3f Node(int nodeId);
		std::map<int, tfVec3f> Nodes();
		std::list<int> Edges(int nodeId);
		bool NodeExists(int nodeId);
		bool EdgeExists(int nodeA, int nodeB);
	private:
		std::map<int, tfVec3f> m_nodes;
		std::map<int, std::list<int> > m_edges;
		int m_nextNodeId;
		float m_width;
		float m_height;
	};
}

#endif /* _INCLUDE_LIBTERRA_ROADMAP_H_ */
