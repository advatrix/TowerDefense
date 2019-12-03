#include "pch.h"
#include "Feature.h"

#include <stdexcept>

namespace TD {
	Feature::Feature(unsigned int p, double r, double d, unsigned int ss, unsigned int lvl) {
		if (r <= 0) throw std::invalid_argument("radius is not positive");
		if (d <= 0) throw std::invalid_argument("damage is not positive");
		price = p;
		radius = r;
		damage = d;
		shotSpeed = ss;
		level = lvl;
	}
}
