#pragma once
#include "Landscape.h"

using namespace TD;

namespace TD {
	class GameManager //класс над игрой, обеаспечивает запуск ландшафта соответствующего уровня
	{
	private:
		Landscape* landscape;
	public:
		void run();
		GameManager();
		~GameManager();
	};
};