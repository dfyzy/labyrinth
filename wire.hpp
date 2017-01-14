#ifndef WIRE_H
#define WIRE_H

#include "link.hpp"

const float WIRE_WIDTH = 3;

class WireLoader {
private:
	const SimpleTexture texture;

public:
	WireLoader() {}

	BoxObject load(SimpleVector position, bool vert, float length) {
		return BoxObject(texture, position, 1, vert ? SimpleVector(WIRE_WIDTH, length) : SimpleVector(length, WIRE_WIDTH), {0});
	}

};

class Wire : public Link {
private:

public:
	Wire(BoxObject box) : Link(box) {
		sprite->setEnabled(false);
	}

	void use(Use u, Link* prev) {
		sprite->setEnabled(u != OFF);
		if (u == NO)			sprite->setColor({1, 0, 0});
		else if (u == YES)	sprite->setColor({0, 1, 0});

		Link::use(u, this);
	}

};

#endif
