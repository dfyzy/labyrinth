#ifndef PERSON_LOADER_H
#define PERSON_LOADER_H

#include "boxObject.hpp"

const float PERSON_SIZE = 20;

class PersonLoader {
private:
	const SimpleTexture texture {"assets/circle.png"};

public:
	PersonLoader() {}

	BoxObject load(SimpleVector position) {
		return BoxObject(texture, position, 0, {PERSON_SIZE}, {1});
	}

};

#endif
