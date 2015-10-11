#include <iostream>
#include <ctime>

using namespace  std;
int main	()
{
	time_t now = time(0);
	char *dt = NULL;

	tm *ltm = localtime(&now);
	dt = asctime(ltm); 
	cout << "The local date and time is: " << dt ;
	cout << endl;
	cout << "\nDay = " << ltm->tm_mday 
		 << "\nMonth = " << ltm->tm_mon + 1
		 << "\nYear = " << ltm->tm_year + 1900
		 << "\nHour = " << ltm->tm_hour
		 << "\nMinute = " << ltm->tm_min 
		 << "\nSeconds = "<< ltm->tm_sec << endl; 


	tm *gmtm = gmtime(&now);
	dt = asctime(gmtm);
	cout << "The UTC date time is:" << dt ;
}
