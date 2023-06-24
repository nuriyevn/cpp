#include <iostream>

class fourwheeler
{
public:
	int category;
	int eurolevel;
	int getCategory(void);
	char getEuroLevel(void);
};

inline int fourwheeler::getCategory(void)
{
	return category;
};

inline char fourwheeler::getEuroLevel(void)
{
	return eurolevel;
};



class car : public fourwheeler
{
public:
	char *brand;
	char *model;
	char *getBrand(void);
	char *getModel(void);
};

int main(void)
{
	car obj_car;
	obj_car.category = 1;
	obj_car.eurolevel = 3;

	std::cout << "\n The fourwheeler category is"
			<< obj_car.category;
	std::cout << "\n The fourwheeler eurolevel is"				<< obj_car.eurolevel;
	return 0;
}

