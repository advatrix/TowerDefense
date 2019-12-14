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
	std::string a = "a";
	Castle c(p, a, 45.15, 50.2, 13);
	ASSERT_EQ(c.getTitle(), "a");
	ASSERT_EQ(c.getMoney(), 13);
	ASSERT_EQ(c.getCurHp(), 45.15);
	ASSERT_EQ(c.getType(), buildingTypeEnum::castle);
	ASSERT_EQ(c.getCords().first, p.first);
	ASSERT_EQ(c.getCords().second, p.second);
}

TEST(_Castle, inc_dec) {
	std::pair<double, double> p(5.6, 6.5);
	Castle c(p, "a", 45.15, 50, 13);
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


TEST(_Field, initEmpty) {
	Field f;
	ASSERT_NEAR(f.cords().first, 0, err);
	ASSERT_NEAR(f.cords().second, 0, err);
	ASSERT_EQ(f.isBuilt(), false);
	ASSERT_TRUE(f.getTower() == nullptr);
}

TEST(_Road, buildCastle) {
	Road r(0, 0);
	Castle* c = new Castle(r.cords(), "castle", 1., 2., 2);
	r.build(c);
	ASSERT_EQ(r.getBuilding(), c);
	ASSERT_EQ(r.isBuilt(), true);
	
	ASSERT_EQ(c->getCords(), r.cords());

	delete c;
}

TEST(_Road, buildTwice) {
	Road r(0, 0);
	Castle* c = new Castle(r.cords(), "castle", 1., 2., 2);
	r.build(c);
	ASSERT_EQ(r.getBuilding(), c);
	ASSERT_EQ(r.isBuilt(), true);

	Castle* b = new Castle(r.cords(), "castle", 2., 3., 4);
	ASSERT_THROW(r.build(b), std::runtime_error);

	delete c;
	delete b;
}

TEST(_Road, buildLire) {
	Road r(0, 0);
	Lire* l = new Lire();

	r.build(l);

	ASSERT_EQ(r.getBuilding(), l);
	ASSERT_EQ(r.isBuilt(), true);

	delete l;
}

TEST(_Road, buildTrap) {
	Road r(0, 0);
	Trap* t = new Trap();

	r.build(t);

	ASSERT_EQ(r.getBuilding(), t);
	ASSERT_EQ(r.isBuilt(), true);

	delete t;
}

TEST(_Road, buildTower) {
	Road r(0, 0);
	Tower* t = new Tower();

	ASSERT_THROW(r.build(t), std::invalid_argument);
	ASSERT_EQ(r.getBuilding(), nullptr);
	ASSERT_EQ(r.isBuilt(), false);

	delete t;
}

TEST(_Road, buildMagicTower) {
	Road r(0, 0);
	MagicTower* m = new MagicTower();

	ASSERT_THROW(r.build(m), std::invalid_argument);
	ASSERT_EQ(r.getBuilding(), nullptr);
	ASSERT_EQ(r.isBuilt(), false);

	delete m;
}

TEST(_Road, destroy) {
	Road r(0, 0);
	Trap* t = new Trap();

	r.build(t);
	r.destroy();

	ASSERT_EQ(r.getBuilding(), nullptr);
	ASSERT_EQ(r.isBuilt(), false);
	
	t = new Trap();

	r.build(t);
	ASSERT_EQ(r.getBuilding(), t);
	ASSERT_EQ(r.isBuilt(), true);

	delete t;
}

TEST(_Road, destroyEmpty) {
	Road r(0, 0);
	ASSERT_THROW(r.destroy(), std::exception);
}

TEST(_Road, destroyCastle) {
	Road r(0, 0);
	Castle* c = new Castle(r.cords(), "castle", 2., 3., 23);

	r.build(c);


	ASSERT_THROW(r.destroy(), std::exception);
	ASSERT_EQ(r.getBuilding(), c);

	delete c;
}

TEST(_Road, destroyLire) {
	Road r(0, 0);
	Lire* l = new Lire();

	r.build(l);

	ASSERT_THROW(r.destroy(), std::exception);
	ASSERT_EQ(r.getBuilding(), l);

	delete l;
}

TEST(_Road, buildNullptr) {
	Road r(0, 0);
	ASSERT_THROW(r.build(nullptr), std::invalid_argument);
}

TEST(_Field, buildTower) {
	Field f(0, 0);
	Tower* t = new Tower();
	f.build(t);
	ASSERT_EQ(f.getTower(), t);
	delete t;
}

TEST(_Field, buildMagicTower) {
	MagicTower* m = new MagicTower();
	Field f(0, 0);
	f.build(m);

	ASSERT_EQ(f.getTower(), m);
	ASSERT_EQ(f.isBuilt(), true);
	delete m;

}

TEST(_Field, destroy) {
	Tower* t = new Tower();
	Field f(0, 0);
	f.build(t);

	f.destroy();

	ASSERT_EQ(f.getTower(), nullptr);
	ASSERT_EQ(f.isBuilt(), false);

	t = new Tower();
	f.build(t);
	Tower* u = new Tower();
	ASSERT_THROW(f.build(u), std::exception);

	delete u;
	delete t;
}

TEST(_Field, buildNullPtr) {
	Field f(0, 0);
	ASSERT_THROW(f.build(nullptr), std::invalid_argument);
}

TEST(_Weakness, def) {
	Weakness w;
	ASSERT_EQ(w.getRemainedTime(), std::numeric_limits<unsigned>::max());
	ASSERT_EQ(w.getType(), effectTypeEnum::weakness);
	ASSERT_EQ(w.getValue(), 0);
}

TEST(_Poison, def) {
	Poison p;
	ASSERT_EQ(p.getRemainedTime(), std::numeric_limits<unsigned>::max());
	ASSERT_EQ(p.getType(), effectTypeEnum::poison);
	ASSERT_EQ(p.getValue(), 0);
}

TEST(_Slowdown, def) {
	Slowdown s;
	ASSERT_EQ(s.getRemainedTime(), std::numeric_limits<unsigned>::max());
	ASSERT_EQ(s.getType(), effectTypeEnum::slowdown);
	ASSERT_EQ(s.getValue(), 0);
}

TEST(_Weakness, update) {
	std::string title = "enemy";
	Enemy* e = new Enemy(0, 0, 3, 3, 3, title, 3, 3, 1);

	Weakness* w = new Weakness(e, 5, 5);

	ASSERT_NEAR(e->getDamageMultiplier(), 1., err);
	w->update();
	ASSERT_EQ(w->getRemainedTime(), 4);
	ASSERT_EQ(w->getValue(), 5);
	ASSERT_NEAR(e->getDamageMultiplier(), 1.05, err);

	e->makeDamage(1);
	ASSERT_NEAR(e->getCurHp(), 1.95, err);

	for (int i = 0; i < 4; i++) w->update();
	ASSERT_NEAR(e->getDamageMultiplier(), 1, err);
	ASSERT_EQ(w->getRemainedTime(), 0);

	e->makeDamage(1);
	ASSERT_EQ(e->getCurHp(), 0.95, err);

	delete w;
	delete e;
}

TEST(Poison, update) {
	std::string title = "enemy";
	Enemy* e = new Enemy(0, 0, 10, 10, 10, title, 10, 10, 1);
	Poison* p = new Poison(e, 5, 1);

	p->update();
	ASSERT_NEAR(e->getCurHp(), 9, err);

	for (int i = 0; i < 4; i++) {
		p->update();
		ASSERT_NEAR(e->getCurHp(), 8 - i, err);
	}

	ASSERT_NEAR(e->getCurHp(), 5, err);
	ASSERT_EQ(p->getRemainedTime(), 0);

	ASSERT_EQ(p->isActive(), false);
	delete e;
	delete p;
}

TEST(_Slowdown, update) {
	std::string title = "enemy";
	Enemy* e = new Enemy(0, 0, 10, 10, 10, title, 10, 10, 1);

	Slowdown* s = new Slowdown(e, 5, 5);

	ASSERT_NEAR(e->getCurSpeed(), 10., err);

	for (int i = 0; i < 4; i++) {
		s->update();
		ASSERT_EQ(s->getRemainedTime(), 4 - i);
		ASSERT_NEAR(e->getCurSpeed(), (10 / 1.05), err);
	}

	s->update();
	ASSERT_NEAR(e->getCurSpeed(), 10, err);

	delete s;
	delete e;
}

TEST(_Slowdown, copy) {
	std::string title = "enemy";
	Enemy* e = new Enemy(0, 0, 10, 10, 10, title, 10, 10, 1);

	Slowdown* s = new Slowdown(e, 5, 5);

	Effect* t = s->copy();
	ASSERT_EQ(t->getRemainedTime(), 5);
	ASSERT_EQ(t->getType(), effectTypeEnum::slowdown);
	ASSERT_EQ(t->getValue(), 5);

	delete e;
	delete s;
	delete t;
}

TEST(_Weakness, copy) {
	std::string title = "enemy";
	Enemy* e = new Enemy(0, 0, 10, 10, 10, title, 10, 10, 1);

	Weakness* s = new Weakness(e, 5, 5);

	Effect* t = s->copy();
	ASSERT_EQ(t->getRemainedTime(), 5);
	ASSERT_EQ(t->getType(), effectTypeEnum::weakness);
	ASSERT_EQ(t->getValue(), 5);

	delete e;
	delete s;
	delete t;
}

TEST(_Poison, copy) {
	std::string title = "enemy";
	Enemy* e = new Enemy(0, 0, 10, 10, 10, title, 10, 10, 1);

	Poison* s = new Poison(e, 5, 5);

	Effect* t = s->copy();
	ASSERT_EQ(t->getRemainedTime(), 5);
	ASSERT_EQ(t->getType(), effectTypeEnum::poison);
	ASSERT_EQ(t->getValue(), 5);

	delete e;
	delete s;
	delete t;
}

TEST(_Effects, setEnemy) {
	std::string title = "enemy";
	Enemy* e = new Enemy(0, 0, 10, 10, 10, title, 10, 10, 1);

	Effect* p = new Poison(e, 5, 5);
	Effect* w = new Weakness(e, 5, 5);
	Effect* s = new Slowdown(e, 5, 5);

	s->setEnemy(nullptr);
	s->update();

	ASSERT_NEAR(e->getCurSpeed(), 10, err);
	ASSERT_EQ(s->getRemainedTime(), 5);

	Enemy* f = new Enemy(1, 1, 30, 30, 30, title, 20, 30, 1);
	p->setEnemy(f);
	
	p->update();
	ASSERT_NEAR(f->getCurHp(), 15, err);
	ASSERT_NEAR(e->getCurHp(), 10, err);
	ASSERT_EQ(p->getRemainedTime(), 4);

	p->setEnemy(e);
	p->update();
	ASSERT_EQ(p->getRemainedTime(), 3);

	w->setEnemy(e);
	w->update();
	ASSERT_EQ(w->getRemainedTime(), 4);
	w->setEnemy(e);
	ASSERT_EQ(w->getRemainedTime(), 4);

	delete e;
	delete f;
	delete p;
	delete s;
	delete w;

}

TEST(_Effects, updateNullptr) {
	Poison p;
	Slowdown s;
	Weakness w;

	p.update();
	ASSERT_EQ(p.getRemainedTime(), std::numeric_limits<unsigned>::max());

	s.update();
	ASSERT_EQ(s.getRemainedTime(), std::numeric_limits<unsigned>::max());

	w.update();
	ASSERT_EQ(w.getRemainedTime(), std::numeric_limits<unsigned>::max());
}

TEST(pc, tests) {
	ASSERT_NEAR(Effect::pc(1), 1.01, err);
	ASSERT_NEAR(Effect::pc(0), 1., err);
	ASSERT_NEAR(Effect::pc(100), 2., err);
	ASSERT_NEAR(Effect::pc(-1), 0.99, err);
	ASSERT_NEAR(Effect::pc(-100), 0, err);
	ASSERT_NEAR(Effect::pc(-200), -1, err);
	ASSERT_NEAR(Effect::pc(12.34), 1.1234, err);
	ASSERT_NEAR(Effect::pc(500), 6, err);
}





int _tmain(int argc, _TCHAR* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}