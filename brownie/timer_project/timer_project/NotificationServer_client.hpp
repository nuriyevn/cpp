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
		: mCountdownNotification(0), mNeedStop(false), mNeedPause(false), mMaxTimer(0),
		mCurTimer(0)
	{
	}

	// this strcture will store countdown value
	struct NotificationStatus
	{
		NotificationStatus() {};
		int MaximumTimer;
		int CurrentTimer;
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

	struct StartCallArgument
	{
		StartCallArgument() : maxTimer(0), curTimer(0)	
		{
		}
		int maxTimer;
		int curTimer;
	};

	struct PauseCallArgument
	{
		PauseCallArgument() : pause_duration_ms(0)
		{
		}
		int pause_duration_ms;
	};

	struct UnpauseCallArgument
	{
		UnpauseCallArgument()
		{
		}
		int empty;
	};

	struct IsFinishedCallArgument
	{
		IsFinishedCallArgument()
		{
		}
		int empty;
	};

	struct IsFinishedCallResult
	{
		IsFinishedCallResult() : flag(false) {};
		bool flag;
	};
	
	typedef brownie::asynch::FormalOperationCall<StartCallArgument> StartCall;
	typedef brownie::asynch::FormalOperationCall<PauseCallArgument> PauseCall;
	typedef brownie::asynch::FormalOperationCall<UnpauseCallArgument> UnpauseCall;
	typedef brownie::asynch::FormalOperationCall<IsFinishedCallArgument, IsFinishedCallResult> IsFinishedCallWithResult;
	
	// startTimerFromClient handling
	void handleCall(StartCall& call)
	{
		mMaxTimer = call.getArgument().maxTimer;
		mNeedPause = false;
		call.sendResult();
	}
	// pauseTimerFromClient handling
	void handleCall(PauseCall& call)
	{
		mNeedPause = true;
		call.sendResult();
	}

	// unpauseTimerFromClient handling
	void handleCall(UnpauseCall& call)
	{
		mNeedPause = false;
		call.sendResult();
	}

	void handleCall(IsFinishedCallWithResult& call)
	{
		call.result().flag = mNeedStop;
		call.sendResult();
	}
	
	DWORD start()
	{
		mNeedStop = false;
		mNeedPause = false;
	
		while (1)
		{
			if (mNeedPause)
				continue;
			if (mNeedStop)
				break;

			if (mCountdownNotification != 0)
			{
				mCountdownNotification->status().MaximumTimer = mMaxTimer;
				mCountdownNotification->status().CurrentTimer = mCurTimer;
				mCountdownNotification->sendStatus();
						
				if (mCurTimer >= mMaxTimer)
				{
					mNeedStop = true;
				}
				mCurTimer += 500;
			}
			
			::Sleep(500);
		}
		return 0;
	}

	void stop()
	{
		mNeedStop = true;
	};

private:
	bool mNeedStop;
	bool mNeedPause;
	int mMaxTimer;
	int mCurTimer;
	CountdownNotification* mCountdownNotification;	
};

class CNotificationClientCallback : public brownie::asynch::LocalCallback<CNotificationClientCallback>
{
public:
	CNotificationClientCallback(CNotificationServerCallable& callable)
		: mCallable(callable)
		, mCountdownNotification(0)
		, mFinished(false)
	{

	};

	//---------NOTIFICATION STUFF--------------------
	typedef ConcreteNotification<CNotificationServerCallable::CountdownNotification> MyCountdownNotification;
	void onStatus(MyCountdownNotification& notification)
	{
		int local_maxTimer = notification.getStatus().MaximumTimer;
		int local_curTimer = notification.getStatus().CurrentTimer;

		std::cout << "Countup = " << local_maxTimer << " out of " << local_curTimer << std::endl;
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
	//---------------------------------------------------


	// STARTING TIMER FUNCTIONS
	typedef ConcreteOperationCall<CNotificationServerCallable::StartCall> MyStartCall;
	void onResult(MyStartCall& call)
	{
		//std::cout << "onResult(MyStartCall&)" << std::endl;

	}
	void onError(MyStartCall& call)
	{
		//std::cout << "onError(MyStartCall&)" << std::endl;
	}
	void startTimerFromClient(int total_run_ms)
	{
		MyStartCall *pCall;
		if (createCall(pCall))
		{
			pCall->argument().curTimer = 0;
			pCall->argument().maxTimer = total_run_ms;
			pCall->sendTo(mCallable);
		}

		//Sleep(10);
		std::cout << "Client: called startTimerFromClient(" << total_run_ms << ") milliseconds" << std::endl;
	}

	// PAUSING TIMER FUNCTIONS
	typedef ConcreteOperationCall<CNotificationServerCallable::PauseCall> MyPauseCall;
	void onResult(MyPauseCall& call)
	{
		//std::cout << "onResult(MyPauseCall&)" << std::endl;
	}
	void onError(MyPauseCall& call)
	{
		//std::cout << "onError(MyPauseCall&) " << std::endl;
	}
	void pauseTimerFromClient(int pause_ms)
	{
		
		MyPauseCall *pCall;
		if (createCall(pCall))
		{
			pCall->argument().pause_duration_ms = pause_ms;
			pCall->sendTo(mCallable);
		}
		//Sleep(10);
		std::cout << "Client: called pauseTimerFromClient(" << pause_ms << ")" << std::endl;
	}

	// UNPAUSING TIMER FUNCTIONS
	typedef ConcreteOperationCall<CNotificationServerCallable::UnpauseCall> MyUnpauseCall;
	void onResult(MyUnpauseCall& call)
	{
		//std::cout << "onResult(MyUnpauseCall&)" << std::endl;
	}
	void onError(MyUnpauseCall& call)
	{
		std::cout << "onError(MyUnpauseCall&) " << std::endl;
	}
	void unpauseTimerFromClient()
	{
		MyUnpauseCall *pCall;
		if (createCall(pCall))
		{
			pCall->sendTo(mCallable);
		}
		Sleep(10);
		std::cout << "Client: called unpauseTimerFromClient() " << std::endl;

	}

	//ISFINISHED TIMER FUNCTIONS
	typedef ConcreteOperationCall<CNotificationServerCallable::IsFinishedCallWithResult> MyIsFinishedCallWithResult;
	void onResult(MyIsFinishedCallWithResult& call) 
	{
		mFinished = call.getResult().flag;
	}
	void onError(MyIsFinishedCallWithResult& call) {
		std::cout << "onError(MyIsFinishedCallWithResult& call)" << std::endl;
	}
	
	void getIsFinished()
	{
		MyIsFinishedCallWithResult *pCall;
		if (createCall(pCall))
		{
			pCall->sendTo(mCallable);
		}
	}
	bool isFinishedFromClient()
	{
		getIsFinished();
		Sleep(50); // Wait a bit until the result will come to onResult(); Hope 50 ms is enough;
		return mFinished;
	}
	

private:
	bool mFinished; 
	CNotificationServerCallable& mCallable;
	MyCountdownNotification* mCountdownNotification;	
};

}
}
}


#endif