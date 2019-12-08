#include "pch.h"
#include "GameManager.h"
#include "MagicTower.h"

namespace TD {
	void GameManager::update() {
		for (auto it = entities.begin(); it != entities.end(); it++)
			(*it)->update();
		landscape->update();
	}
	
	void GameManager::upgrade(int i, int j) {
		Field* f = dynamic_cast<Field*>(landscape->getCell(i, j));
		Tower* t = f->getTower();
		unsigned int currLevel = t->getLevel();
		if (currLevel < features.size()) {
			t->setFeature(features[currLevel]);
			landscape->getCastle()->decMoney(features[currLevel]->getPrice());
		}
	}

	void GameManager::buildTower(int i, int j, unsigned int level) {
		Tower* t = new Tower(features[level - 1], strategies[strategyTypeEnum::nearToTower], 0,
			landscape->getCell(i, j)->cords());
		Field* f = dynamic_cast<Field*>(landscape->getCell(i, j));
		f->build(t);
	}

	void GameManager::buildMagicTower(int i, int j, unsigned int lvl,
		effectTypeEnum effType, unsigned int value, unsigned int time) {
		Effect* e = nullptr;
		switch (effType) {
		case effectTypeEnum::noEffect:
			throw std::invalid_argument("ettempt to build a magic tower without eny effect");
			break;
		case effectTypeEnum::poison:
			e = new Poison(nullptr, time, value);
			break;
		case effectTypeEnum::slowdown:
			e = new Slowdown(nullptr, time, value);
			break;
		case effectTypeEnum::weakness:
			e = new Weakness(nullptr, time, value);
			break;
		}
		MagicTower* m = new MagicTower(features[lvl - 1], strategies[strategyTypeEnum::nearToTower], 0,
			landscape->getCell(i, j)->cords(), e);

	}


}
