#ifndef _BUILDING_H_
#define _BUILDING_H_

#include <set>

#include "Entity.h"
#include "Enums.h"

namespace TD {
	
	class Building : public Entity {
	protected:
		buildingTypeEnum type;
		std::pair<double, double>* cords;
	public:
		virtual ~Building() = 0;

		inline buildingTypeEnum getType() const { return type; }
		inline std::pair<double, double> getCords() { return *cords; }
		Building();
		Building(std::pair<double, double>* c);

	};

	
}

#endif

