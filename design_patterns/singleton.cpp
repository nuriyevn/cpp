#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

class Singleton
{
private:
	static Singleton * p_instance;
	Singleton() {}
	Singleton( const Singleton& );
	Singleton& operator=(Singleton&);
public:
	static Singleton * getInstance() {
		if (!p_instance)
		{
			cout << "Creating object" << endl;
			p_instance = new Singleton();
		}
		else
			cout << "Object is already created" << endl;
		return p_instance;
	}
};

Singleton *Singleton::p_instance = 0;

int main(int argc, char *argv[])
{
	Singleton* obj = Singleton::getInstance();	
	Singleton* obj2 = Singleton::getInstance();
	Singleton* obj3 = Singleton::getInstance();
	cout << "size of obj = " << sizeof(obj) << endl;
	
	cout << "obj = " << (unsigned long long int)obj;
	cout << "obj2 = " << (unsigned long long int)obj2; 
	cout << "obj3 = " << (unsigned long long int)obj3;  

	delete obj;	

}
