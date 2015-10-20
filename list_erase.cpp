#include <iostream>
#include <list>

int main()
{
	std::list<int> mylist;
	std::list<int>::iterator it1, it2;

	for (int i = 1; i < 10; ++i)
		mylist.push_back(i*10);

	it1 = it2 = mylist.begin();
	advance(it2, 6);
	++it1;

	it1 = mylist.erase(it1);

	it2 = mylist.erase(it2);

	++it1;
	--it2;

	mylist.erase(it1, it2);

	std::cout << "mylist contains:";

	for (it1 = mylist.begin(); it1 != mylist.end(); ++it1)
	{
		std::cout << ' ' << *it1;
	}
	std::cout << '\n';

	return 0;
}
