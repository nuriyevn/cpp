void CSampleDemoService::requestStartDemo()
{
	TRC_SCOPE( inteco_template_onoff, CSampleDemoService, requestStartDemo);
	DBG_MSG(("receiving request!!"));
	mComponent.startTimers();
}


