#ifndef DOOR_H
#define DOOR_H

#include "link.hpp"
#include "wall.hpp"
#include "target.hpp"

const float DOOR_LENGTH = 60;

class DoorLoader {
private:
	const SimpleTexture texture;

public:
	DoorLoader() {}

	BoxObject load(SimpleVector position, bool vert) {
		return BoxObject(texture, position, 0, vert ? SimpleVector(WALL_WIDTH, DOOR_LENGTH) : SimpleVector(DOOR_LENGTH, WALL_WIDTH), {0, 0, 1});
	}

};

class Door : public Link, public Target {
private:
	bool opened {false};

public:
	Door(BoxObject box) : Link(box) {}

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
