#pragma once
#include "Building.h"
#include "Landscape.h"
#include "Enemy.h"

namespace TD {
	class Tower : public Building {
	protected:
		unsigned int level_;
		unsigned int lastShot_;
		Feature* feature_;
		virtual void fire(Enemy&) {}
	public:
		virtual void upgrade() {}
		virtual void attack() {}
	};

	class Feature {
	private:
		int price_;
		double radius_;
		double damage_;
		double shotSpeed_;
	public:
		void behaviour();
		Feature();
		friend class Tower;
		Feature(int price, double raduis, double damage, double shotSpeed);
	};


	class DefaultTower : public Tower {
	protected:
		Strategy* strategy_;
		void fire(Enemy&);
	public:
		DefaultTower();
		DefaultTower(Feature*, Strategy*);
		void attack();
	};

	class Strategy {
	public:
		virtual void attack(Tower&);
	};

	class NearToTower : public Strategy {
	public:
		void attack(Tower&);
		NearToTower() {}
	};

	class NearToCastle : public Strategy {
	public:
		void attack(Tower&);
	};

	class Strong : public Strategy {
	public:
		void attack(Tower&);
	};

	class Weak : public Strategy {
	public:
		void attack(Tower&);
	};

	class Fast : public Strategy {
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

