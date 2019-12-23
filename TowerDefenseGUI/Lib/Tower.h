/**
\file
This file contains implementaion of the Tower class
*/

#ifndef _TOWER_H_
#define _TOWER_H_

#include "Building.h"
#include "Feature.h"
#include "Strategy.h"

namespace TD {
	/**
	This class describes states of every Tower instance in the game
	*/
	class Tower : public Building {
	protected:
		Strategy* strategy; ///< A pointer to the Strategy Tower has
		Feature* feature; ///< A pointer to the Feature Tower has
		unsigned int lastShot; ///< Tick since the las shot of the Tower
		std::pair<double, double> cords; ///< Current coodrninates of the Cell the Tower stands on
	public:
		virtual ~Tower() {}
		Tower() : strategy(nullptr), feature(nullptr), lastShot(0), cords() {}
		Tower(Feature* _feature, Strategy* _strategy, unsigned int _lastShot,
			std::pair<double, double> cords);

		inline strategyTypeEnum getStrategyType() const { return strategy->getType(); }
		virtual inline buildingTypeEnum getType() const { return buildingTypeEnum::tower; }


		/**
		This function is called every game tick and updates the Tower's state: increases last shot time and shots if necessary
		*/
		virtual void update();


		/**
		Sets a new Feature to the Tower
		\param [in] f A pointer to the new Feature
		*/
		void setFeature(Feature* f) { feature = f; }

		/**
		Sets a new Strategy to the Tower
		\param [in] s A pointer to the new Strategy
		*/
		void setStrategy(Strategy* s) { strategy = s; }

		/**
		\return current Level of the Feature Tower has
		*/
		unsigned int getLevel() const { return feature->getLevel(); }


	};
}

#endif

