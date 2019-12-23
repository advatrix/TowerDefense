/**
\file
This file contains implementation of Entity class
*/

#ifndef _ENTITY_H_
#define _ENTITY_H_

namespace TD {
	/**
	\brief The very basic class of every entity of the game
	This class provides polymorphism to every entity that has to be updated every game tick and whose behaviour depends on time
	*/
	class Entity {
	public:
		/**
		Function that is called every game tick and updates the instance's state
		*/
		virtual void update() = 0;
		virtual ~Entity() {}
	};
}

#endif

