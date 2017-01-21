#ifndef ITEM_H
#define ITEM_H

#include "boxObject.hpp"
#include "target.hpp"

enum Item { LAMP, KEY };

const float ITEM_SIZE = 20;

class ItemLoader {
private:
	const SimpleTexture texture {"assets/items.png"};

public:
	ItemLoader() {}

	BoxObject load(SimpleVector position) {
		return BoxObject(texture, position, 0, {ITEM_SIZE}, {1});
	}
};

class ItemObject : public BoxObject, public Target {
private:
	Item item {KEY};

public:
	ItemObject(BoxObject box) : BoxObject(box), Target(position, bounds) {
		sprite->setTexPosition({ITEM_SIZE, 0});
	}

	void change(Item i) {
		if (i == KEY)	sprite->setTexPosition({ITEM_SIZE, 0});
		else				sprite->setTexPosition({0, 0});
		item = i;
	}

	void targ(bool b);

	void collision(BoxObject* box);

};

#endif
