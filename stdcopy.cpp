#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
	int myints[] = {10, 20, 30, 40, 50};
	vector<int> v(5);
	copy(myints, myints + 5, v.begin());
	
	for (auto it = v.begin(); it != v.end(); ++it)
		cout << " " << *it;
	cout << endl;	
};
