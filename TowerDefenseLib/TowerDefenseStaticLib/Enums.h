/**
\file
This file contains implementation of all enumerators used in game
*/
#ifndef _ENUMS_H_
#define _ENUMS_H_

namespace TD {
	/// Set of every possible building type
	enum buildingTypeEnum {
		none, ///< Type of the building is undefined
		tower, ///< Default tower
		magicTower, ///< Magic Tower
		trap, ///< Trap
		lire, ///< Lire
		castle ///< Castle
	};

	/// Set of every possible cell type
	enum cellTypeEnum {
		forest, ///< Basic cell type: nothing can be built there
		road, ///< Road: allbuilding except Towers can be built there. Enemies can be placed only there.
		field ///< Field: only Towers can be built there
	};
	
	/// Set of possible towers type
	enum towerTypeEnum { 
		default_, ///< Basic tower type
		magic ///< Magic Tower
	};

	/// Set of possible Strategy types towers can have
	enum strategyTypeEnum {
		nearToTower, ///< Chooses the nearest to the tower enemy to attack 
		nearToCastle, ///< Chooses the nearest to the castle enemy to attack
		strong, ///< Chooses the enemy with the most current hit points to attack
		weak, ///< Chooses the enemy tih the least current hit points to attack
		fast, ///< Chooses the enmy with the most curresnt speed to attack
		noStrategy ///< The strategy is undefined
	};

	/// Set of possible Effect types
	enum effectTypeEnum { 
		weakness, ///< Weakness
		slowdown, ///< Slowdown
		poison, ///< Poison
		noEffect ///< The effect type is undefined
	
	};
}

#endif
