#include "GraphicsCell.h"

void GraphicsCell::update() {
	switch (spectationCell->getType()) {
	case cellTypeEnum::field: {
		Field* f = dynamic_cast<Field*>(spectationCell);
		setBuilding(f->getTower());
		if (spectationBuilding) {
			switch (spectationBuilding->getType()) {
			case buildingTypeEnum::tower: {
				Tower* t = dynamic_cast<Tower*>(spectationBuilding);
				setRepr(t->getLevel() + 96);
				break;
			}
			case buildingTypeEnum::magicTower: {
				MagicTower* m = dynamic_cast<MagicTower*>(spectationBuilding);
				setRepr(m->getLevel() + 64);
				switch (m->getEffectType()) {
				case effectTypeEnum::poison:
					setTxtColor(LightGreen);
					break;
				case effectTypeEnum::slowdown:
					setTxtColor(LightBlue);
					break;
				case effectTypeEnum::weakness:
					setTxtColor(Magenta);
					break;
				}
			}
			}
		}
		else {
			setRepr('.');
			setTxtColor(Yellow);
		}
		break;
	}
	case cellTypeEnum::forest: {
		setRepr('^');
		setTxtColor(Green);
		break;
	}
	case cellTypeEnum::road: {
		Road* r = dynamic_cast<Road*>(spectationCell);
		setBuilding(r->getBuilding());
		if (spectationBuilding) {
			switch (spectationBuilding->getType()) {
			case buildingTypeEnum::castle:
				setRepr('@');
				setTxtColor(White);
				break;
			case buildingTypeEnum::lire:
				setRepr('*');
				setTxtColor(Red);
				break;
			case buildingTypeEnum::trap: {
				setRepr('+');
				Trap* t = dynamic_cast<Trap*>(spectationBuilding);
				switch (t->getEffectType()) {
				case effectTypeEnum::poison:
					setTxtColor(LightGreen);
					break;
				case effectTypeEnum::weakness:
					setTxtColor(Magenta);
					break;
				case effectTypeEnum::slowdown:
					setTxtColor(LightBlue);
					break;
				}
				break;
			}
			}
		}
		setRepr('=');
		setTxtColor(LightGray);
		break;
	}
	}
}
