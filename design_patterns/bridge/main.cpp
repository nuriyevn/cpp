#include <cstring>
#include "Logger.h"


using namespace std;

int main()
{
	Logger *p = new FileLogger(string("log.txt"));
	p->log(string("message"));
	delete p;
	return 0;
}
