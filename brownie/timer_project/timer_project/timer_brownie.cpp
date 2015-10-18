#include <iostream>

#include <windows.h>

#include "../asynch/LocalCallable.hpp"
#include "../asynch/LocalCallback.hpp"
#include "../asynch/impl/JobExecutor.cpp"

#include "./thread.hpp"
#include "./NotificationServer.hpp"

namespace brownie {
namespace asynch {
namespace timertest {

	static CRITICAL_SECTION critSection;
	static CRITICAL_SECTION critSectionLoop;

class CNotificationClientThread
{
public:
	static CNotificationClientThread* getInstance()
	{
		::EnterCriticalSection(&critSection);
		if (mInstance == 0)
		{
			mInstance = new  CNotificationClientThread();
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
	CNotificationClientThread() : mNeedStop(false) {};
	CNotificationClientThread(const CNotificationClientThread& T) {};
	CNotificationClientThread& operator=(const  CNotificationClientThread& T) {};
	static CNotificationClientThread *mInstance;
	bool mNeedStop;
};

CNotificationClientThread *CNotificationClientThread::mInstance = 0;
}
}
}

using namespace brownie::asynch::timertest;

int main(int argc, char *argv[])
{
	std::cout << "--------------Super mega timer Using brownie with brain------------" << std::endl;
	
	::InitializeCriticalSection(&brownie::asynch::timertest::critSection);
	::InitializeCriticalSection(&brownie::asynch::timertest::critSectionLoop);
		
	Thread<CNotificationClientThread> thread(CNotificationClientThread::getInstance(), &CNotificationClientThread::start);
	if (thread.start())
	{
		CNotificationServerCallable callable_notification;
		CNotificationServerCallback callback_notification(callable_notification);

		Thread<CNotificationServerCallable> callable_thread(&callable_notification, &CNotificationServerCallable::start);
		if (callable_thread.start())
		{
			callback_notification.subscribeCountdownNotification();
			Sleep(10000);
			callable_notification.pause();
			Sleep(3000);
			callable_notification.unpause();
			Sleep(10000);
			callback_notification.unsubscribeCountdownNotification();
		}
	}

	brownie::asynch::timertest::CNotificationClientThread::getInstance()->stop();
	thread.join();

	system("PAUSE");
	return 0;	
}
