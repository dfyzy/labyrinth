#ifndef TARGET_H
#define TARGET_H

#include "simple.h"

class Target {
private:
	sgl::Sprite* targetSprt;

public:
	Target(sgl::Vector position, sgl::Vector bounds) {
		targetSprt = new sgl::Sprite(bounds, sgl::Data().position(position).color({1}), 5);
		targetSprt->setEnabled(false);
	}

	virtual void targ(bool b) =0;

	void setEnabled(bool b) {
		targetSprt->setEnabled(b);
	}

};

#endif
