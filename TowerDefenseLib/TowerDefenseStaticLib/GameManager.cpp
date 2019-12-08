#include "pch.h"

#include <fstream>

#include "GameManager.h"
#include "MagicTower.h"
#include "Trap.h"
#include "FileStructs.h"
#include "Lire.h"

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
		if (landscape->getCell(i, j)->getType() != cellTypeEnum::field) throw std::runtime_error("invalid cell type");
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
		Field* f = dynamic_cast<Field*>(landscape->getCell(i, j));
		f->build(m);
	}

	void GameManager::buildTrap(int i, int j, effectTypeEnum effType, unsigned int value, unsigned int time) {
		if (landscape->getCell(i, j)->getType() != cellTypeEnum::road) throw std::runtime_error("invalid cell type");
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
		Trap* t = new Trap(landscape->getCell(i, j)->cords(), e, landscape->getEnemyTable);
		Road* r = dynamic_cast<Road*>(landscape->getCell(i, j));
		r->build(t);

	}

	void GameManager::destroy(int i, int j) {
		landscape->getCell(i, j)->destroy();
	}

	GameManager::~GameManager() {
		for (auto it = features.begin(); it != features.end(); it++) delete (*it);
		for (auto it = strategies.begin(); it != strategies.end(); it++) delete (*it);
	}

	void GameManager::save() {
		std::ifstream cellsFile("cells.bin", std::ios::binary),
			enemiesFile("enemies.bin", std::ios::binary),
			towersFile("towers.bin", std::ios::binary),
			liresFile("lires.bin", std::ios::binary),
			effectsFile("effects.bin", std::ios::binary),
			trapsFile("traps.bin", std::ios::binary),
			schedulesFile("schedules.bin", std::ios::binary);

		std::vector<FileCell> cellsStructs;
		std::vector<FileEnemy> enemiesStructs;
		std::vector<FileTower> towerStructs;
		std::vector<FileLire> liresStructs;
		std::vector<FileEffect> effectsStructs;
		std::vector<FileTrap> trapsStructs;
		std::vector<std::vector<FileScheduleItem>> schedules;

		unsigned int height = landscape->getHeight(), width = landscape->getWidth();


		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++) {
				Cell* c = landscape->getCell(i, j);
				switch (c->getType()) {
				case cellTypeEnum::forest:
					cellsStructs.push_back(FileCell(floor(c->cords().first), floor(c->cords().second), cellTypeEnum::forest, 0, 0));
					break;
				case cellTypeEnum::road:
					Road* r = dynamic_cast<Road*>(c);
					Building* b = nullptr;
					int bId = 0;
					switch (b->getType()) {
					case buildingTypeEnum::lire:
						bId = liresStructs.size();
						Lire* l = dynamic_cast<Lire*>(b);
						liresStructs.push_back(FileLire(floor(b->getCords().first), floor(b->getCords().second), )
						break;
					case buildingTypeEnum::trap:
						bId = trapsStructs.size();
						break;
					default:
						bId = 0;
						break;
					}
					if (b = r->getBuilding()) cellsStructs.push_back(FileCell(floor(r->cords().first), floor(r->cords().second), cellTypeEnum::road,
						b->getType(), bId));

				}
			}

	}


}
