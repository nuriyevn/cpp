#include <iostream>
#include <ctime>
#include <unistd.h>
#include <signal.h>

using namespace  std;

static volatile int keepRunning = 1;

void intHandler(int dummy)
{
   keepRunning = 0;
   cout << ("SIGINT catched. Exiting...\n");
}

int main	()
{
   signal(SIGINT, intHandler);

   while (keepRunning)
   {
      sleep(1);
      time_t now = time(0);
      char *dt = NULL;
      cout << "\n" << now << " seconds elapsed since Unix Epoch" << endl; 
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
}
