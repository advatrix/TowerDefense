#pragma once
#include "Landscape.h"

using namespace TD;

namespace TD {
	class GameManager //����� ��� �����, ������������� ������ ��������� ���������������� ������
	{
	private:
		Landscape* landscape;
	public:
		void run();
		GameManager();
		~GameManager();
	};
};