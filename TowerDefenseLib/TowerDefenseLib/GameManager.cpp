#include "pch.h"
#include "GameManager.h"

#include "..//..//..//labs3sem/labslib/labslib.h"

using namespace TD;

using namespace labslib;

namespace TD {
	GameManager::GameManager() {
		print("cnhoose level");
		int n;
		input(n);
		landscape = new Landscape(n);
	}
}
