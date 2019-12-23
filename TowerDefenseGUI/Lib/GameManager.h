/**
This file contains implementation of the GameManager class
*/

#pragma warning(disable:4996)

#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_


#include "Table.h"
#include "Landscape.h"
#include "Entity.h"

namespace ct = customTemplates;

namespace TD {
	/**
	This class rules all game entities, enemies and cells
	*/
	class GameManager {
	private:
		unsigned int level; ///< Level name of the current map, according to this in config file
		Landscape* landscape; ///< Pointer to Landscape instance that describes map state
		std::vector<Feature*> features; ///< Vector of pointers to every possible Feature towers can have
		std::vector<Strategy*> strategies; ///< Vector of pointers to every possible Strategy towers can have

		std::vector<Entity*> entities; ///< Vector of pointers to every Entity of the game which updates every tick

		size_t internalTime; ///< Number of turns since tha game started
	public:
		/**
		Creates new game session loading the level by its number.
		\param [in] level Number of the level to load
		*/
		void load(unsigned int level);

		/**
		Continues game session loading its state by the name of the save directory.
		\param [in] filename Name of the save to load
		*/
		void load(std::string filename);

		/**
		Function that updates game state
		*/
		void update();
		GameManager(unsigned int _level) {
			load(_level);
			level = _level;
		}

		GameManager(std::string fname) {
			load(fname);
			level = 0;
		}

		GameManager(): features(), strategies(), entities() {
			landscape = nullptr;
			level = 0;
			internalTime = 0;
		}

		~GameManager();

		/**
		Upgrades any Tower of MagicTower, changing its Feature to the next one if possible
		\param [in] i X cord of the Tower to upgrade
		\param [in] j Y cord of the Tower to upgrade
		*/
		void upgrade(int i, int j);

		/**
		Destroys any Building if possible.
		\warning It cannot destroy Castle or Lire.
		\param [in] i X cord of the Building to destroy
		\param [in] j Y cord of the Building to destroy
		*/
		void destroy(int i, int j);

		/**
		Saves current state of the game to config files in a corresponding directory.
		*/
		void save();

		

		

		/**
		Builds a Tower
		\warning This function doesn't build Magic towers
		\param [in] i X cords of the Cell to build the Tower on
		\param [in] j Y cords of the Cell to build the Tower on
		\param [in] level Level of the Feature to apply to the Tower
		*/
		void buildTower(int i, int j, unsigned int level);

		/**
		Builds a MagicTower
		\param [in] i X cords of the Cell to build the MagicTower on
		\param [in] j Y cords of the Cell to build the MagicTower on
		\param [in] level Level of the Feature to apply to the MagicTower
		\param [in] effType Type of the Effect MagicTower has according to effectTypeEnum
		\param [in] value Magnitude of the Effect
		\param [in] time Remaining time of the Effect
		*/
		void buildMagicTower(int i, int j, unsigned int level, effectTypeEnum effType, unsigned int value, unsigned int time);

		/**
		Builds a Trap
		\param [in] i X cord of the Cell to build the Trap on
		\param [in] j Y cord of the Cell to build the Trap on
		\param [in] effType Type of the Effect MagicTower has according to effectTypeEnum
		\param [in] value Magnitude of the Effect
		\param [in] time Remaining time of the Effect
		*/
		void buildTrap(int i, int j, effectTypeEnum effType, unsigned int value, unsigned int time);
		
		/**
		Returns table of the enemies on the landscape.
		\return Pointer to the table of Enemy pointers from the landscape
		*/
		inline ct::Table<Enemy*>* getEnemyTable() const { return landscape->getEnemyTable(); }

		/**
		Returns current hit points of the Castle.
		\return current hit points of the Castle.
		*/
		inline double getHp() const { return landscape->getCastle()->getCurHp(); }

		/**
		Returns current money balance of the Castle
		\return current money balance of the Castle
		*/
		inline int getMoney() const { return landscape->getCastle()->getMoney(); }

		/**
		Returns two-dimensional vector of Cell pointers describing current level tile state
		/return two-dimensional vector of Cell pointers
		*/
		inline std::vector<std::vector<Cell*>> getCells() const { return landscape->getCells(); }

		inline size_t getTime() const { return internalTime; }

		inline Feature* getFeature(size_t level) const { return features[level]; }

		inline void setStrategy(int i, int j, strategyTypeEnum s);

		inline Castle* getCastle() const { return landscape->getCastle(); }

	};
}



#endif