#include <iostream>
#include <ctime>
#include <signal.h>
// is not tested thoroughly
#if __cplusplus >= 201103L || (defined(_MSC_VER) && _MSC_VER >= 1900)
   #define cpp11plus
   #include <chrono>
   #include <thread>
#else
   #ifdef _WIN32
   #include <Windows.h>
   #endif
   #ifdef linux
   #include <unistd.h>
   #endif
#endif

using namespace  std;

static volatile int keepRunning = 1;

void intHandler(int dummy)
{
   keepRunning = 0;
   cout << ("SIGINT catched. Exiting...\n");
}

inline void SLEEP(int seconds)
{
   int milliseconds = seconds * 1000;

   #ifdef cpp11plus
      std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
   #else
      #ifdef _WIN32
      Sleep(milliseconds);
      #elif linux
      sleep(seconds);
      #endif
   #endif
}

int main	()
{
   signal(SIGINT, intHandler);
   int seconds = 1;

   while (keepRunning)
   {
      SLEEP(seconds);
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
