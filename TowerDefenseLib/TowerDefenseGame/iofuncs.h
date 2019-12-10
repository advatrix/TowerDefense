#pragma once

#include <iostream>

namespace IOFuncs {
	template<class T>
	void print(T a) {
		std::cout << a << std::endl;
	}

	template <class T>
	int input(T& a) {
		int r = 0;
		do {
			std::cin >> a;
			if (std::cin.eof()) {
				std::cin.clear();
				return -1;
			}
			if (!std::cin.good()) {
				std::cin.clear();
				while (std::cin.get() != '\n');
				r++;
			}
			else r = 0;
		} while (r);
		return r;
	}
}