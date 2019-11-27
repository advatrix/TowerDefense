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
		strategyTypeEnum strategyType_;
		
		static Landscape* land;
	public:
		virtual void upgrade() = 0;
		virtual void attack() = 0;
		inline void tick() { ++lastShot_; }
		inline Landscape* ls() const { return land; }
		virtual void fire(Enemy*) = 0;
		virtual strategyTypeEnum strategyType() const = 0;
	};

	class Feature {
	private:
		int price_;
		double radius_;
		double damage_;
		unsigned int shotSpeed_;
		int level_;
	public:
		// void behaviour();
		Feature() : price_(0), radius_(0), damage_(0), shotSpeed_(0), level_(0) {}
		friend class Tower;
		inline int price() const { return price_; }
		inline double radius() const { return radius_; }
		inline double damage() const { return damage_; }
		inline double shotSpeed() const { return shotSpeed_; }
		inline int level() const { return level_; }
		Feature(int level, int price, double raduis, double damage, double shotSpeed);
	};


	class DefaultTower : public Tower {
	protected:
		Strategy* strategy_;
		strategyTypeEnum strategyType_;
	public:
		DefaultTower();
		DefaultTower(Cell*, Feature*, Strategy*, Landscape*);
		DefaultTower(Landscape*);
		void attack();
		void upgrade();
		void fire(Enemy *);
		friend class Strategy;

		inline strategyTypeEnum strategyType() const { return strategyType_;}
	};

	class Strategy {
	public:
		virtual void attack(Tower *) = 0;
		virtual ~Strategy() {}
		static double distance(Enemy*, Building*);
	};

	class NearToTower : public Strategy {
	public:
		void attack(Tower *);
	};

	class NearToCastle : public Strategy {
	public:
		void attack(Tower *);
	};

	class Strong : public Strategy {
	public:
		void attack(Tower *);
	};

	class Weak : public Strategy {
	public:
		void attack(Tower *);
	};

	class Fast : public Strategy {
	public:
		void attack(Tower *);
	};

	class MagicEntity {
	protected:
		Effect* effect;
		std::vector<Enemy*> attached;
		Landscape* land_;
	public:
		void applyEffect(Enemy*);
		virtual ~MagicEntity() {}
	};

	class Trap : Building, MagicEntity {
	public:
		void attack();
		Trap();
		Trap(Landscape*);
		Trap(Landscape*, Cell*, effectTypeEnum, int value, unsigned int time);
	};

	class MagicTower : DefaultTower, MagicEntity {
	public:
		MagicTower();
		MagicTower(Landscape*, Cell*, Feature*, Strategy*, effectTypeEnum, int, unsigned int);
	};
}

