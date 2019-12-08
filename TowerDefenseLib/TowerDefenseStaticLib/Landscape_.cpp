#include "pch.h"



#include <iostream>
#include <fstream>
#include <limits>
#include <queue>


#include "Landscape.h"
/*#include "Enemy.h"
#include "Building.h"
#include "Tower.h"

*/
// using namespace nlohmann;

namespace TD {
	/*
	Landscape::Landscape() {
		playingField = nullptr;
		width = 0;
		height = 0;
		nLires = 0;
		enemyTable = EnemyTable();
		castle = nullptr;
	}

	Landscape::Landscape(int level) {
		if (level < 1) throw std::invalid_argument("invalid level number");
		// open file <level>.json here
		// load
		json jLevel;
		std::string filename = std::to_string(level) + ".json";
		std::ifstream f(filename);
		f.open(filename);
		if (!f) throw std::runtime_error("file opening failure");
		else f >> jLevel;
		std::cout << jLevel;
		height = jLevel["height"];
		//...
		width = jLevel["width"];

		NearToTower* neartotower_ = new NearToTower;
		NearToCastle* neartocastle_ = new NearToCastle;
		Strong* strong_ = new Strong;
		Weak* weak_ = new Weak;
		Fast* fast_ = new Fast;
		strategies.push_back(neartotower_);
		strategies.push_back(neartocastle_);
		strategies.push_back(strong_);
		strategies.push_back(weak_);
		strategies.push_back(fast_);

		playingField = new Cell * [height];
		for (int i = 0; i < height; i++) playingField[i] = new Cell[width];
		for (int i = 0; i < height; i++) {
			std::string strI = std::to_string(i);
			for (int j = 0; j < width; j++) {
				std::string strJ = std::to_string(j);
				std::string currCellType = jLevel[strI][strJ].value("type", "forest");
				if (currCellType == "forest")
					playingField[i][j] = new Cell(i, j);
				else if (currCellType == "field") {
					delete playingField[i][j];
					playingField[i][j] = new Field(i, j);
					std::string currBuilding = jLevel[strI][strJ].value("building", "none");
					if (currBuilding == "tower") {
						json tmp = jLevel[strI][strJ]["tower"];
						int strategyType = tmp.value("strategy", 0);
						int featureType = tmp.value("feature", 0);
						unsigned int towerLevel = tmp["tower"].value("level", 1);
						unsigned int lastShot = jLevel[strI][strJ]["tower"].value("lastShot", 0);
						int featurePrice = jLevel[strI][strJ]["tower"].value("price", 100);
						double radius = jLevel[strI][strJ]["tower"].value("radius", 0);
						double damage = jLevel[strI][strJ]["tower"].value("damage", 0);
						double shotSpeed = jLevel[strI][strJ]["tower"].value("shotSpeed", 0);

						Feature* tmpFeature = new Feature(featurePrice, radius, damage, shotSpeed);
						DefaultTower* tmpTower = new DefaultTower(tmpFeature, strategies[strategyType]);
						Building* tmpBuilding = dynamic_cast<Building*>(tmpTower);

						playingField[i][j]->build(tmpBuilding);
					}
					else if (currBuilding == "castle") {
						json tmp = jLevel[strI][strJ]["castle"];

					}
				}
			}
		}
	}
	*/


	void Landscape::loadLevel(int level) {
		/*
		загрузка карты из файла, соответствующего уровню
		для определения имени файла должно использоваться соответствие уровень - имя файла,
		которое также в свою очередь загружается из файла с константным именем
		там же определено, сколько уровней есть всего, чтобы кидать исключение в плохом случае
		так же есть файлы конфигурации фич башен, аналогично для каждого уровня


		можно сделать через json
		*/



	}

	Landscape::Landscape() {
		width = 0;
		height = 0;
		nLires = 0;
		castle = nullptr;
		strategies_[0] = new NearToTower;
		strategies_[1] = new NearToCastle;
		strategies_[2] = new Strong;
		strategies_[3] = new Weak;
		strategies_[4] = new Fast;

		features_[0] = new Feature(1, 0, 1, 1, 10);
		features_[1] = new Feature(2, 10, 3, 2, 8);

		time = 0;
		enemyTable = new EnemyTable;
	}

	void Landscape::createPath() {
		std::queue<Road*> searchFrontier;
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
				if (playingField[i][j]->getType() == road) {
					Road* a = dynamic_cast<Road*>(playingField[i][j]);
					if (i > 0 && (playingField[i - 1][j]->getType() == cellTypeEnum::road)) {
						Road* b = dynamic_cast<Road*>(playingField[i - 1][j]);
						Road::makeNorthSouthNeighbours(b, a);
					}
					if (j > 0 && (playingField[i][j - 1]->getType() == cellTypeEnum::road)) {
						Road* b = dynamic_cast<Road*>(playingField[i][j - 1]);
						Road::makeWestEastNeighbours(b, a);
					}
					a->clearPath();
				}
		Road* dest = dynamic_cast<Road*>(castle->cell_);
		dest->becomeDestination();
		searchFrontier.push(dest);

		while (!searchFrontier.empty()) {
			Road* tmp = searchFrontier.front();
			searchFrontier.pop();
			if (tmp) {
				searchFrontier.push(tmp->growPathNorth());
				searchFrontier.push(tmp->growPathSouth());
				searchFrontier.push(tmp->growPathEast());				
				searchFrontier.push(tmp->growPathWest());
			}
		}

	}

	bool Landscape::checkWay() const {
		
		
		for (auto i = lires.begin(); i != lires.end(); i++) {
			Road* tmp = dynamic_cast<Road*>((*i)->cell_);
			if (tmp->dist == std::numeric_limits<int>::max()) return false;
		}
		return true;
		
		/*
		for (int i = 0; i < lires.size(); i++) {
			Road* tmp = dynamic_cast<Road*>(lires[i]->cell_);
			if (tmp->dist == std::numeric_limits<int>::max()) return false;
		}
		return true;
		*/
	}

	void Landscape::finish() {
		for (auto i = playingField.begin(); i != playingField.end(); i++) 
			for (auto j = (*i).begin(); j != (*i).end(); j++) delete (*j);
		
		for (auto i = strategies_.begin(); i != strategies_.end(); i++) delete (*i);

		enemyTable->erase();
		
		// for enemy in emenyTable delete enemy

		

	}

	void Landscape::setCellType(int i, int j, cellTypeEnum type) {
		/*
		cellTypeEnum oldType = playingField[i][j]->getType();
		if (type == road || oldType == road) {
			// здесь надо проверить, не нарушится ли условие наличия пути от каждого логова к замку
		}
		Cell* newCell = playingField[i][j]->setType(type);
		playingField[i][j] = newCell;
		*/

		//redo

		return;

	}

	bool Landscape::check() const {
		return (checkCastle() && checkLire() && checkWay());
	}

	void Landscape::updateBalance(int mn) {
		castle->updBalance(mn);
	}

	cellTypeEnum Landscape::getCellType(int i, int j) const {
		return playingField[i][j]->getType();
	}


	void Field::destroy() {
		if (tower) delete tower;
	}


	Cords::Cords() {
		x = 0;
		y = 0;
	}

	Cords::Cords(double _x, double _y) {
		x = _x;
		y = _y;
	}

	/*
	EnemyTable::Iterator EnemyTable::begin()
	{
		return EnemyTableIt(arr.begin());
	}

	EnemyTable::Iterator EnemyTable::end()
	{
		return EnemyTableIt(arr.end());
	}

	int EnemyTableIt::operator !=(const EnemyTableIt& it) const
	{
		return cur != it.cur;
	}
	int EnemyTableIt::operator ==(const EnemyTableIt& it) const
	{
		return cur == it.cur;
	}

	std::vector<Enemy*> & EnemyTableIt::operator *()
	{
		return *cur;
	}

	std::pair<const std::string, int>* ConstAssocIt::operator ->()
	{
		return &(*cur);
	}

	ConstAssocIt& ConstAssocIt::operator ++()
	{
		++cur;
		return *this;
	}

	ConstAssocIt ConstAssocIt::operator ++(int)
	{
		ConstAssocIt res(*this);
		++cur;
		return res;
	}
	*/

	void EnemyTable::add(Enemy* e) {
		if (e) arr.push_back(e);
		else throw std::invalid_argument("enemy nullptr");
	}

	void EnemyTable::update() {
		for (int i = 0; i < arr.size(); i++) {
			if (arr[i]->hp()) arr[i]->turn();
			else {
				delete arr[i];
				arr.erase(arr.begin() + i);
			}
		}		
	}

	void EnemyTable::erase() {
		for (int i = 0; i < arr.size(); i++) delete arr[i];
	}

	

	Enemy* EnemyTable::operator[] (int i) const {
		return arr[i];
	}


	Landscape::~Landscape() {
		for (int i = 0; i < playingField.size(); i++)
			for (int j = 0; j < playingField[i].size(); j++)
				delete playingField[i][j];

		delete enemyTable;
	}

	bool Landscape::makeTurn() {
		for (int i = 0; i < enemyTable->size(); i++)
			(*enemyTable)[i]->turn();
		for (int i = 0; i < lires.size(); i++)
			lires[i]->spawnByTime();
		if (!castle->getHp()) return false;
		for (int i = 0; i < playingField.size(); i++)
			for (int j = 0; j < playingField[i].size(); j++) {
				Field* prField = dynamic_cast<Field*>(playingField[i][j]);
				if (prField) {
					bool b = prField->isBuilt();
					if (b) prField->getTower()->attack();
				}
				else {
					Road* prRoad = dynamic_cast<Road*>(playingField[i][j]);
					if (prRoad) {
						bool b = prRoad->isBuilt();
						if (b) {
							Trap* prTrap = dynamic_cast<Trap*>(prRoad->getBuilding());
							if (prTrap) prTrap->attack();
						}
					}
				}

			}


	}

	Castle::Castle(Cell* cell, double curHp, double maxHp, int money, std::string title) {
		cell_ = cell;
		curHp_ = curHp;
		maxHp_ = maxHp;
		money_ = money;
		title_ = title;
	}

	Building::Building() {
		cell_ = nullptr;
	}

	Building::Building(Cell* cell) {
		cell_ = cell;
	}

	Castle::Castle() {
		curHp_ = 100;
		maxHp_ = 100;
		money_ = 100;
		title_ = "Castle";
	}

	std::pair<double, double> Building::cords() const {
		return cell_->cords();
	}

	Lire::Lire() {
		cell_ = nullptr;
		schedule = nullptr;
		land = nullptr;
	}

	Lire::Lire(Cell* _cell, EnemySchedule* _schedule, Landscape* _land) {
		cell_ = _cell;
		schedule = _schedule;
		land = _land;
	}

	void Lire::spawn(Enemy* en) {
		EnemyTable* table = land->enemyTable;
		en->setCords(cell_->cords());
		table->add(en);
	}

	void Lire::spawnByTime() {
		std::vector<Enemy*> enemies = schedule->find(land->time);
		for (auto it = enemies.begin(); it != enemies.end(); it++) spawn(*it);
	}

	void Enemy::getHurt(double damage) {
		curHp -= damage * dmgMultiplier;
	}

	std::pair<double, double> Enemy::cords() const {
		return std::pair<double, double>(x_, y_);
	}

	void Enemy::setCords(std::pair<double, double> newCords) {
		x_ = newCords.first;
		y_ = newCords.second;
	}

	void Enemy::move() {
		directionEnum direction;
		if (road->getDist() == 0) {
			hit(land_->getCastle());
			return;
		}
		std::pair<double, double> dest = road->getNext()->cords();
		std::pair<double, double> cur = road->cords();
		double deltaX = dest.first - cur.first;
		double deltaY = dest.second - cur.second;

		if (deltaY > 0) direction = east;
		if (deltaY < 0) direction = west;
		if (deltaX > 0) direction = south;
		if (deltaX < 0) direction = north;

		switch (direction) {
		case east: {
			y_ += realSpeed;
			break;
		}
		case west: {
			y_ -= realSpeed;
			break;
		}
		case south: {
			x_ += realSpeed;
			break;
		}
		case north: {
			x_ -= realSpeed;
			break;
		}
		}


	}

	void Enemy::calculateHp() {
		for (int i = 0; i < effects->getSize(); i++)
			(*effects)[i]->action(this);
	}

	Enemy::Enemy() {
		title = "Enemy";
		maxHp = 1;
		curHp = 1;
		money = 1;
		speed = 0.25;
		realSpeed = speed;
		effects = nullptr;
		road = nullptr;
		land_ = nullptr;
		x_ = -1;
		y_ = -1;
	}

	Enemy::Enemy(std::string _title, double _max, double _cur, int _money, double _speed, std::vector<Effect*> _effects, double _x, double _y, Landscape* land) {
		title = _title;
		maxHp = _max;
		curHp = _cur;
		money = _money;
		speed = _speed;
		realSpeed = speed;
		effects = new EffectTable;
		for (int i = 0; i < _effects.size(); i++) {
			effects->addEffect(_effects[i]);
		}
		land_ = land;
		road = dynamic_cast<Road*>(land->getCell(floor(_x), floor(_y)));
		x_ = road->cords().first;
		y_ = road->cords().second;
	}

	Effect* EffectTable::operator[] (int index) {
		if (index >= 0 && index < effectsVec.size()) return effectsVec[index];
		return nullptr;
	}

	void Enemy::turn() {
		move();
		calculateHp();
	}

	void Enemy::hit(Castle* c) {
		c->damage(curHp);
		c->updBalance(money);
	}

	void Enemy::addEffect(Effect* eff) {
		if (eff) effects->addEffect(eff);
	}

	EnemySchedule::EnemySchedule(std::multimap<unsigned int, Enemy*> sch) {
		schedule = sch;
	}

	std::vector<Enemy*> EnemySchedule::find(unsigned int time) {
		auto eqRange = schedule.equal_range(time);
		auto beg = eqRange.first;
		auto end = eqRange.second;
		std::vector<Enemy*> ret;
		for (auto it = beg; it != end; it++) {
			Enemy* tmp = (*it).second;
			ret.push_back(tmp);
		}
		return ret;
	}

	
	

	void Landscape::start(int level) {

	}

	Feature::Feature(int level, int price, double radius, double damage, double shotSpeed) {
		price_ = price;
		radius_ = radius;
		damage_ = damage;
		shotSpeed_ = shotSpeed;
		level_ = level;
	}

	DefaultTower::DefaultTower(Cell* cell, Feature* feature, Strategy* strategy, Landscape* ls) {
		cell_ = cell;
		feature_ = feature;
		strategy_ = strategy;
		land = ls;
		if (dynamic_cast<NearToTower*>(strategy)) strategyType_ = nearToTower;
		else if (dynamic_cast<NearToCastle*>(strategy)) strategyType_ = nearToCastle;
		else if (dynamic_cast<Weak*>(strategy)) strategyType_ = weak;
		else if (dynamic_cast<Strong*>(strategy)) strategyType_ = strong;
		else strategyType_ = fast;
	}

	void DefaultTower::fire(Enemy* e) {
		if (lastShot_ < feature_->shotSpeed()) {
			tick();
			return;
		}
		if (e) e->getHurt(feature_->damage());
		lastShot_ = 0;
	}

	DefaultTower::DefaultTower(Landscape* land) {
		strategy_ = land->strategies()[strategyTypeEnum::nearToTower];
		level_ = 0;
		lastShot_ = 0;
		feature_ = land->features()[level_];
		strategyType_ = nearToTower;

	}

	DefaultTower::DefaultTower() {
		strategy_ = nullptr;
		level_ = 0;
		lastShot_ = 0;
		feature_ = nullptr;
		strategyType_ = noStrategy;
	}

	void DefaultTower::attack() {
		if (strategy_) strategy_->attack(this);
		else throw std::runtime_error("this tower cannot attack");

	}

	void DefaultTower::upgrade() {
		level_++;
		feature_ = land->features()[level_];
		land->updateBalance(feature_->price());

	}

	double Strategy::distance(Enemy* e, Building* b) {
		std::pair<double, double> ce = e->cords(),
			cb = b->cords();
		return sqrt(pow((ce.first - cb.first), 2) - pow((ce.second - cb.second), 2));
	}

	void NearToTower::attack(Tower* tw) {
		Enemy* curEnemy = nullptr;
		double mind = std::numeric_limits<double>::max();
		Landscape* land = tw->ls();
		EnemyTable* table = land->enemyTable;
		int size = table->size();

		for (int i = 0; i < size; i++) {
			double tmpDist = distance((*table)[i], tw);
			if (tmpDist < mind) {
				curEnemy = (*table)[i];
				mind = tmpDist;
			}
		}
		if (curEnemy && (mind < land->features()[tw->getLevel()]->radius()))
			tw->fire(curEnemy);
	}

	void NearToCastle::attack(Tower* tw) {
		Enemy* curEnemy = nullptr;
		double mind = std::numeric_limits<double>::max();
		Landscape* land = tw->ls();
		EnemyTable* table = land->enemyTable;
		int size = table->size();

		for (int i = 0; i < size; i++) {
			double tmpDist = distance((*table)[i], land->castle);
			if (tmpDist < mind && distance((*table)[i], tw) < land->features()[tw->getLevel()]->radius()) {
				curEnemy = (*table)[i];
				mind = tmpDist;
			}
		}
		if (curEnemy && (mind < land->features()[tw->getLevel()]->radius()))
			tw->fire(curEnemy);
	}

	void Strong::attack(Tower* tw) {
		Enemy* curEnemy = nullptr;
		double maxf = 0;
		Landscape* land = tw->ls();
		EnemyTable* table = land->enemyTable;
		int size = table->size();

		for (int i = 0; i < size; i++) {
			double tmpf = (*table)[i]->hp();
			if (tmpf > maxf && distance((*table)[i], tw) < land->features()[tw->getLevel()]->radius()) {
				curEnemy = (*table)[i];
				maxf = tmpf;
			}
		}
		if (curEnemy) tw->fire(curEnemy);
	}

	void Weak::attack(Tower* tw) {
		Enemy* curEnemy = nullptr;
		double minf = std::numeric_limits<double>::max();
		Landscape* land = tw->ls();
		EnemyTable* table = land->enemyTable;
		int size = table->size();

		for (int i = 0; i < size; i++) {
			double tmpf = (*table)[i]->hp();
			if (tmpf < minf && distance((*table)[i], tw) < land->features()[tw->getLevel()]->radius()) {
				curEnemy = (*table)[i];
				minf = tmpf;
			}
		}
		if (curEnemy) tw->fire(curEnemy);
	}

	void Fast::attack(Tower* tw) {
		Enemy* curEnemy = nullptr;
		double maxs = std::numeric_limits<double>::max();
		Landscape* land = tw->ls();
		EnemyTable* table = land->enemyTable;
		int size = table->size();

		for (int i = 0; i < size; i++) {
			double tmps = (*table)[i]->spd();
			if (tmps > maxs && distance((*table)[i], tw) < land->features()[tw->getLevel()]->radius()) {
				curEnemy = (*table)[i];
				maxs = tmps;
			}
		}
		if (curEnemy) tw->fire(curEnemy);
	}

	void Trap::attack() {
		EnemyTable* table = land_->table();
		int size = table->size();
		for (int i = 0; i < size; i++) {
			std::pair<double, double> tmpCords = (*table)[i]->cords();
			std::pair<double, double> selfCords = cell_->cords();
			if (floor(tmpCords.first) == floor(selfCords.first) &&
				floor(tmpCords.second) == floor(selfCords.second)) {
				auto result = std::find(std::begin(attached), std::end(attached), (*table)[i]);
				if (result != std::end(attached)) {
					Enemy* en = (*table)[i];
					applyEffect(en);
					attached.push_back(en);
				}
			}
		}
	}

	void MagicEntity::applyEffect(Enemy* e) {
		if (e) e->addEffect(effect);
	}

	Trap::Trap() {
		land_ = nullptr;
		effect = nullptr;
		cell_ = nullptr;
	}

	Trap::Trap(Landscape* _land) {
		land_ = _land;
		effect = nullptr;
		cell_ = nullptr;
	}

	Trap::Trap(Landscape* _land, Cell* _cell, effectTypeEnum _type, int value, unsigned int time) {
		land_ = _land;
		cell_ = _cell;
		switch (_type) {
		case weakness: {
			effect = new Weakness(_type, value, time);
			break;
		}
		case slowdown: {
			effect = new Slowdown(_type, value, time);
			break;
		}
		case poison: {
			effect = new Poison(_type, value, time);
		}
		default: {
			throw std::invalid_argument("invalid effect type");
		}
		}
	}

	MagicTower::MagicTower() {
		land_ = nullptr;
		cell_ = nullptr;
		feature_ = nullptr;
		strategy_ = nullptr;
		effect = nullptr;
	}

	MagicTower::MagicTower(Landscape* _land, Cell* _cell, Feature* feature, Strategy* _strategy, effectTypeEnum _type, int _value, unsigned int _time) {
		land_ = _land;
		cell_ = _cell;
		feature_ = feature;
		strategy_ = _strategy;
		switch (_type) {
		case weakness: {
			effect = new Weakness(_type, _value, _time);
			break;
		}
		case slowdown: {
			effect = new Slowdown(_type, _value, _time);
			break;
		}
		case poison: {
			effect = new Poison(_type, _value, _time);
		}
		default: {
			throw std::invalid_argument("invalid effect type");
		}
		}
	}

	



}
