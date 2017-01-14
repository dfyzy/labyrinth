#ifndef SWITCH_H
#define SWITCH_H

#include "link.hpp"

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

class Switch : public Link {
private:
	const bool type;
	bool switched {false};

public:
	Switch(BoxObject box, bool type) : Link(box), type(type) {}

	void use() {
		Use u = switched ? OFF : (type ? YES : NO);
		switched = !switched;
		Link::use(u, this);
	}

};

#endif
