#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;
class Singleton
{
private:
	Singleton() {}
	Singleton( const Singleton&);
	Singleton& operator=(Singleton&);
public:
	static Singleton& getInstance() {
		static Singleton instance;
		return instance;
	}
};

int main()
{	
	Singleton* s = Singleton::getInstance();
	
	
}

