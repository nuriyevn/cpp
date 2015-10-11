#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
	int hr_ = 11;
	int min_ = 3;
	cout << "time is ";
	cout.setw(2);
	cout.setfill('0');

	cout << hr_ << min_ << endl;

	return 0;
}
