#include "pch.h"
#include "MagicEntity.h"

#include <stdexcept>

namespace TD {
	MagicEntity::MagicEntity(Effect* eff) {
		if (!eff) throw std::invalid_argument("effect nullptr");
		effect = eff;
	}

	void MagicEntity::applyEffect(Enemy* e) {
		auto findRes = attached.find(e);
		if (findRes == attached.end()) {
			Effect* n = effect->copy();
			e->addEffect(n);
		}
	}
}
