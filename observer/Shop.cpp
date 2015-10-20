#include "Shop.h"

Shop::Shop(std::string name)
{
	this->name = name ;
}

void Shop::Update(float price)
{
	this->price = price;
	std::cout << "Price at " << name << " is now " <<  price << "\n";
}


