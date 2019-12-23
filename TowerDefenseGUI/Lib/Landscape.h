/**
\file
This file contains implementation of the Landscape class
*/
#ifndef _LANDSCAPE_H_
#define _LANDSCAPE_H_

#include "pch.h"

#include <vector>

#include "Table.h"

#include "Cell.h"
#include "Enemy.h"

namespace ct = customTemplates;

namespace TD {
	/**
	This class describes the state of the current level map
	*/
	class Landscape {
	private:
		std::vector<std::vector<Cell*>> cells; ///< Two-dimensional vector of Cell pointers describing the map
		unsigned int height; ///< Height of the map in cells
		unsigned int width; ///< Width of the map in cells

		ct::Table<Enemy*>* enemyTable; ///< Table of every Enemy on the map

		/**
		Calculates the direction of Enemy movement and moves the Enemy
		\param [in] e Pointer to the Enemy to move
		*/
		void moveEnemy(Enemy* e); 

		Castle* castle_; ///< A pointer to the Castle
		
	public:
		Landscape() : cells(), height(0), width(0), enemyTable(), castle_(nullptr) {}
		Landscape(std::vector<std::vector<Cell*>>& _cells);
		Landscape(std::vector<std::vector<Cell*>>& _cells, ct::Table<Enemy*>* et);

		inline unsigned int getHeight() const { return height; }
		inline unsigned int getWidth() const { return width; }

		Cell* getCell(int i, int j) const;
		ct::Table<Enemy*>* getEnemyTable() const { return enemyTable; }

		~Landscape();

		void update();
		
		/**
		Sets a new pointer to the Castle
		\param [in] c New pointer to the Castle
		*/
		inline void setCastle(Castle* c) { castle_ = c; }
		inline Castle* getCastle() const { return castle_; }

		/**
		Returns two-dimensional vector of the Cell pointers describing cuurent map state
		\return two-dimensional vector of the Cell pointers
		*/
		inline std::vector<std::vector<Cell*>> getCells() const { return cells; }

		/**
		Creates all possible pathes from every Lire on the Landscape to the Castle.
		\return Flag showing whether path creating was successfull (true) or not (false).
		*/
		bool createPath();
	};

}

#endif
