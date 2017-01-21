#ifndef SWITCH_H
#define SWITCH_H

#include "link.hpp"
#include "target.hpp"

const float SWITCH_SIZE = 20;

class SwitchLoader {
private:
	const SimpleTexture texture;

public:
	SwitchLoader() {}

	BoxObject load(SimpleVector position) {
		return BoxObject(texture, position, 0, {SWITCH_SIZE}, {1, 0, 0});
	}

};

class Switch : public Link, public Target {
private:
	const bool type;
	bool switched {false};

public:
	Switch(BoxObject box, bool type) : Link(box), Target(position, bounds + SimpleVector(6)), type(type) {}

	void targ(bool b) {
		Use u = switched ? OFF : (type ? YES : NO);
		switched = !switched;
		use(u, this);
	}

	void collision(BoxObject* box);

};

#endif
