#ifndef _MAGIC_ENTITY_H_
#define _MAGIC_ENTITY_H_

#include "Effect.h"
#include "Table.h"
#include "Enemy.h"

namespace TD {
	class MagicEntity {
	protected:
		Effect* effect;
		customTemplates::Table<Enemy*> attached;
	public:
		MagicEntity() :effect(nullptr), attached() {}
		MagicEntity(Effect* eff);
		MagicEntity(Effect* eff, customTemplates::Table<Enemy*> att) :
			effect(eff), attached(att) {}
		inline effectTypeEnum getEffectType() const { return effect->getType(); }
		void applyEffect(Enemy*);

		virtual ~MagicEntity() {}
	};
}

#endif