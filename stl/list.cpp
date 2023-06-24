#include <iostream>
#include <list>

using namespace std;

void print(list<int>& l)
{
	cout << "starting to print" << endl;
	for (list<int>::iterator it = l.begin(); it != l.end(); it++)
		cout << *it << endl;
	cout << "end of the print" << endl;
}

int main()
{	
	list<int> my_list; 
	
	my_list.push_back(799);
	my_list.push_back(34);
	print(my_list);	
	my_list.remove(3);
	print(my_list);
	my_list.remove(34);
	print(my_list);
}
