#ifndef _PLOTMAP_H_
#define _PLOTMAP_H_

#include <libterra/Exception.h>

#include <string>
#include <map>
#include <glm/glm.hpp>

namespace LibTerra
{
	struct tfBuilding
	{
		enum Type
		{
			RESIDENTIAL,
			COMMERCIAL,
			SKYSCRAPER
		};
		Type type;
		int numFloors;
		glm::vec3 basepoints[4];
	};
	class tfPlotmap
	{
	public:
		tfPlotmap(float width, float height);
		tfPlotmap(std::string xml);
		virtual ~tfPlotmap();

		void Export(std::string xml);

		void AddBuilding(tfBuilding::Type type, int numFloors, glm::vec3 basepoints[4]);

		int BuildingMaxId();
		tfBuilding Building(int id);
		std::map<int, tfBuilding> Buildings();
	private:
		std::map<int, tfBuilding> m_buildings;
		int m_nextBuildingId;
		float m_width;
		float m_height;
	};
}

#endif /* _PLOTMAP_H_ */
