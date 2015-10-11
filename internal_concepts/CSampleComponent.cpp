#include "api/sys/mocca/pf/appbase/application/base/src/HBApplication.hpp"
#include "CSampleComponent.h"


CSampleComponent::CSampleComponent()
	: CHBComponent()
	, IHBTimerConsumer()
	, mDemoService(self())
	, mFirstTimer(self())
	, mSecondTimerConsumer()
	, mSecondTimer(mSecondTimerConsumer)
{

}

void CSampleComponent::startTimers(void)
{
	TRC_SCOPE( inteco_timer_sample, CSampleComponent, startTimers);
	DBG_MSG(("Starting Timer"));
	mFirstTimer.start(600, CHBTimer::eContinously);
	mSecondTimer.start(1000, 3);
}

//{{DBG_SCOPE_DEFINITIONS
	TRC_SCOPE_DEF( inteco_timer_sample, CSampleComponent, processEvent);
	TRC_SCOPE_DEF( inteco_timer_sample, CSampleComponent, startTimers);
	TRC_SCOPE_DEF( inteco_timer_sample, CSecondTimerConsumer, processEvent);
//}}DBG_SCOPE_DEFINITIONS

void CSampleComponent::processEvent(const CHBTimerEvent &ev)
{
	TRC_SCOPE( inteco_timer_sample, CSampleComponent, processEvent);
	static int count = 1;
	if (count < 5)
	{
		DBG_MSG(("First Timer elapsed for the %d. time", count));
		count++;
	}
	else
	{	
		mFirstTimer.stop();
	}
}

void CSampleComponent::CSecondTimerConsumer::processEvent(const CHBTimerEvent &ev)
{
	TRC_SCOPE( inteco_timer_sample, CSecondTimerConsumer, processEvent);
	DBG_MSG(("Second Timer elapsed"));
}






