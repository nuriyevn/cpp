#include <cstdio>
#include <iostream>

#include "DummyProduct.h"
#include "Shop.h"

int main()
{
	std::cout << "Starting program" << std::endl;

	DummyProduct product;
	// We have four shops wanting to keep updated price set by product owner
	Shop shop1("Shop 1");
	Shop shop2("Shop 2");

	product.Attach(&shop1);
	product.Attach(&shop2);


	product.ChangePrice(23.0f);
	product.Detach(&shop2);

	product.ChangePrice(26.0f);
	return 0;
}



