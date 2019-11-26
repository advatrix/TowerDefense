#pragma once

#include <map>

#include "Building.h"
#include "Landscape.h"
#include "Tower.h"
namespace TD {
	class Enemy {
	protected:
		std::string title;
		double maxHp;
		double curHp;
		int money;
		double speed;
		EffectTable effects;
		// Cords* cords;
		double x_;
		double y_;
		void move();
		void calculateHp();
	public:
		Enemy();
		virtual void turn();
		virtual void hit(int, Building*);
		void getHurt(double);
		
		void addEffect(Effect*);
		~Enemy();
		friend class Effect;
		inline double hp() const { return curHp; }
		std::pair<double, double> cords() const;
		inline double spd() const { return speed; }

	};
	
	
	
	
	class EnemySchedule {
	private:
		std::multimap<unsigned int, Enemy*> schedule; // std multi map
	public:
		EnemySchedule(std::pair<unsigned int, Enemy*>*);
		~EnemySchedule();
		friend class EnemyScheduleIterator;
	};

	class EnemyScheduleIterator {
	private:
		std::pair<unsigned int, Enemy*> cur;
	public:
		EnemyScheduleIterator next();
		EnemyScheduleIterator();
	};

	

	class EffectTable {
	private:
		int n;
		Effect* effects;
	public:
		EffectTable();
		~EffectTable();
		int getN();
		void addEffect(Effect*);
		friend class EffectTableIterator;
	};

	class EffectTableIterator {
	private:
		Effect cur;
	public:
		EffectTableIterator next();
	};

	class Effect {
	protected:
		int value;
		unsigned int remainedTime;
	public:
		virtual void action(Enemy&);
		virtual void update();
		Effect();
	};

	class Weakness : Effect {
	public:
		void action(Enemy&);
	};

	class Slowdown : Effect {
	public:
		void action(Enemy&);
	};

	class Poison : Effect {
	public:
		void action(Enemy&);
	};
}

