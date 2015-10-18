#ifndef brownie_async_timertest_notificationserver
#define brownie_async_timertest_notificationserver

#include <iostream>
#include <ctime>
#include <Windows.h>

#include "../asynch/LocalCallable.hpp"
#include "../asynch/LocalCallback.hpp"

namespace brownie {
namespace asynch {
namespace timertest {

class CNotificationServerCallable : public brownie::asynch::LocalCallable<CNotificationServerCallable>
{
public:
	CNotificationServerCallable()
		: mCountdownNotification(0)
	{

	}

	// this strcture will store countdown value
	struct NotificationStatus
	{
		NotificationStatus() : countdown(20) {};
		int countdown;
	};

	typedef brownie::asynch::FormalNotification<NotificationStatus> CountdownNotification;

	void handleNotification(CountdownNotification& notification)
	{
		if (mCountdownNotification != 0)
		{
			mCountdownNotification->sendDenotification();
		}
		mCountdownNotification = &notification;
	}

	void handleDenotification(CountdownNotification& notification)
	{
		if (mCountdownNotification != 0)
		{
			mCountdownNotification->sendDenotification();
		}
		mCountdownNotification = 0;
	}

	DWORD start()
	{
		mNeedStop = false;
		mNeedPause = false;
		int cd = 20;

		while (1)
		{
			if (mNeedPause)
				continue;
			if (mNeedStop)
				break;

			if (mCountdownNotification != 0)
			{
				mCountdownNotification->status().countdown = cd;
				mCountdownNotification->sendStatus();
			}
			--cd;
			::Sleep(1000);
		}
		return 0;
	}

	DWORD pause()
	{
		std::cout << "Pausing notifications\n" << std::endl;
		mNeedPause = true;
		return 0;
	}

	DWORD unpause()
	{
		std::cout << "Continuing notifications\n" << std::endl;
		mNeedPause = false;
		return 0;
	}

	void stop()
	{
		mNeedStop = true;
	};

private:
	bool mNeedStop;
	bool mNeedPause;
	CountdownNotification* mCountdownNotification;	
};

class CNotificationServerCallback : public brownie::asynch::LocalCallback<CNotificationServerCallback>
{
public:
	CNotificationServerCallback(CNotificationServerCallable& callable)
		: mCallable(callable)
		, mCountdownNotification(0)
	{

	};
	typedef ConcreteNotification<CNotificationServerCallable::CountdownNotification> MyCountdownNotification;
	
	void onStatus(MyCountdownNotification& notification)
	{
		int countdown = notification.getStatus().countdown;
		std::cout << "Countdown = " << countdown << std::endl;
	}
	void onErrorStatus(MyCountdownNotification& notification)
	{
		std::cout << "Status Error MyCountdownNotification" << std::endl;
	}
	void onDenotification(MyCountdownNotification& notfication)
	{
		std::cout << "Bye MyCountdownNotification" << std::endl;
	}
	void subscribeCountdownNotification()
	{
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "Subscribe to the MyCountdownNotification" << std::endl;
		setNotification(mCountdownNotification, mCallable);

	}
	void unsubscribeCountdownNotification()
	{
		std::cout << "Unsubscribe from the MyCountdownNotification" << std::endl;
		removeNotification(mCountdownNotification);
	}

private:

	CNotificationServerCallable& mCallable;
	MyCountdownNotification* mCountdownNotification;	
};

}
}
}


#endif