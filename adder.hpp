#ifndef ADDER_H
#define ADDER_H

#include "link.hpp"

const float ADDER_SIZE = 10;

class AdderLoader {
private:
	const SimpleTexture texture;

public:
	AdderLoader() {}

	BoxObject load(SimpleVector position) {
		return BoxObject(texture, position, 0, {ADDER_SIZE}, {0.6f, 0.3f, 0});
	}

};

class Adder : public Link {
private:
	Link* links [2];
	Use uses [2];

public:
	Adder(BoxObject box) : Link(box) {
		for (int i = 0; i < 2; i++) {
			links[i] = nullptr;
			uses[i] = OFF;
		}
	}

	void use(Use u, Link* prev) {
		for (int i = 0; i < 2; i++) {
			if (links[i] == nullptr)	links[i] = prev;
			if (links[i] == prev) {		uses[i] = u; break; }
		}

		for (int i = 0; i < 2; i++)
			if (uses[i] == OFF) {
				Link::use(uses[!i], this);
				return;
			}

		if (uses[0] == uses[1])	u = YES;
		else							u = NO;

		Link::use(u, this);
	}

};

#endif
