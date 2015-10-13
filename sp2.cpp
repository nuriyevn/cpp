#include <iostream>
#include <memory>

struct C 
{
	int *data;
};

int main()
{
	std::shared_ptr<int>	p1;
	std::shared_ptr<int>	p2(nullptr);
	std::shared_ptr<int>	p3(new int);
	
}
