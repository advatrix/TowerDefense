/**
\file 
This file contains implementation of Feature class
*/

#ifndef _FEATURE_H_
#define _FEATURE_H_

#include "Enums.h"

namespace TD {
	/**
	This class decribes features of every Tower in the game
	*/
	class Feature {
	private:
		unsigned int price; ///< The price to build a Tower with this feature or to update Tower to this feature
		double radius; ///< Raduis in which the Tower cann attack enemies
		double damage; ///< Damage that the Tower can make on the Enemy every shot
		unsigned int shotSpeed; ///< The minimum possible interval between two Tower shots
		unsigned int level; ///< Current level of the Tower (indeed, the serial number of the Feature instance)
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

