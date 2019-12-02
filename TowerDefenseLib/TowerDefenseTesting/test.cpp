#include "pch.h"

#include "..//TowerDefenseStaticLib/Landscape.h"
#include <tchar.h>

using namespace TD;

const double err = 1e-8;

TEST(LandscapeInit, Default) {
	Landscape land;
	ASSERT_EQ(land.getCastle(), nullptr);
	ASSERT_EQ(land.getHeight(), 0);
	ASSERT_EQ(land.getWidth(), 0);
	ASSERT_EQ(land.getSize(), 0);
	ASSERT_EQ(land.getTime(), 0);
}

TEST(LandscapeStart, Empty) {
	Landscape land;
//	ASSERT_THROW(land.start(0), std::runtime_error);
}


TEST(RoadInit, Default) {
	Road r;
	ASSERT_EQ(r.isBuilt(), false);
	ASSERT_EQ(r.getDist(), std::numeric_limits<int>::max());
//	ASSERT_EQ(r.)
}

TEST(roadDestroy, destroyEmpty) {
	Road r;
	ASSERT_EQ(r.isBuilt(), false);
	// r.destroy();
	ASSERT_THROW(r.destroy(), std::exception);
	try {
		r.destroy();
	}
	catch (std::exception& e) {
		ASSERT_EQ(strcmp(e.what(), "impossible to destroy"), 0);
	}
}

TEST(cellInit, defaultCords) {
	ASSERT_NO_THROW(Cell c(5, 4));
	Cell c(5, 4);
	std::pair<double, double> cords = c.cords();
	ASSERT_NEAR(cords.first, 5., err);
	ASSERT_NEAR(cords.second, 4., err);
	ASSERT_EQ(c.getType(), forest);


}

TEST(cellInit, _default) {
	Cell c;
	ASSERT_EQ(c.getType(), forest);
	auto cords = c.cords();
	ASSERT_NEAR(cords.first, 0, err);
	ASSERT_NEAR(cords.second, 0, err);
}

TEST(emptyCell, setType) {
	Cell c;

}






int _tmain(int argc, _TCHAR* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}