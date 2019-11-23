#pragma once
#include "Building.h"
#include "Landscape.h"
#include "Enemy.h"

namespace TD {
	class Tower : Building {
	protected:
		unsigned int lvl;
		unsigned int lastShot;
		Feature* feature;
	public:
		virtual void upgrade();
		virtual void attack();
	};

	class Feature {
	private:
		int price;
		double radius;
		double damage;
		double shotSpeed;
	public:
		void behaviour();
		Feature();
		friend class Tower;
	};


	class DefaultTower : Tower {
	protected:
		Strategy* strategy;
		void fire(Enemy&);
	public:
		DefaultTower();
		void attack();
	};

	class Strategy {
	public:
		virtual void attack(Tower&);
	};

	class NearToTower : Strategy {
	public:
		void attack(Tower&);
	};

	class NearToCastle : Strategy {
	public:
		void attack(Tower&);
	};

	class Strong : Strategy {
	public:
		void attack(Tower&);
	};

	class Weak : Strategy {
	public:
		void attack(Tower&);
	};

	class Fast : Strategy {
	public:
		void attack(Tower&);
	};

	class MagicEntity {
	protected:
		Effect effect;
	public:
		virtual void applyEffect(Enemy&);
	};

	class Trap : Building, MagicEntity {
	public: void attack();
	};

	class MagicTower : DefaultTower, MagicEntity {
	public:
		void applyEffect(Enemy&);
	};
}

