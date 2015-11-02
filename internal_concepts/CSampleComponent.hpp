#include "api/sys/mocca/pf/comm/itc/src/CHBTimer.hpp"

class CSampleComponent : public CHBComponent
			, public IHBTimerConsumer
{
private:
	class CSampleTimerConsumer : public IHBTimerConsumer
	{
	public:
		CSecondTimerConsumer();
		virtual ~CSecondTimerConsumer();
		virtual void processEvent(const CHBTimerEvent &ev);
	}
	CSampleDemoService mDemoService;
	CHBTimer mFirstTimer;
	CSecondTimerConsumer mSecondTimerConsumer;
	CHBTimer mSecondTimer;
public:
	void startTimers(void);
};

void processEvent( const CHBTimerEvent &ev);


