#include <iostream>
#include <vector>

using namespace std;

class Stooge
{
	public:
		static Stooge *make_stooge(int choice);
		virtual void slap_stick() = 0;
};


