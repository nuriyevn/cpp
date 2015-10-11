#include "COnOffComponent.hpp"

COnOffComponent::COnOffComponent()
	: CHBComponent()
	, mCalculatorClient("myCalculator")
	, mRootService(mCalculatorClient)
{

}
