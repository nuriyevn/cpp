#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;


void print_vector(vector<int>& my_vector)
{
	vector<int>::iterator it = my_vector.begin();
	for (; it != my_vector.end(); ++it)	
		cout << *it << endl;
}

int main()
{
	vector<int> vec;
	vec.push_back(5);
	vec.push_back(7);

	vector<int>::iterator iter1 = vec.begin();

	*iter1 = 10; // legal;
	++iter1; // legal
	
	cout << *iter1 << endl;

	print_vector(vec);

	// location
	const vector<int>::iterator iter2 = vec.begin();
	*iter2 = 15; // legal
	//	++iter2; // illegal

	// 			  data
	vector<int>::const_iterator iter3 = vec.begin();
	// *iter3 = 15; // illegal
	++iter3;  // legal


	// location         data
	const vector<int>::const_iterator iter4 = vec.begin();
	//*iter4 = 15; // illegal
	//++iter4;  // ilegal 
	// iter4 - actually, is not very useful.

}

