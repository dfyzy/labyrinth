#ifndef PLAYER_H
#define PLAYER_H

#include "map.hpp"

const float PLAYER_SPEED = 3.5f;

class Player : public BoxObject {
private:
	Map* map;

public:
	Player(BoxObject box, Map* map) : BoxObject(box), map(map) {}

	Player() {}

	void update(SimpleVector delta) {
		position += delta*PLAYER_SPEED;
		map->collision(this);
		updateSprite();
		simpleGL::setCameraPosition(position);
	}

};

#endif
