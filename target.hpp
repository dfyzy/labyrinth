#ifndef TARGET_H
#define TARGET_H

#include <simpleGL/simpleGL.hpp>

class Target {
private:
	SimpleSprite* targetSprt;

public:
	Target(SimpleVector position, SimpleVector bounds) {
		targetSprt = SimpleSprite::Loader({}).position(position).z(5).texBounds(bounds).color({1}).load();
		targetSprt->setEnabled(false);
	}

	virtual void targ(bool b) =0;

	void setEnabled(bool b) {
		targetSprt->setEnabled(b);
	}

};

#endif
