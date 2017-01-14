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
		sprite = SimpleSprite::Loader(texture).position(position).z(z).bounds(
																							bounds/SimpleVector(texture.getWidth(), texture.getHeight())
																						).color(color).load();
	}

	BoxObject(const SimpleTexture& texture, SimpleVector position, int z, SimpleColor color)
					: BoxObject(texture, position, z, {(float)texture.getWidth(), (float)texture.getHeight()}, color) {}

	SimpleVector getPosition() const { return position; }
	void setPosition(SimpleVector sv) { position = sv; updateSprite(); }

	SimpleVector getBounds() const { return bounds; }

};

#endif
