#ifndef LINK_H
#define LINK_H

#include "boxObject.hpp"

class Link : public BoxObject {
protected:
	std::list<Link*> links;

public:
	enum Use { YES, NO, OFF };

	Link(BoxObject box) : BoxObject(box) {}

	Link* connect(Link* link) { links.push_back(link); return this; }

	virtual void use(Use u, Link* prev) {
		for (auto& l : links) l->use(u, this);
	}

};

#endif
