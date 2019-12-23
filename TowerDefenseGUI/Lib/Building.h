/**
\file
\brief Header for Building class
*/
#ifndef _BUILDING_H_
#define _BUILDING_H_

#include <set>

#include "Entity.h"
#include "Enums.h"

namespace TD {

	/**
	\brief Parent class for every building

	This class is abstract, adding ability to place Entity on a cell
	
	
	*/
	class Building : public Entity {
	protected:
		std::pair<double, double> cords;
	public:
		virtual ~Building() {}
		/**
		Returns cords of the building as pair of x and y
		\return cords of the building as std::pair
		*/
		inline std::pair<double, double> getCords() { return cords; }
		Building() : cords() {}
		Building(std::pair<double, double> c);

		/**
		Virtual function that returns type of the particular building.
		\return buildingTypeEnum element corresponding to the type of the building
		*/
		virtual buildingTypeEnum getType() const { return buildingTypeEnum::none; }

	};

	
}

#endif

