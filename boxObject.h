#ifndef BOX_OBJECT_H
#define BOX_OBJECT_H

#include "simple.h"

class BoxObject {
protected:
	sgl::Vector position;
	sgl::Vector bounds;
	sgl::Sprite* sprite;

	inline void updateSprite() const { sprite->setPosition(position); }

public:
	BoxObject(sgl::Texture texture, sgl::Vector position, int z, sgl::Color color) : position(position), bounds(texture.getBounds()) {
		sprite = new sgl::Sprite(sgl::Sprite::Data(texture).position(position).z(z).color(color));
	}

	BoxObject() {}

	sgl::Vector getPosition() const { return position; }
	void setPosition(sgl::Vector sv) { position = sv; updateSprite(); }

	sgl::Vector getBounds() const { return bounds; }

	virtual void collision(BoxObject* box) {
		sgl::Vector diff = position - box->position;
		sgl::Vector offs = diff.abs() - (bounds + box->bounds)/2;

		if (offs.x <= 0 && offs.y <= 0) {
			if (offs.x > offs.y)	box->position.x -= copysign(offs.x, diff.x);
			else						box->position.y -= copysign(offs.y, diff.y);
		}
	}

};

#endif
