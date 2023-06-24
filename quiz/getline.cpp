#include <cstring>
#include <iostream>

using namespace std;

int main()
{
	string name[2];
	int age[2];
	cout << "Please input the age and the name of the first animal line by line." << endl;

	cin >> age[0];
	cin.get(); // after "cin >>" operator, newline symbol left on the input, we delete it.
	getline(cin, name[0]);


	cout << "PLease input the age and the name of the second animal line by line" << endl;	
	cin >> age[1];
	cin.get(); //
	getline(cin, name[1]);
		
	for (int i = 0; i < 2; i++)
	{
		cout << "Name: " << name[i] << "; age: " << age[i] << endl;
	}	
}
