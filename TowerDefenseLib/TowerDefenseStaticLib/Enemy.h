#pragma once

#include <map>

#include "Building.h"
#include "Landscape.h"
#include "Tower.h"


namespace TD {
	class Road;
	class Landscape;


	class EffectTable {
	private:
		std::vector<Effect*> effectsVec;
	public:
		EffectTable() {}
		~EffectTable();
		void addEffect(Effect*);
		// friend class EffectTableIterator;
		Effect* operator[] (int index);
		// Effect* operator[] (int);
		inline int getSize() const { return effectsVec.size(); }
	};



	class Enemy {
	protected:
		std::string title;
		double maxHp;
		double curHp;
		int money;
		double speed;
		double realSpeed;
		double dmgMultiplier = 1;
		EffectTable* effects;
		Road* road;
		// Cords* cords;
		Landscape* land_;
		double x_;
		double y_;
		void move();
		void calculateHp();
	public:
		Enemy();

		Enemy(std::string _title, double _max, double _cur, int _money, double _speed, std::vector<Effect*> _effects, double _x, double _y, Landscape* land);


		void turn();
		void hit(Castle*);
		void getHurt(double);
		
		void addEffect(Effect*);
		~Enemy() {}
		friend class Effect;
		friend class Weakness;
		friend class Slowdown;
		friend class Poison;



		inline double hp() const { return curHp; }
		std::pair<double, double> cords() const;
		inline double spd() const { return speed; }
		void setCords(std::pair<double, double>);

	};
	
	enum directionEnum { north, east, south, west };
	
	
	
	class EnemySchedule {
	private:
		std::multimap<unsigned int, Enemy*> schedule; // std multi map
	public:
		EnemySchedule(std::multimap<unsigned int, Enemy*>);
		~EnemySchedule() {}
		// friend class EnemyScheduleIterator;

		std::vector<Enemy*> find(unsigned int);
	};
	/*/
	class EnemyScheduleIterator {
	private:
		std::pair<unsigned int, Enemy*> cur;
	public:
		EnemyScheduleIterator next();
		EnemyScheduleIterator();
	};

	*/

	


	/*
	class EffectTableIterator {
	private:
		Effect cur;
	public:
		EffectTableIterator next();
	};

	*/

	class Effect {
	protected:
		int value;
		unsigned int remainedTime;
		Enemy* en;
	public:
		virtual void action(Enemy*) = 0;
		void update();
		Effect();
		Effect(int, unsigned int, Enemy*) throw (std::invalid_argument);
	};

	class Weakness : Effect {
	public:
		void action(Enemy*);
	};

	class Slowdown : Effect {
	public:
		void action(Enemy*);
	};

	class Poison : Effect {
	public:
		void action(Enemy*);
	};
}

