#ifndef ITEM_H
#define ITEM_H

#include "boxObject.h"
#include "target.h"

enum Item { LAMP, KEY };

const float ITEM_SIZE = 20;

class ItemLoader {
private:
	sgl::Image* image;

public:
	ItemLoader() {
		image = new sgl::Image("assets/items.png", GL_LINEAR);
	}

	BoxObject load(sgl::Vector position) {
		return BoxObject({image, {}, {ITEM_SIZE}}, position, 0, {1});
	}
};

class ItemObject : public BoxObject, public Target {
private:
	Item item {KEY};

public:
	ItemObject(BoxObject box) : BoxObject(box), Target(position, bounds) {
		sprite->setTexturePosition({ITEM_SIZE, 0});
	}

	void change(Item i) {
		if (i == KEY)	sprite->setTexturePosition({ITEM_SIZE, 0});
		else				sprite->setTexturePosition({0, 0});
		item = i;
	}

	void targ(bool b);

	void collision(BoxObject* box);

};

#endif
