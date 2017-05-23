#ifndef WALL_LOADER_H
#define WALL_LOADER_H

#include "boxObject.h"

const float WALL_WIDTH = 13;//temp

class WallLoader {
private:
	const sgl::Image* image;

public:
	WallLoader() {}

	BoxObject load(sgl::Vector position, bool vert, float length) {
		return BoxObject({vert ? sgl::Vector(WALL_WIDTH, length) : sgl::Vector(length, WALL_WIDTH)}, position, 10, {0.2f});
	}

};

#endif
