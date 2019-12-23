#pragma warning(disable:4996)


#include "pch.h"

#include <fstream>
#include <filesystem>
#include <experimental/filesystem>
#include <ctime>

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
		++internalTime;
	}

	void GameManager::upgrade(int i, int j) {

		Field* f = dynamic_cast<Field*>(landscape->getCell(i, j));
		if (!f) throw std::runtime_error("Tower is not built here");
		Tower* t = f->getTower();
		if (!t) throw std::runtime_error("Tower is not built here");
		unsigned int currLevel = t->getLevel();
		if (currLevel < features.size()) {
			if (features[currLevel]->getPrice() > landscape->getCastle()->getMoney())
				throw std::runtime_error("Not enough money");
			t->setFeature(features[currLevel]);
			landscape->getCastle()->decMoney(features[currLevel]->getPrice());
		}
		else throw std::runtime_error("Impossible to upgrade");
	}

	void GameManager::buildTower(int i, int j, unsigned int level) {
		Field* f = dynamic_cast<Field*>(landscape->getCell(i, j));
		if (!f) throw std::runtime_error("A tower can be built only on a Field cell");
		if (features[level - 1]->getPrice() > landscape->getCastle()->getMoney())
			throw std::runtime_error("Not enough money");
		Tower* t = new Tower(features[level - 1], strategies[strategyTypeEnum::nearToTower], 0,
			landscape->getCell(i, j)->cords());
		f->build(t);
		entities.push_back(t);
		landscape->getCastle()->decMoney(features[level - 1]->getPrice());
	}

	void GameManager::buildMagicTower(int i, int j, unsigned int lvl,
		effectTypeEnum effType, unsigned int value, unsigned int time) {
		if (landscape->getCell(i, j)->getType() != cellTypeEnum::field) throw std::runtime_error("invalid cell type");
		if (features[lvl - 1]->getPrice() + value * time > landscape->getCastle()->getMoney())
			throw std::runtime_error("Not enough money");
		Effect* e = nullptr;
		switch (effType) {
		case effectTypeEnum::noEffect:
			throw std::invalid_argument("attempt to build a magic tower without eny effect");
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
		landscape->getCastle()->decMoney(features[lvl]->getPrice() + value * time);
		entities.push_back(m);
	}

	void GameManager::buildTrap(int i, int j, effectTypeEnum effType, unsigned int value, unsigned int time) {
		if (landscape->getCell(i, j)->getType() != cellTypeEnum::road) throw std::runtime_error("invalid cell type");
		if (features[0]->getPrice() + value * time > landscape->getCastle()->getMoney())
			throw std::runtime_error("Not enough money");
		Effect* e = nullptr;
		switch (effType) {
		case effectTypeEnum::noEffect:
			throw std::invalid_argument("ettempt to build a trap without eny effect");
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
		Trap* t = new Trap(landscape->getCell(i, j)->cords(), e, landscape->getEnemyTable());
		Road* r = dynamic_cast<Road*>(landscape->getCell(i, j));
		r->build(t);
		landscape->getCastle()->decMoney(features[0]->getPrice() + value * time);
		entities.push_back(t);
	}

	void GameManager::destroy(int i, int j) {
		Cell* c = landscape->getCell(i, j);
		size_t lvl = 0;
		if (c->getType() == cellTypeEnum::field) {
			Field* f = dynamic_cast<Field*>(c);
			if (f->isBuilt()) lvl = f->getTower()->getLevel();

		}
		c->destroy();
		landscape->getCastle()->incMoney(ceil(features[lvl]->getPrice() * 0.8));
		switch (c->getType()) {
		case cellTypeEnum::field: {
			Tower* t = dynamic_cast<Field*>(c)->getTower();
			entities.erase(std::remove(entities.begin(), entities.end(), t), entities.end());
			break;
		}
		case cellTypeEnum::road: {
			Trap* t = dynamic_cast<Trap*>(dynamic_cast<Road*>(c)->getBuilding());
			if (!t) throw std::runtime_error("Impossible to destroy this building");
			entities.erase(std::remove(entities.begin(), entities.end(), t), entities.end());
			break;
		}
		}
	}

	GameManager::~GameManager() {
		for (auto it = features.begin(); it != features.end(); it++) delete (*it);
		for (auto it = strategies.begin(); it != strategies.end(); it++) delete (*it);
	}

	void GameManager::save() {
		// std::cout << std::experimental::filesystem::current_path();
		// std::experimental::filesystem::current_path("../");
		std::experimental::filesystem::current_path("../saves");
		time_t t;
		t = time(0);
		std::string timename = std::to_string(t);

		std::experimental::filesystem::create_directory(timename);
		std::experimental::filesystem::current_path(timename);


		std::fstream cellsFile("cells.bin", std::ios::binary | std::ios::out | std::ios::trunc),
			enemiesFile("enemies.bin", std::ios::binary | std::ios::out | std::ios::trunc),
			towersFile("towers.bin", std::ios::binary | std::ios::out | std::ios::trunc),
			liresFile("lires.bin", std::ios::binary | std::ios::out | std::ios::trunc),
			effectsFile("effects.bin", std::ios::binary | std::ios::out | std::ios::trunc),
			trapsFile("traps.bin", std::ios::binary | std::ios::out | std::ios::trunc),
			schedulesFile("schedules.bin", std::ios::binary | std::ios::out | std::ios::trunc),
			featuresFile("features.bin", std::ios::binary | std::ios::out | std::ios::trunc);

		std::vector<FileCell> cellsStructs;
		std::vector<FileEnemy> enemiesStructs;
		std::vector<FileTower> towerStructs;
		std::vector<FileLire> liresStructs;
		std::vector<FileEffect> effectsStructs;
		std::vector<FileTrap> trapsStructs;
		std::vector<std::vector<FileScheduleItem>> schedulesStructs;
		std::vector<FileFeature> featuresStructs;

		unsigned int height = landscape->getHeight(), width = landscape->getWidth();

		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++) {
				Cell* c = landscape->getCell(i, j);
				switch (c->getType()) {
				case cellTypeEnum::forest:
					cellsStructs.push_back(FileCell(floor(c->cords().first), floor(c->cords().second), cellTypeEnum::forest, 0, 0));
					break;
				case cellTypeEnum::road: {
					Road* r = dynamic_cast<Road*>(c);
					Building* b = r->getBuilding();
					int bId = 0;
					if (b) {
						switch (b->getType()) {
						case buildingTypeEnum::lire: {
							bId = liresStructs.size();
							Lire* l = dynamic_cast<Lire*>(b);
							liresStructs.push_back(FileLire(floor(b->getCords().first), floor(b->getCords().second), l->getSchedule().size()));
							cellsStructs.push_back(FileCell(i, j, cellTypeEnum::road, buildingTypeEnum::lire, liresStructs.size() - 1));
							std::vector<FileScheduleItem> tmpSchVector;
							for (auto it = l->schedule.begin(); it != l->schedule.end(); it++)
								tmpSchVector.push_back(FileScheduleItem((*it).first, (*it).second->getTitle(), (*it).second->getCurHp(),
								(*it).second->getCurSpeed(), (*it).second->getMoney()));
							schedulesStructs.push_back(tmpSchVector);
							break;
						}
						case buildingTypeEnum::trap: {
							bId = trapsStructs.size();
							Trap* t = dynamic_cast<Trap*>(b);
							trapsStructs.push_back(FileTrap(floor(b->getCords().first), floor(b->getCords().second), effectsStructs.size()));
							Effect* e = t->getEffect();
							effectsStructs.push_back(FileEffect(e->getType(), e->getValue(), e->getRemainedTime()));
							cellsStructs.push_back(FileCell(i, j, cellTypeEnum::road, buildingTypeEnum::trap, trapsStructs.size() - 1));
							break;
						}
						default: {
							bId = 0;
							cellsStructs.push_back(FileCell(i, j, cellTypeEnum::road, buildingTypeEnum::castle, 0));
							Castle* c = dynamic_cast<Castle*>(r->getBuilding());
							FileCastle castle_(i, j, c->getMoney(), c->getTitle(), c->getMaxHp(), c->getCurHp());
							std::fstream castleFile("castle.bin", std::ios::binary | std::ios::out | std::ios::trunc);
							castleFile << castle_;
							castleFile.close();
							break;
						}
						}
					}
					else {
						cellsStructs.push_back(FileCell(i, j, cellTypeEnum::road, 0, 0));
					}
					break;
				}
				case cellTypeEnum::field: {
					Field* f = dynamic_cast<Field*>(c);
					Tower* t = f->getTower();
					int bId = 0;
					if (t) {
						switch (t->getType()) {
						case buildingTypeEnum::magicTower: {
							MagicTower* m = dynamic_cast<MagicTower*>(t);
							Effect* e = m->getEffect();
							effectsStructs.push_back(FileEffect(e->getType(), e->getValue(), e->getRemainedTime()));
							towerStructs.push_back(FileTower(i, j, towerTypeEnum::magic, effectsStructs.size() - 1, t->getLevel(), t->getStrategyType()));
							cellsStructs.push_back(FileCell(i, j, cellTypeEnum::field, buildingTypeEnum::magicTower, towerStructs.size()));
							break;
						}
						case buildingTypeEnum::tower: {
							towerStructs.push_back(FileTower(i, j, buildingTypeEnum::tower, 0, t->getLevel(), t->getStrategyType()));
							cellsStructs.push_back(FileCell(i, j, cellTypeEnum::field, buildingTypeEnum::tower, towerStructs.size()));
							break;
						}
						}
					}
					else {
						cellsStructs.push_back(FileCell(i, j, cellTypeEnum::field, 0, 0));
					}
				}
				}
			}

		cellsFile << height << std::endl << width << std::endl;
		for (auto it = cellsStructs.begin(); it != cellsStructs.end(); it++) cellsFile << (*it);

		enemiesFile << static_cast<unsigned>(enemiesStructs.size()) << std::endl;
		for (auto it = enemiesStructs.begin(); it != enemiesStructs.end(); it++) enemiesFile << (*it);

		towersFile << static_cast<unsigned>(towerStructs.size()) << std::endl;
		for (auto it = towerStructs.begin(); it != towerStructs.end(); it++) towersFile << (*it);

		liresFile << static_cast<unsigned>(liresStructs.size()) << std::endl;
		for (auto it = liresStructs.begin(); it != liresStructs.end(); it++) liresFile << (*it);

		effectsFile << static_cast<unsigned>(effectsStructs.size()) << std::endl;
		for (auto it = effectsStructs.begin(); it != effectsStructs.end(); it++) effectsFile << (*it);

		trapsFile << static_cast<unsigned>(trapsStructs.size()) << std::endl;
		for (auto it = trapsStructs.begin(); it != trapsStructs.end(); it++) trapsFile << (*it);

		schedulesFile << static_cast<unsigned>(schedulesStructs.size()) << std::endl;
		for (auto it = schedulesStructs.begin(); it != schedulesStructs.end(); it++) {
			schedulesFile << static_cast<unsigned>((*it).size()) << std::endl;
			for (auto jt = (*it).begin(); jt != (*it).end(); jt++) schedulesFile << (*jt);
		}


		featuresFile << static_cast<unsigned>(features.size()) << std::endl;
		for (auto it = features.begin(); it != features.end(); it++) {
			FileFeature f((*it)->getLevel(), (*it)->getPrice(), (*it)->getDamage(), (*it)->getRadius(), (*it)->getShotSpeed());
			featuresFile << f;
		}

		cellsFile.close();
		enemiesFile.close();
		towersFile.close();
		liresFile.close();
		effectsFile.close();
		trapsFile.close();
		schedulesFile.close();
		featuresFile.close();
	}

	void GameManager::load(std::string filename) {
		std::experimental::filesystem::current_path("../saves");
		std::experimental::filesystem::current_path(filename);

		std::fstream cellsFile("cells.bin", std::ios::binary | std::ios::in),
			enemiesFile("enemies.bin", std::ios::binary | std::ios::in),
			towersFile("towers.bin", std::ios::binary | std::ios::in),
			liresFile("lires.bin", std::ios::binary | std::ios::in),
			effectsFile("effects.bin", std::ios::binary | std::ios::in),
			trapsFile("traps.bin", std::ios::binary | std::ios::in),
			schedulesFile("schedules.bin", std::ios::binary | std::ios::in),
			castleFile("castle.bin", std::ios::binary | std::ios::in),
			featuresFile("features.bin", std::ios::binary | std::ios::in);

		std::vector<std::vector<Cell*>> cells;

		/*
		std::vector<std::vector<FileCell>> fileCells;
		FileCastle fileCastle;
		std::vector<FileEffect> fileEffects;
		std::vector<FileEnemy> fileEnemies;
		std::vector<FileFeature> fileFeatures;
		std::vector<FileLire> fileLires;
		std::vector<std::vector<FileScheduleItem>> fileSchedules;
		std::vector<FileTower> fileTowers;
		std::vector<FileTrap> fileTraps;
		*/

		FileCell tmpFileCell;
		FileEffect tmpFileEffect;
		FileEnemy tmpFileEnemy;
		FileFeature tmpFileFeature;
		FileLire tmpFileLire;
		FileScheduleItem tmpFileSchedule;
		FileTower tmpFileTower;
		FileTrap tmpFileTrap;
		FileCastle tmpFileCastle;

		// landscape = new Landscape();
		Castle* c = nullptr;

		size_t liresCount;
		liresFile >> liresCount;

		size_t featuresCount;
		featuresFile >> featuresCount;
		for (unsigned i = 0; i < featuresCount; i++) {
			featuresFile >> tmpFileFeature;
			Feature* f = new Feature(tmpFileFeature.price, tmpFileFeature.radius, tmpFileFeature.damage,
				tmpFileFeature.shotSpeed, tmpFileFeature.level);
			features.push_back(f);
		}

		unsigned height, width;
		ct::Table<Enemy*>* enemyTable = new ct::Table<Enemy*>();
		cellsFile >> height >> width;
		for (unsigned i = 0; i < height; i++) {
			std::vector<Cell*> row;
			for (unsigned j = 0; j < width; j++) {
				cellsFile >> tmpFileCell;
				switch (tmpFileCell.type) {
				case cellTypeEnum::forest: {
					row.push_back(new Cell(tmpFileCell.x, tmpFileCell.y));
					break;
				}
				case cellTypeEnum::road: {
					Road* r = new Road(tmpFileCell.x, tmpFileCell.y);
					std::pair<double, double> cords(tmpFileCell.x, tmpFileCell.y);
					switch (tmpFileCell.building) {
					case buildingTypeEnum::castle: {
						castleFile >> tmpFileCastle;
						c = new Castle(cords, tmpFileCastle.title, tmpFileCastle.curHp, tmpFileCastle.maxHp, tmpFileCastle.money);
						r->build(c);
						entities.push_back(c);
						// landscape->setCastle(c);
						break;
					}
					case buildingTypeEnum::lire: {
						liresFile >> tmpFileLire;
						std::multimap<unsigned, Enemy*>* enemySchedule = new std::multimap<unsigned, Enemy*>();
						for (int i = 0; i < tmpFileLire.enemiesCount; i++) {
							schedulesFile >> tmpFileSchedule;
							Enemy* e = new Enemy(tmpFileLire.x, tmpFileLire.y, tmpFileSchedule.maxHp,
								tmpFileSchedule.speed, tmpFileSchedule.money, tmpFileSchedule.name, tmpFileSchedule.maxHp,
								tmpFileSchedule.speed);
							enemySchedule->insert(std::make_pair(tmpFileSchedule.time, e));
						}
						Lire* l = new Lire(cords, *enemySchedule, 0, enemyTable);
						r->build(l);
						entities.push_back(l);
						break;
					}
					case buildingTypeEnum::trap: {
						trapsFile >> tmpFileTrap;
						effectsFile >> tmpFileEffect;
						Effect* eff = nullptr;
						switch (tmpFileEffect.type) {
						case effectTypeEnum::poison:
							eff = new Poison(nullptr, tmpFileEffect.time, tmpFileEffect.value);
							break;
						case effectTypeEnum::slowdown:
							eff = new Slowdown(nullptr, tmpFileEffect.time, tmpFileEffect.value);
							break;
						case effectTypeEnum::weakness: {
							eff = new Weakness(nullptr, tmpFileEffect.time, tmpFileEffect.value);
							break;
						}
						}
						Trap* t = new Trap(cords, eff, enemyTable);
						r->build(t);
						entities.push_back(t);
						break;
					}
					}
					row.push_back(r);
					break;
				}
				case cellTypeEnum::field: {
					Field* f = new Field(tmpFileCell.x, tmpFileCell.y);
					std::pair<double, double> cords(tmpFileCell.x, tmpFileCell.y);
					switch (tmpFileCell.building) {
					case buildingTypeEnum::tower: {
						towersFile >> tmpFileTower;
						Tower* t = new Tower(features[tmpFileTower.level], strategies[tmpFileTower.strategyType], 0, cords);
						f->build(t);
						entities.push_back(t);
						break;
					}
					case buildingTypeEnum::magicTower: {
						towersFile >> tmpFileTower;
						effectsFile >> tmpFileEffect;
						Effect* eff = nullptr;
						switch (tmpFileEffect.type) {
						case effectTypeEnum::poison:
							eff = new Poison(nullptr, tmpFileEffect.time, tmpFileEffect.value);
							break;
						case effectTypeEnum::slowdown:
							eff = new Slowdown(nullptr, tmpFileEffect.time, tmpFileEffect.value);
							break;
						case effectTypeEnum::weakness: {
							eff = new Weakness(nullptr, tmpFileEffect.time, tmpFileEffect.value);
							break;
						}
						}
						MagicTower* m = new MagicTower(features[tmpFileTower.level], strategies[tmpFileTower.strategyType],
							0, cords, eff);
						f->build(m);
						entities.push_back(m);
						break;
					}
					}
					row.push_back(f);
				}
				}
			}
			cells.push_back(row);
		}

		cellsFile.close();
		enemiesFile.close();
		towersFile.close();
		liresFile.close();
		effectsFile.close();
		trapsFile.close();
		schedulesFile.close();
		castleFile.close();
		featuresFile.close();

		landscape = new Landscape(cells, enemyTable);
		landscape->setCastle(c);
		if (!landscape->createPath()) throw std::exception("Bad level");


		strategies.push_back(new NearToTower(enemyTable));
		strategies.push_back(new NearToCastle(enemyTable, c->getCords()));
		strategies.push_back(new Strong(enemyTable));
		strategies.push_back(new Weak(enemyTable));
		strategies.push_back(new Fast(enemyTable));

		std::experimental::filesystem::current_path("../");

	}

	void GameManager::load(unsigned int level) {
		std::string levelName = std::to_string(level);
		std::experimental::filesystem::current_path("../levels");
		std::experimental::filesystem::current_path(levelName);
		this->level = level;

		std::fstream cellsFile("cells.bin", std::ios::binary | std::ios::in),
			enemiesFile("enemies.bin", std::ios::binary | std::ios::in),
			towersFile("towers.bin", std::ios::binary | std::ios::in),
			liresFile("lires.bin", std::ios::binary | std::ios::in),
			effectsFile("effects.bin", std::ios::binary | std::ios::in),
			trapsFile("traps.bin", std::ios::binary | std::ios::in),
			schedulesFile("schedules.bin", std::ios::binary | std::ios::in),
			castleFile("castle.bin", std::ios::binary | std::ios::in),
			featuresFile("features.bin", std::ios::binary | std::ios::in);

		std::vector<std::vector<Cell*>> cells;

		/*
		std::vector<std::vector<FileCell>> fileCells;
		FileCastle fileCastle;
		std::vector<FileEffect> fileEffects;
		std::vector<FileEnemy> fileEnemies;
		std::vector<FileFeature> fileFeatures;
		std::vector<FileLire> fileLires;
		std::vector<std::vector<FileScheduleItem>> fileSchedules;
		std::vector<FileTower> fileTowers;
		std::vector<FileTrap> fileTraps;
		*/

		FileCell tmpFileCell;
		FileEffect tmpFileEffect;
		FileEnemy tmpFileEnemy;
		FileFeature tmpFileFeature;
		FileLire tmpFileLire;
		FileScheduleItem tmpFileSchedule;
		FileTower tmpFileTower;
		FileTrap tmpFileTrap;
		FileCastle tmpFileCastle;

		// landscape = new Landscape();
		Castle* c = nullptr;

		size_t liresCount;
		liresFile >> liresCount;

		size_t schedulesCount;
		schedulesFile >> schedulesCount;

		size_t featuresCount;
		featuresFile >> featuresCount;
		for (unsigned i = 0; i < featuresCount; i++) {
			featuresFile >> tmpFileFeature;
			Feature* f = new Feature(tmpFileFeature.price, tmpFileFeature.radius, tmpFileFeature.damage,
				tmpFileFeature.shotSpeed, tmpFileFeature.level);
			features.push_back(f);
		}

		unsigned height, width;
		ct::Table<Enemy*>* enemyTable = new ct::Table<Enemy*>();
		cellsFile >> height >> width;
		for (unsigned i = 0; i < height; i++) {
			std::vector<Cell*> row;
			for (unsigned j = 0; j < width; j++) {
				cellsFile >> tmpFileCell;
				switch (tmpFileCell.type) {
				case cellTypeEnum::forest: {
					row.push_back(new Cell(tmpFileCell.x, tmpFileCell.y));
					break;
				}
				case cellTypeEnum::road: {
					Road* r = new Road(tmpFileCell.x, tmpFileCell.y);
					std::pair<double, double> cords(tmpFileCell.x, tmpFileCell.y);
					switch (tmpFileCell.building) {
					case buildingTypeEnum::castle: {
						castleFile >> tmpFileCastle;
						c = new Castle(cords, tmpFileCastle.title, tmpFileCastle.curHp, tmpFileCastle.maxHp, tmpFileCastle.money);
						r->build(c);
						entities.push_back(c);
						// landscape->setCastle(c);
						break;
					}
					case buildingTypeEnum::lire: {
						liresFile >> tmpFileLire;
						std::multimap<unsigned, Enemy*>* enemySchedule = new std::multimap<unsigned, Enemy*>();
						size_t ec;
						schedulesFile >> ec;
						for (int i = 0; i < tmpFileLire.enemiesCount; i++) {
							schedulesFile >> tmpFileSchedule;
							Enemy* e = new Enemy(tmpFileLire.x, tmpFileLire.y, tmpFileSchedule.maxHp,
								tmpFileSchedule.speed, tmpFileSchedule.money, tmpFileSchedule.name, tmpFileSchedule.maxHp,
								tmpFileSchedule.speed);
							enemySchedule->insert(std::make_pair(tmpFileSchedule.time, e));
						}
						Lire* l = new Lire(cords, *enemySchedule, 0, enemyTable);
						r->build(l);
						entities.push_back(l);
						break;
					}
					case buildingTypeEnum::trap: {
						trapsFile >> tmpFileTrap;
						effectsFile >> tmpFileEffect;
						Effect* eff = nullptr;
						switch (tmpFileEffect.type) {
						case effectTypeEnum::poison:
							eff = new Poison(nullptr, tmpFileEffect.time, tmpFileEffect.value);
							break;
						case effectTypeEnum::slowdown:
							eff = new Slowdown(nullptr, tmpFileEffect.time, tmpFileEffect.value);
							break;
						case effectTypeEnum::weakness: {
							eff = new Weakness(nullptr, tmpFileEffect.time, tmpFileEffect.value);
							break;
						}
						}
						Trap* t = new Trap(cords, eff, enemyTable);
						r->build(t);
						entities.push_back(t);
						break;
					}
					}
					row.push_back(r);
					break;
				}
				case cellTypeEnum::field: {
					Field* f = new Field(tmpFileCell.x, tmpFileCell.y);
					std::pair<double, double> cords(tmpFileCell.x, tmpFileCell.y);
					switch (tmpFileCell.building) {
					case buildingTypeEnum::tower: {
						towersFile >> tmpFileTower;
						Tower* t = new Tower(features[tmpFileTower.level], strategies[tmpFileTower.strategyType], 0, cords);
						f->build(t);
						entities.push_back(t);
						break;
					}
					case buildingTypeEnum::magicTower: {
						towersFile >> tmpFileTower;
						effectsFile >> tmpFileEffect;
						Effect* eff = nullptr;
						switch (tmpFileEffect.type) {
						case effectTypeEnum::poison:
							eff = new Poison(nullptr, tmpFileEffect.time, tmpFileEffect.value);
							break;
						case effectTypeEnum::slowdown:
							eff = new Slowdown(nullptr, tmpFileEffect.time, tmpFileEffect.value);
							break;
						case effectTypeEnum::weakness: {
							eff = new Weakness(nullptr, tmpFileEffect.time, tmpFileEffect.value);
							break;
						}
						}
						MagicTower* m = new MagicTower(features[tmpFileTower.level], strategies[tmpFileTower.strategyType],
							0, cords, eff);
						f->build(m);
						entities.push_back(m);
						break;
					}
					}
					row.push_back(f);
				}
				}
			}
			cells.push_back(row);
		}

		cellsFile.close();
		enemiesFile.close();
		towersFile.close();
		liresFile.close();
		effectsFile.close();
		trapsFile.close();
		schedulesFile.close();
		castleFile.close();
		featuresFile.close();

		landscape = new Landscape(cells, enemyTable);
		landscape->setCastle(c);
		if (!landscape->createPath()) throw std::exception("Bad level");

		strategies.push_back(new NearToTower(enemyTable));
		strategies.push_back(new NearToCastle(enemyTable, c->getCords()));
		strategies.push_back(new Strong(enemyTable));
		strategies.push_back(new Weak(enemyTable));
		strategies.push_back(new Fast(enemyTable));

		std::experimental::filesystem::current_path("../");
	}

	void GameManager::setStrategy(int i, int j, strategyTypeEnum s) {
		Road* r = dynamic_cast<Road*>(landscape->getCell(i, j));
		if (!r) throw std::runtime_error("Wrong cell");
		Tower* t = dynamic_cast<Tower*>(r->getBuilding());
		if (!t) throw std::runtime_error("Strategy changing cannot be applied");
		t->setStrategy(strategies[s]);
	}


}

	



