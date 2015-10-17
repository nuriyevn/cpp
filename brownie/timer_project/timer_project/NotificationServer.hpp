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
		NotifictionStatus() : countdown(20) {};
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
	/*	mNeedStop = false;
		while (!mNeedStop)
		{
			time_t rawtime;
			time(&rawtime);

		}*/
	}

	void stop()
	{
		mNeedStop = true;
	};

private:
	bool mNeedStop;
	CountdownNotification* mCountdownNotification;	
};

class CNotificationServerCallback : public brownie::asynch::LocalCallback<CNotificationServerCallback>
{
public:
	CNotificationSeverCallback(CNotificationServerCallable& callable)
		: mCallable(callable)
	{

	};
	typedef ConcreteNotification<CNotificationServerCallable::CountdownNotification> MyCountdownNotification;
	
	void onStatus(MyCountdownNotificatio& notification)
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
		setNotification(m)
	}

private:

	CNotificationServerCallable& mCallable;
	MyCountdownNotification* mCountdownNotification;	
};




}
}
}


#endif