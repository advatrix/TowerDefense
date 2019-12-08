#ifndef _EFFECTS_H_
#define _EFFECTS_H_

#include <limits>

#include "Entity.h"
#include "Enums.h"
#include "Enemy.h"

namespace TD {
	class Effect: public Entity
	{
	protected:
		unsigned int remainedTime;
		unsigned int value;
		Enemy* enemy;
		bool active;
	public:
		virtual void update() = 0;
		virtual Effect* copy() = 0;
		Effect() :
			remainedTime(std::numeric_limits<unsigned>::max()), value(0), enemy(nullptr), active(false){}
		Effect(Enemy* en, unsigned int time, unsigned int t);
		virtual ~Effect() {}

		unsigned int getRemainedTime() const { return remainedTime; }
		virtual effectTypeEnum getType() const { return effectTypeEnum::noEffect; }
		bool isActive() const { return active; }

		inline void setEnemy(Enemy* e) { enemy = e; }


		inline static double pc(double v) { return (v + 100) / 100; }
	};

	class Weakness : public Effect {
	public:
		Weakness() : Effect() {}
		using Effect::Effect;

		void update();
		~Weakness() {}
		Effect* copy();

		inline effectTypeEnum getType() const { return effectTypeEnum::weakness; }
	};

	class Slowdown : public Effect {
	public:
		Slowdown() : Effect() {}
		using Effect::Effect;
		void update();
		~Slowdown() {}
		Effect* copy();

		inline effectTypeEnum getType() const { return effectTypeEnum::slowdown; }
	};

	class Poison : public Effect {
	public: 
		Poison() : Effect() {}
		using Effect::Effect;
		void update();
		~Poison() {}
		Effect* copy();

		inline effectTypeEnum getType() const { return effectTypeEnum::poison; }
	};

}
#endif

