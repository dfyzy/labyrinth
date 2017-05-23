#ifndef DOOR_H
#define DOOR_H

#include "link.h"
#include "wall.h"
#include "target.h"

const float DOOR_LENGTH = 60;

class DoorLoader {
public:
	DoorLoader() {}

	BoxObject load(sgl::Vector position, bool vert) {
		return BoxObject({vert ? sgl::Vector(WALL_WIDTH, DOOR_LENGTH) : sgl::Vector(DOOR_LENGTH, WALL_WIDTH)}, position, 0, {0, 0, 1});
	}

};

class Door : public Link, public Target {
private:
	bool opened {false};

public:
	Door(BoxObject box) : Link(box), Target(position, bounds + sgl::Vector(6)) {}

	void use(Use u, Link* prev) {
		opened = u == YES;
		if (opened)	sprite->setEnabled(false);
		else			sprite->setEnabled(true);
	}

	void targ(bool b) {
		use(b ? YES : NO, this);
	}

	void collision(BoxObject* box);

};

#endif
