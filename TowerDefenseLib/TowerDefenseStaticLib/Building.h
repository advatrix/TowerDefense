#ifndef _BUILDING_H_
#define _BUILDING_H_

#include <set>

#include "Entity.h"
#include "Enums.h"

namespace TD {
	
	class Building : public Entity {
	protected:
		std::pair<double, double> cords;
	public:
		virtual ~Building() {}
		inline std::pair<double, double> getCords() { return cords; }
		Building() : cords() {}
		Building(std::pair<double, double> c);

		virtual buildingTypeEnum getType() const { return buildingTypeEnum::none; }

	};

	
}

#endif

