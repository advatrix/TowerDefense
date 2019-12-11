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
		Trap* t = new Trap(landscape->getCell(i, j)->cords(), e, landscape->getEnemyTable());
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
		std::experimental::filesystem::current_path("../saves");
		time_t rawtime;
		auto time = ctime(&rawtime);
		std::experimental::filesystem::create_directory(time);
		std::experimental::filesystem::current_path('/'+ time);


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
					break;
				}
				case cellTypeEnum::field: {
					Field* f = dynamic_cast<Field*>(c);
					Tower* t = f->getTower();
					int bId = 0;
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
				}
			}

		cellsFile << static_cast<unsigned>(cellsStructs.size());
		for (auto it = cellsStructs.begin(); it != cellsStructs.end(); it++) cellsFile << (*it);

		enemiesFile << static_cast<unsigned>(enemiesStructs.size());
		for (auto it = enemiesStructs.begin(); it != enemiesStructs.end(); it++) enemiesFile << (*it);

		towersFile << static_cast<unsigned>(towerStructs.size());
		for (auto it = towerStructs.begin(); it != towerStructs.end(); it++) towersFile << (*it);

		liresFile << static_cast<unsigned>(liresStructs.size());
		for (auto it = liresStructs.begin(); it != liresStructs.end(); it++) liresFile << (*it);

		effectsFile << static_cast<unsigned>(effectsStructs.size());
		for (auto it = effectsStructs.begin(); it != effectsStructs.end(); it++) effectsFile << (*it);

		trapsFile << static_cast<unsigned>(trapsStructs.size());
		for (auto it = trapsStructs.begin(); it != trapsStructs.end(); it++) trapsFile << (*it);

		schedulesFile << static_cast<unsigned>(schedulesStructs.size());
		for (auto it = schedulesStructs.begin(); it != schedulesStructs.end(); it++) {
			schedulesFile << static_cast<unsigned>((*it).size());
			for (auto jt = (*it).begin(); jt != (*it).end(); jt++) schedulesFile << (*jt);
		}

		featuresFile << static_cast<unsigned>(features.size());
		for (auto it = features.begin(); it != features.end(); it++) featuresFile << (*it);

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
		std::experimental::filesystem::current_path("../levels");
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

		unsigned int featuresCount;
		featuresFile >> featuresCount;
		for (unsigned int i = 0; i < featuresCount; i++) {
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
						Castle* c = new Castle(cords, tmpFileCastle.title, tmpFileCastle.curHp, tmpFileCastle.maxHp, tmpFileCastle.money);
						r->build(c);
						landscape->setCastle(c);
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
						break;
					}
					}
				}
				case cellTypeEnum::field: {
					Field* f = new Field(tmpFileCell.x, tmpFileCell.y);
					std::pair<double, double> cords(tmpFileCell.x, tmpFileCell.y);
					switch (tmpFileCell.building) {
					case buildingTypeEnum::tower: {
						towersFile >> tmpFileTower;
						Tower* t = new Tower(features[tmpFileTower.level], strategies[tmpFileTower.strategyType], 0, cords);
						f->build(t);
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
						break;
					}
					}
				}
				}
			}
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
						Castle* c = new Castle(cords, tmpFileCastle.title, tmpFileCastle.curHp, tmpFileCastle.maxHp, tmpFileCastle.money);
						r->build(c);
						landscape->setCastle(c);
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
						break;
					}
					}
				}
				case cellTypeEnum::field: {
					Field* f = new Field(tmpFileCell.x, tmpFileCell.y);
					std::pair<double, double> cords(tmpFileCell.x, tmpFileCell.y);
					switch (tmpFileCell.building) {
					case buildingTypeEnum::tower: {
						towersFile >> tmpFileTower;
						Tower* t = new Tower(features[tmpFileTower.level], strategies[tmpFileTower.strategyType], 0, cords);
						f->build(t);
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
						break;
					}
					}
				}
				}
			}
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


	}


}

	



