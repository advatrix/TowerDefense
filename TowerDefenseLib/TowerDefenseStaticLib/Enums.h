#ifndef _ENUMS_H_
#define _ENUMS_H_

namespace TD {
	enum buildingTypeEnum { none, tower, magicTower, trap, lire, castle };
	enum cellTypeEnum { forest, road, field };
	enum towerTypeEnum { default_, magic };
	enum strategyTypeEnum { nearToTower, nearToCastle, strong, weak, fast, noStrategy };
	enum effectTypeEnum { weakness, slowdown, poison, noEffect };
}

#endif
