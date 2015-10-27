#ifndef __SWIPECARD_H__
#define __SWIPECARD_H__

#include <iostream>
#include "Manager.h"

using std::cout;
using std::endl;
using std::string;

class Manager;

class SwipeCard
{
public:
	string Swipe(Manager* manager);
	string MakeOfSwipeCard();
};


#endif
