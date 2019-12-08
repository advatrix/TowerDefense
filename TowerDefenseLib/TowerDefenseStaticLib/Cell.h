#ifndef _CELL_H_
#define _CELL_H_


#include <stdexcept>

#include "Enums.h"
#include "Building.h"
#include "Castle.h"
#include "Tower.h"

namespace TD {
		class Cell {
		protected:
			int x;
			int y;
		public:
			virtual inline cellTypeEnum getType() const { return cellTypeEnum::forest; }
			Cell();
			Cell(int, int);
			virtual void destroy() {}
			virtual ~Cell() {}
			std::pair<double, double> cords() const;
		};


		class Road : public Cell {
		private:
			Building* building;

			Road* west;
			Road* east;
			Road* north;
			Road* south;
			Road* next;

			unsigned int dist;

			static void makeWestEastNeighbours(Road* west, Road* east);
			static void makeNorthSouthNeighbours(Road* north, Road* south);

			void clearPath();
			void becomeDestination();
			void growPathTo(Road* neighbour);
			Road* growPathToNeighbour(Road* neighbour);

			inline Road* growPathNorth() { return growPathToNeighbour(north); }
			inline Road* growPathSouth() { return growPathToNeighbour(south); }
			inline Road* growPathWest() { return growPathToNeighbour(west); }
			inline Road* growPathEast() { return growPathToNeighbour(east); }
		public:
			void build(Building*);
			void destroy() throw (std::exception);
			inline bool isBuilt() { return building; }
			~Road();
			Road();
			Road(int, int);
			inline unsigned int getDist() const { return dist; }
			inline bool hasPath() const { return dist != std::numeric_limits<unsigned>::max(); }
			inline Building* getBuilding() const { return building; }
			friend class Landscape;
			friend class Road;

			inline cellTypeEnum getType() const { return cellTypeEnum::road; }

			inline Road* getNext() const { return next; }
		};

		class Field : public Cell {
		private:
			Tower* tower;
		public:
			void build(Tower*) throw (std::invalid_argument);
			Field();
			Field(int i, int j);
			~Field();
			void destroy();
			inline bool isBuilt() { return tower; }
			inline Tower* getTower() const { return tower; }

			inline cellTypeEnum getType() const { return cellTypeEnum::field; }
		};
}

#endif

