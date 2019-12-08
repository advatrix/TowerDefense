#include "pch.h"

#include "..//TowerDefenseStaticLib/TowerDefenseLib.h"
#include <tchar.h>

using namespace TD;

const double err = 1e-8;

TEST(LandscapeInit, Default) {
	Landscape land;
	ASSERT_EQ(land.getHeight(), 0);
	ASSERT_EQ(land.getWidth(), 0);
}

TEST(_Castle, initEmpty) {
	Castle c;
	ASSERT_EQ(c.getTitle(), "Castle");
	ASSERT_EQ(c.getMoney(), 100);
	ASSERT_EQ(c.getCurHp(), 100);
	ASSERT_EQ(c.getType(), buildingTypeEnum::castle);
}

TEST(_Castle, init) {
	std::pair<double, double> p(5.6, 6.5);
	Castle c(&p, "a", 45.15, 50, 13);
	ASSERT_EQ(c.getTitle(), "a");
	ASSERT_EQ(c.getMoney(), 13);
	ASSERT_EQ(c.getCurHp(), 45.15);
	ASSERT_EQ(c.getType(), buildingTypeEnum::castle);
	ASSERT_EQ(c.getCords().first, p.first);
	ASSERT_EQ(c.getCords().second, p.second);
}

TEST(_Castle, inc_dec) {
	std::pair<double, double> p(5.6, 6.5);
	Castle c(&p, "a", 45.15, 50, 13);
	ASSERT_EQ(c.getMoney(), 13);
	ASSERT_EQ(c.getCurHp(), 45.15);

	c.decHp(1.2);
	ASSERT_NEAR(c.getCurHp(), 43.95, err);

	c.decHp(0);
	ASSERT_NEAR(c.getCurHp(), 43.95, err);

	c.decHp(-3.95);
	ASSERT_NEAR(c.getCurHp(), 40, err);

	c.decHp(50);
	ASSERT_NEAR(c.getCurHp(), 0, err);

	c.decHp(10);
	ASSERT_NEAR(c.getCurHp(), 0, err);

	c.incHp(44.2);
	ASSERT_NEAR(c.getCurHp(), 44.2, err);

	c.incHp(0.2);
	ASSERT_NEAR(c.getCurHp(), 44.4, err);

	c.incHp(7.6);
	ASSERT_NEAR(c.getCurHp(), 50, err);

	c.incMoney(909);
	ASSERT_EQ(c.getMoney(), 922);

	ASSERT_THROW(c.decMoney(940), std::runtime_error);
	ASSERT_EQ(c.getMoney(), 922);

	c.decMoney(922);
	ASSERT_EQ(c.getMoney(), 0);
}

TEST(_Cell, initEmpty) {
	Cell c;
	ASSERT_EQ(c.getType(), cellTypeEnum::forest);
	std::pair<double, double> cords = c.cords();
	ASSERT_NEAR(cords.first, 0, err);
	ASSERT_NEAR(cords.second, 0, err);
}


TEST(_Cell, init) {
	Cell c(4, -8);
	ASSERT_EQ(c.getType(), cellTypeEnum::forest);
	std::pair<double, double> cords = c.cords();
	ASSERT_NEAR(cords.first, 4, err);
	ASSERT_NEAR(cords.second, -8, err);
}

TEST(_Road, initEmpty) {
	Road r;
	ASSERT_EQ(r.getType(), cellTypeEnum::road);
	std::pair<double, double> cords = r.cords();
	ASSERT_NEAR(cords.first, 0, err);
	ASSERT_NEAR(cords.second, 0, err);
	ASSERT_EQ(r.hasPath(), false);
	ASSERT_EQ(r.isBuilt(), false);
	ASSERT_EQ((r.getNext() == nullptr), true);
	ASSERT_EQ((r.getBuilding() == nullptr), true);
	ASSERT_EQ(r.getDist(), std::numeric_limits<unsigned>::max());
}

TEST(_Road, init) {
	Road r(5, 6);
	ASSERT_EQ(r.getType(), cellTypeEnum::road);
	std::pair<double, double> cords = r.cords();
	ASSERT_NEAR(cords.first, 5, err);
	ASSERT_NEAR(cords.second, 6, err);
	ASSERT_EQ(r.hasPath(), false);
	ASSERT_EQ(r.isBuilt(), false);
	ASSERT_TRUE(r.getNext() == nullptr);
	ASSERT_TRUE(r.getBuilding() == nullptr);
	ASSERT_EQ(r.getDist(), std::numeric_limits<unsigned>::max());
}

TEST(_Road, build) {
	/*
	std::pair<double, double> p(4., 5.);
	Road r(4, 5);
	Castle* c = new Castle(&p, "castle", 35, 40, 100);
	Feature* f = new Feature(1, 1, 1, 1, 1);
	Effect* e = new Weakness();
	Strategy* s = new NearToTower;
	Tower* t = new Tower(f, s, 0, &p);
	ASSERT_EQ(t->getType(), buildingTypeEnum::tower);
	Trap* tr = new Trap;

	ASSERT_THROW(r.build(t), std::invalid_argument);
	*/ //TODO
}

TEST(_Field, initEmpty) {
	Field f;
	ASSERT_NEAR(f.cords().first, 0, err);
	ASSERT_NEAR(f.cords().second, 0, err);
	ASSERT_EQ(f.isBuilt(), false);
	ASSERT_TRUE(f.getTower() == nullptr);
}




int _tmain(int argc, _TCHAR* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}