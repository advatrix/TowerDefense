#ifndef _FEATURE_H_
#define _FEATURE_H_

#include "Enums.h"

namespace TD {
	class Feature {
	private:
		unsigned int price;
		double radius;
		double damage;
		unsigned int shotSpeed;
		unsigned int level;
	public:
		Feature(unsigned int p, double r, double d, unsigned int ss, unsigned int lvl);
		Feature() :
			price(0), radius(1), damage(1), shotSpeed(0), level(0) {}

		inline unsigned int getPrice() const { return price; }
		inline double getRadius() const { return radius; }
		inline double getDamage() const { return damage; }
		inline unsigned int getShotSpeed() const { return shotSpeed; }
		inline unsigned int getLevel() const { return level; }

	};
}


#endif

