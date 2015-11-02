#include <iostream>

#include <windows.h>

#include "../asynch/LocalCallable.hpp"
#include "../asynch/LocalCallback.hpp"
#include "../asynch/impl/JobExecutor.cpp"

#include "./thread.hpp"
#include "./NotificationServer_client.hpp"

#include <ctime>

namespace brownie {
namespace asynch {
namespace timertest {

	static CRITICAL_SECTION critSection;
	static CRITICAL_SECTION critSectionLoop;

class JobThread
{
public:
	static JobThread* getInstance()
	{
		::EnterCriticalSection(&critSection);
		if (mInstance == 0)
		{
			mInstance = new  JobThread();
		}
		::LeaveCriticalSection(&critSection);
		return mInstance;
	}
	
	DWORD start()
	{
		mNeedStop = false;
		while (!mNeedStop)
		{
			::EnterCriticalSection(&critSectionLoop);
			brownie::asynch::JobExecutor::getInstance()->run();
			::LeaveCriticalSection(&critSectionLoop);
			::Sleep(100);
		}

		return 0;
	}

	void stop()
	{
		mNeedStop = true;
	}
private:
	JobThread() : mNeedStop(false) {};
	JobThread(const JobThread& T) {};
	JobThread& operator=(const  JobThread& T) {};
	static JobThread *mInstance;
	bool mNeedStop;
};

JobThread *JobThread::mInstance = 0;
}
}
}

using namespace brownie::asynch::timertest;

int main(int argc, char *argv[])
{
	srand(time(NULL));
	std::cout << "--------------Super mega timer Using brownie with brain------------" << std::endl;
	
	::InitializeCriticalSection(&brownie::asynch::timertest::critSection);
	::InitializeCriticalSection(&brownie::asynch::timertest::critSectionLoop);
		
	Thread<JobThread> thread(JobThread::getInstance(), &JobThread::start);
	if (thread.start())
	{
		CNotificationServerCallable server_notification;   // server notification
		CNotificationClientCallback client_notification(server_notification); // client notification

		Thread<CNotificationServerCallable> callable_thread(&server_notification, &CNotificationServerCallable::start);
		if (callable_thread.start())
		{
			client_notification.subscribeCountdownNotification();
			int expected_total_run_ms = 15740;
			int elapsed_run_ms = 0;
			int run_ms = 0;
			int pause_ms = 0;

			client_notification.startTimerFromClient(expected_total_run_ms);

			while (1)
			{
				run_ms = rand() % 3000 + 3000;

				if (run_ms + elapsed_run_ms > expected_total_run_ms)
					run_ms = expected_total_run_ms - elapsed_run_ms;

				std::cout << "Will run for (" << run_ms << ") milliseconds" << std::endl;
				
				Sleep(run_ms);
				elapsed_run_ms += run_ms;

				if (elapsed_run_ms >= expected_total_run_ms)
					break;

				pause_ms = rand() % 2500 + 1000;
				client_notification.pauseTimerFromClient(pause_ms);
				Sleep(pause_ms);

				client_notification.unpauseTimerFromClient();
			}
			client_notification.unsubscribeCountdownNotification();
		}
	}

	brownie::asynch::timertest::JobThread::getInstance()->stop();
	thread.join();

	system("PAUSE");
	return 0;	
}
