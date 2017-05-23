#ifndef WIRE_H
#define WIRE_H

#include "link.h"

const float WIRE_WIDTH = 3;

class WireLoader {
public:
	WireLoader() {}

	BoxObject load(sgl::Vector position, bool vert, float length) {
		return BoxObject({vert ? sgl::Vector(WIRE_WIDTH, length) : sgl::Vector(length, WIRE_WIDTH)}, position, 11, {0});
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
