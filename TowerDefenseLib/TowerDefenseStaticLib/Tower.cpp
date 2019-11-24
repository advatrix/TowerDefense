#include "pch.h"
#include "Tower.h"

namespace TD {
	Feature::Feature(int price, double radius, double damage, double shotSpeed) {
		price_ = price;
		radius_ = radius;
		damage_ = damage;
		shotSpeed_ = shotSpeed;
	}

	DefaultTower::DefaultTower(Feature* feature, Strategy* strategy) {
		feature_ = feature;
		strategy_ = strategy;
	}

}