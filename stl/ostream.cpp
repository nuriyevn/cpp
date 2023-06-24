#include <fstream>
#include <iostream>
#include <cstdlib>
using namespace std;

int main()
{
	fstream f;
	f.open("/tmp/test.txt", fstream::in | fstream::out);
	
	f << "Test" << endl;
	
	f.close();

}
