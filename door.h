#ifndef DOOR_H
#define DOOR_H

#include "link.h"
#include "target.h"

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
