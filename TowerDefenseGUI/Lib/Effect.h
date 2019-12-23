/**
\file
\brief In this file all Effects of the game are implemented.
*/
#ifndef _EFFECTS_H_
#define _EFFECTS_H_

#include <limits>

#include "Entity.h"
#include "Enums.h"
#include "Enemy.h"

namespace TD {
	/**
	\brief Parent class that provides polymorphism for all Effects in the game
	*/
	class Effect: public Entity
	{
	protected:
		unsigned int remainedTime;///<Effect remaining time. Equals to maximum posiible unsigned value if effect is not active
		unsigned int value;///<Value of the effect in percents of the enemy's parameter the effect affects.
		Enemy* enemy;///<A pointer to the enemy Effect affects. Equals to nullptr if instance is disabled
		bool active;
	public:
		/**
		\brief This function is called every game tick and updates the parameter of the effect instance.
		The function updates the parameters of the Effect (decreases remaining time) and the Enemy if needed.
		*/
		virtual void update() = 0;

		/**
		Returns a copy of particular effect instance
		\return A copy of particular effect instance
		*/
		virtual Effect* copy() = 0;
		Effect() :
			remainedTime((std::numeric_limits<unsigned>::max)()), value(0), enemy(nullptr), active(false){}
		Effect(Enemy* en, unsigned int time, unsigned int t);
		virtual ~Effect() {}

		inline unsigned int getValue() const { return value; }
		inline unsigned int getRemainedTime() const { return remainedTime; }
		virtual effectTypeEnum getType() const { return effectTypeEnum::noEffect; }
		inline bool isActive() const { return active; }
		
		inline void setEnemy(Enemy* e) { enemy = e; }

		/**
		Function that converts effect values into a multiplier apllied to the enemy parameters
		\param [in] v Value to convert
		\return Multiplier
		*/
		inline static double pc(double v) { return (v + 100) / 100; }
	};


	/**
	\brief This class describes Weakness effect
	Weakness affects enemy's Damage Multiplier so that the enemy will get higher damage from towers while being affected by Weakness.
	*/
	class Weakness : public Effect {
	public:
		Weakness() : Effect() {}
		using Effect::Effect;

		/**
		Reimplementation of the update() function from the parent Effect class.
		If called firstly, changes the enemy's damageMultiplier according to the instance's "value" parameter, sets the "active" flag to true, and decrements remaining time.
		Otherwise only decrements remaining time.
		*/
		void update();
		~Weakness() {}
		Effect* copy();

		inline effectTypeEnum getType() const { return effectTypeEnum::weakness; }
	};

	/**
	\brief This class describes Slowdown effect
	Slowdown affects Enemy's speed so that the Enemy will move slower while being affected by Slowdown instance.
	*/
	class Slowdown : public Effect {
	public:
		Slowdown() : Effect() {}
		using Effect::Effect;
		/**
		Reimplementation of the update() function from the parent Effect class.
		If called firstly, chenges the Enemy's curSpeed value accorgind to "value" parameter in particular Slowdown instance, sets the "active" flag to true, and decrements remaning time.
		Otherwise only decrements remaining time.
		*/
		void update();
		~Slowdown() {}
		Effect* copy();

		inline effectTypeEnum getType() const { return effectTypeEnum::slowdown; }
	};

	/**
	\brief This class describes Poison effect
	Poison make damage on Enemy's every time update() function is called
	*/
	class Poison : public Effect {
	public: 
		Poison() : Effect() {}
		using Effect::Effect;

		/**
		Reimplementation of the update() function from the parent Effect class.
		Makes damage to the Enemy equal the instance's "value" and decrements remaining time
		*/
		void update();
		~Poison() {}
		Effect* copy();

		inline effectTypeEnum getType() const { return effectTypeEnum::poison; }
	};

}
#endif

