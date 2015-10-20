#ifndef ASUBJECT_HEADER__
#define ASUBJECT_HEADER__

#include <vector>
#include <list>
#include "shop.h"


class ASubject
{
	std::vector<Shop*> list;
public:
	void Attach(Shop *product);
	void Detach(Shop *product);
	void Notify(float price);
};


#endif
