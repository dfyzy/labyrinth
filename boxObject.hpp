#ifndef BOX_OBJECT_H
#define BOX_OBJECT_H

#include <simpleGL/simpleGL.hpp>

class BoxObject {
protected:
	SimpleVector position;
	SimpleVector bounds;
	SimpleSprite* sprite;

	inline void updateSprite() const { sprite->setPosition(position); }

public:
	BoxObject(const SimpleTexture& texture, SimpleVector position, int z, SimpleVector bounds, SimpleColor color) : position(position), bounds(bounds) {
		sprite = SimpleSprite::Loader(texture).position(position).z(z).texBounds(bounds).color(color).load();
	}

	BoxObject(const SimpleTexture& texture, SimpleVector position, int z, SimpleColor color)
					: BoxObject(texture, position, z, {(float)texture.getWidth(), (float)texture.getHeight()}, color) {}

	BoxObject() {}

	SimpleVector getPosition() const { return position; }
	void setPosition(SimpleVector sv) { position = sv; updateSprite(); }

	SimpleVector getBounds() const { return bounds; }

	virtual void collision(BoxObject* box) {
		SimpleVector diff = position - box->position;
		SimpleVector offs = diff.abs() - (bounds + box->bounds)/2;

		if (offs.x <= 0 && offs.y <= 0) {
			if (offs.x > offs.y)	box->position.x -= copysign(offs.x, diff.x);
			else						box->position.y -= copysign(offs.y, diff.y);
		}
	}

};

#endif
