#ifndef  __SHOP_H__
#define __SHOP_H__

#include <iostream>
#include <string>

#include "IObserver.h"

class Shop : IObserver
{
	std::string name;
	float price;
public:
	Shop(std::string n);
	void Update(float price);
};

#endif
