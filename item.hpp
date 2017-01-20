#ifndef ITEM_H
#define ITEM_H

#include "boxObject.hpp"
#include "target.hpp"

enum Item { LAMP, KEY };

const float ITEM_SIZE = 10;

class ItemLoader {
private:
	const SimpleTexture texture;

public:
	ItemLoader() {}

	BoxObject load(SimpleVector position) {
		return BoxObject(texture, position, 0, {ITEM_SIZE}, {0, 0, 1});
	}
};

class ItemObject : public BoxObject, public Target {
private:
	Item item {KEY};

public:
	ItemObject(BoxObject box) : BoxObject(box) {}

	void change(Item i) {
		if (i == KEY)	sprite->setColor({0, 0, 1});
		else				sprite->setColor({0.6f, 0.5f, 0});
		item = i;
	}

	void targ(bool b);

	void collision(BoxObject* box);

};

#endif
