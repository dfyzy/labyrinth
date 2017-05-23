#ifndef SWITCH_H
#define SWITCH_H

#include "link.h"
#include "target.h"

const float SWITCH_SIZE = 20;

class SwitchLoader {
public:
	SwitchLoader() {}

	BoxObject load(sgl::Vector position) {
		return BoxObject({SWITCH_SIZE}, position, 0, {1, 0, 0});
	}

};

class Switch : public Link, public Target {
private:
	const bool type;
	bool switched {false};

public:
	Switch(BoxObject box, bool type) : Link(box), Target(position, bounds + sgl::Vector(6)), type(type) {}

	void targ(bool b) {
		Use u = switched ? OFF : (type ? YES : NO);
		switched = !switched;
		use(u, this);
	}

	void collision(BoxObject* box);

};

#endif
