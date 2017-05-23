#ifndef PERSON_LOADER_H
#define PERSON_LOADER_H

#include "boxObject.h"

const float PERSON_SIZE = 20;

class PersonLoader {
private:
	sgl::Image* image;

public:
	PersonLoader() {
		image = new sgl::Image("assets/circle.png", GL_LINEAR);
	}

	BoxObject load(sgl::Vector position) {
		return BoxObject({image}, position, 0, {0.5f});
	}

};

#endif
