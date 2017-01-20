#ifndef WALL_LOADER_H
#define WALL_LOADER_H

#include "boxObject.hpp"

const float WALL_WIDTH = 13;//temp

class WallLoader {
private:
	const SimpleTexture texture;

public:
	WallLoader() {}

	BoxObject load(SimpleVector position, bool vert, float length) {
		return BoxObject(texture, position, 0, vert ? SimpleVector(WALL_WIDTH, length) : SimpleVector(length, WALL_WIDTH), {0.2f});
	}

};

#endif
