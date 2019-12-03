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
		effectTypeEnum type;
		unsigned int value;
		Enemy* enemy;
		bool active;
	public:
		virtual void update() = 0;
		virtual Effect* copy() = 0;
		Effect() :
			remainedTime(std::numeric_limits<unsigned>::max()), type(noEffect), value(0), enemy(nullptr), active(false){}
		Effect(Enemy* en, unsigned int time, unsigned int t, effectTypeEnum _type);
		virtual ~Effect() {}

		unsigned int getRemainedTime() const { return remainedTime; }
		effectTypeEnum getType() const { return type; }
		bool isActive() const { return active; }

		inline void setEnemy(Enemy* e) { enemy = e; }


		inline static double pc(double v) { return (v + 100) / 100; }
	};

	class Weakness : public Effect {
	public:
		Weakness() : Effect() {
			type = effectTypeEnum::weakness;
		}
		using Effect::Effect;

		void update();
		~Weakness() {}
		Effect* copy();
	};

	class Slowdown : public Effect {
	public:
		Slowdown() : Effect() {
			type = effectTypeEnum::slowdown;
		}
		using Effect::Effect;
		void update();
		~Slowdown() {}
		Effect* copy();
	};

	class Poison : public Effect {
	public: 
		Poison() : Effect() {
			type = effectTypeEnum::poison;
		}
		using Effect::Effect;
		void update();
		~Poison() {}
		Effect* copy();
	};

}
#endif

