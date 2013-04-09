#include <libterra/Plotmap.h>

#include <libterra/XMLDocument.h>
#include <libterra/TypeConv.h>

#include <cstring>

#define max(x, y) (x > y ? x : y)

namespace LibTerra
{
	tfPlotmap::tfPlotmap(float width, float height)
		: m_width(width), m_height(height),
		  m_nextBuildingId(0)
	{

	}
	tfPlotmap::tfPlotmap(std::string xml)
		: m_nextBuildingId(0)
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
		tfXMLNode buildings = root.Child("buildings");
		for (tfXMLNode building = buildings.FirstChild(); building.Valid(); building = building.NextSibling())
		{
			int id = Convert<const char*, int>(building.Attribute("id").Value());
			m_nextBuildingId = max(id, m_nextBuildingId);
			tfBuilding b;
			const char* type = building.Attribute("type").Value();
			if (!strcmp(type, "residential"))
			{
				b.type = tfBuilding::RESIDENTIAL;
			} else if (!strcmp(type, "commercial"))
			{
				b.type = tfBuilding::COMMERCIAL;
			} else if (!strcmp(type, "skyscraper"))
			{
				b.type = tfBuilding::SKYSCRAPER;
			}
			b.numFloors = Convert<const char*, int>(building.Attribute("numberOfFloors").Value());
			int i = 0; // We need to count them manually because for some reason the .Valid method causes pugi to segfault in its destructor?
			for (tfXMLNode basepoint = building.FirstChild(); i < 4; basepoint = basepoint.NextSibling(), i++)
			{
				int bpId = Convert<const char*, int>(basepoint.Attribute("id").Value());
				float absX = Convert<const char*, float>(basepoint.Attribute("absX").Value());
				float absY = Convert<const char*, float>(basepoint.Attribute("absY").Value());
				float absZ = Convert<const char*, float>(basepoint.Attribute("absZ").Value());
				b.basepoints[bpId] = glm::vec3(absX, absY, absZ);
			}
			m_buildings[id] = b;
		}
	}
	tfPlotmap::~tfPlotmap()
	{

	}

	void tfPlotmap::Export(std::string xml)
	{

	}

	void tfPlotmap::AddBuilding(tfBuilding::Type type, int numFloors, glm::vec3 basepoints[4])
	{
		tfBuilding b = {type, numFloors, {basepoints[0], basepoints[1], basepoints[2], basepoints[3]}};
		m_buildings[m_nextBuildingId++] = b;
	}

	int tfPlotmap::BuildingMaxId()
	{
		return m_nextBuildingId;
	}
	tfBuilding tfPlotmap::Building(int id)
	{
		return m_buildings[id];
	}
	std::map<int, tfBuilding> tfPlotmap::Buildings()
	{
		return m_buildings;
	}
}
