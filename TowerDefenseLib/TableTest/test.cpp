#include "pch.h"
#include <tchar.h>

#include "..//TowerDefenseStaticLib/Table.h"

using namespace customTemplates;

TEST(tableInit, _int) {
	Table<int> table;
	ASSERT_EQ(table.getSize(), 0);
	ASSERT_EQ(table.allocated(), 0);

	table.insert(2);
	ASSERT_EQ(table[0], 2);
	ASSERT_EQ(table.getPos(2), 0);
	ASSERT_EQ(table.getSize(), 1);
	ASSERT_EQ(table.allocated(), 1);
	ASSERT_EQ(table.getPos(1), -1);

	table.insert(2);
	ASSERT_EQ(table.getPos(2), 0);
	ASSERT_EQ(table.getSize(), 1);
	ASSERT_EQ(table.allocated(), 1);

	table.insert(1);
	ASSERT_EQ(table.getPos(1), 1);
	ASSERT_EQ(table.getPos(2), 0);
	ASSERT_EQ(table.getSize(), 2);
	ASSERT_EQ(table.allocated(), 2);

	table.insert(3);
	ASSERT_EQ(table.getPos(3), 2);
	ASSERT_EQ(table.getSize(), 3);
	ASSERT_EQ(table.allocated(), 3);
	
	ASSERT_EQ(table[0], 2);
	ASSERT_EQ(table[1], 1);
	ASSERT_EQ(table[2], 3);

	table.remove(2);
	ASSERT_EQ(table.getPos(2), -1);
	ASSERT_EQ(table.getSize(), 2);
	ASSERT_EQ(table.allocated(), 3);
	ASSERT_EQ(table[0], 1);
	ASSERT_EQ(table[1], 3);
	
	ASSERT_THROW(table[2], std::invalid_argument);
	ASSERT_THROW(table[3], std::invalid_argument);
}

TEST(tableCopyConstructor, _int) {
	Table<int> t;
	t.insert(1);
	t.insert(2);
	t.insert(0);
	t.insert(4);
	t.insert(5);
	t.insert(7);
	t.remove(7);

	Table<int> u(t);

	ASSERT_EQ(t.getSize(), u.getSize());
	ASSERT_EQ(t.allocated(), u.allocated());
	
	for (int i = 0; i < t.getSize(); ++i) ASSERT_EQ(t[i], u[i]);
}

TEST(tableMoveConstructor, _int) {
	Table<int> t;
	t.insert(1);
	t.insert(2);
	t.insert(0);
	t.insert(4);
	t.insert(5);
	t.insert(7);

	Table<int> a = std::move(t);
	ASSERT_EQ(a.allocated(), 6);
	ASSERT_EQ(t.allocated(), 0);
	ASSERT_EQ(a.getSize(), 6);
	ASSERT_EQ(t.getSize(), 0);
	ASSERT_EQ(a[0], 1);
	ASSERT_EQ(a[5], 7);
	ASSERT_THROW(t[0], std::invalid_argument);
}

TEST(tableCopyOverloadEqual, _int) {
	Table<int> t;
	t.insert(1);
	t.insert(2);
	t.insert(0);
	t.insert(4);
	t.insert(5);
	t.insert(7);
	t.remove(7);

	Table<int> u = t;

	ASSERT_EQ(t.getSize(), u.getSize());
	ASSERT_EQ(t.allocated(), u.allocated());

	for (int i = 0; i < t.getSize(); ++i) ASSERT_EQ(t[i], u[i]);
}

TEST(tableInsert, _int) {
	Table<int> t;
	ASSERT_EQ(t.insert(0), 0);
	ASSERT_EQ(t.insert(2), 0);
	ASSERT_EQ(t.getSize(), 2);
	ASSERT_EQ(t.allocated(), 2);

	ASSERT_EQ(t.insert(0), 1);
	t.remove(0);

	ASSERT_EQ(t.insert(0), 0);
	ASSERT_EQ(t.getSize(), 2);
	ASSERT_EQ(t.allocated(), 2);

	ASSERT_EQ(t.insert(3), 0);
	ASSERT_EQ(t.getSize(), 3);
	ASSERT_EQ(t.allocated(), 3);
}

TEST(tableRemove, _int) {
	Table<int> t;
	ASSERT_EQ(t.remove(3), 1);
	
	ASSERT_EQ(t.insert(3), 0);
	ASSERT_EQ(t.insert(3), 1);
	ASSERT_EQ(t.remove(3), 0);
	ASSERT_EQ(t.getSize(), 0);
	ASSERT_EQ(t.getPos(3), -1);
	ASSERT_EQ(t.allocated(), 1);

	ASSERT_EQ(t.insert(3), 0);
}

TEST(tableIterator, _int) {
	Table<int> t;
	t.insert(1);
	t.insert(2);
	t.insert(0);
	t.insert(4);
	t.insert(5);
	t.insert(7);

	auto it = t.begin();
	ASSERT_EQ(*it, 1);

	it = t.end();
	ASSERT_EQ(*(--it), 7);
	ASSERT_EQ(*(it--), 7);
	ASSERT_EQ(*(it), 5);
	ASSERT_EQ(*(it++), 5);
	ASSERT_EQ(++it, t.end());
	it -= 3;
	ASSERT_EQ(*it, 4);
	it += 2;
	ASSERT_EQ(*it, 7);
}

TEST(tableTemplate, _double) {
	Table<double> d;
	d.insert(0.);
	d.insert(8.4);
	d.insert(-23);
	d.insert(std::numeric_limits<double>::max());

	ASSERT_EQ(d[0], 0.);
	ASSERT_EQ(d[1], 8.4);
	ASSERT_EQ(d[2], -23);
	ASSERT_EQ(d[3], std::numeric_limits<double>::max());
}

TEST(tableTemplate, _char) {
	Table<char> d;
	d.insert('\0');
	d.insert('û');
	d.insert('w');
	d.insert('\n');

	ASSERT_EQ(d[0], '\0');
	ASSERT_EQ(d[1], 'û');
	ASSERT_EQ(d[2], 'w');
	ASSERT_EQ(d[3], '\n');
}







int _tmain(int argc, _TCHAR* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}