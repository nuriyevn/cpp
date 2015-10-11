#include <iostream>
using namespace std;

struct Person
{
	string name() const
	{
		cout << " Person.name()" <<  endl;
	}
};

struct Student : Person
{
	string name() const
	{
		cout << "Student.name()" << endl;
	}
};


int main()
{
	Student s;
	Person &p = s;
	s.name();
	p.name();
}



