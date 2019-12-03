#ifndef _ENTITY_H_
#define _ENTITY_H_

namespace TD {
	class Entity {
	public:
		virtual void update() = 0;
		virtual ~Entity() {}
	};
}

#endif

