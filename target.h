#ifndef TARGET_H
#define TARGET_H

#include "simple.h"

class Target {
private:
	sgl::Sprite* targetSprt;

public:
	Target(sgl::Vector position, sgl::Vector bounds) {
		targetSprt = new sgl::Sprite(sgl::Sprite::Data(bounds).position(position).z(5).color({1}));
		targetSprt->setEnabled(false);
	}

	virtual void targ(bool b) =0;

	void setEnabled(bool b) {
		targetSprt->setEnabled(b);
	}

};

#endif
