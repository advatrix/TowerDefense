#ifndef _GAMR_MANAGER_H_
#define _GAME_MANAGER_H_

#include "..//TowerDefenseStaticLib/TowerDefenseLib.h"

using namespace TD;

namespace game {
	class GameManager {
		Landscape* landscape;
		ct::Table<Entity*>* entities;
		Castle* castle;
		unsigned int time;
		unsigned int level;
		unsigned int winTime;

	public:
		GameManager() : landscape(nullptr), entities(nullptr), time(0), level(0), winTime(0), castle(nullptr) {}
		// void init();
	};
}

#endif
