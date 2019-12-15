/**
\file
This file contains implementation of MagicEntity class
*/

#ifndef _MAGIC_ENTITY_H_
#define _MAGIC_ENTITY_H_

#include "Effect.h"
#include "Table.h"
#include "Enemy.h"

namespace TD {
	/**
	This class provides polymorhism for every entity on the game that can apply magic Effects to Enemies.
	*/
	class MagicEntity {
	protected:
		Effect* effect; ///< A pointer to the Effect this Entity applies on enemies.
		customTemplates::Table<Enemy*> attached; ///< Table of the Enemy pointers on which this MagicEntity has already applied its effects.
	public:
		MagicEntity() :effect(nullptr), attached() {}
		MagicEntity(Effect* eff);
		MagicEntity(Effect* eff, customTemplates::Table<Enemy*> att) :
			effect(eff), attached(att) {}
		inline effectTypeEnum getEffectType() const { return effect->getType(); }

		/**
		Copies the internal Effect of the MagicEntity instance, applies this copy to the Enemy and inserts Enemy pointer to 'attached' table
		\param [in] e A pointer to the Enemy to apply the Effect on
		*/
		void applyEffect(Enemy* e);

		/**
		\return Magnitude of the Effect
		*/
		inline unsigned int getValue() const { return effect->getValue(); }
		inline Effect* getEffect() const { return effect; }

		virtual ~MagicEntity() {}
	};
}

#endif