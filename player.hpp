#ifndef PLAYER_H
#define PLAYER_H

#include "map.hpp"
#include "item.hpp"

const float PLAYER_SPEED = 3.5f;

class Player : public BoxObject {
private:
	Map* map;
	SimpleLight::Source* lamp;
	Item own {LAMP};

public:
	Player(BoxObject box, Map* map) : BoxObject(box), map(map) {
		lamp = map->torch({}, 300);
	}

	Player() {}

	Item getOwn() const { return own; }

	void setOwn(Item i) {
		lamp->setEnabled(i == LAMP);
		own = i;
	}

	void update(SimpleVector delta) {
		position += delta*PLAYER_SPEED;
		map->collision(this);
		updateSprite();
		lamp->setPosition(position);
		simpleGL::setCameraPosition(position);
	}

};

#endif
