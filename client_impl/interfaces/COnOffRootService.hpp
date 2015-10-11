class COnOffCalculatorClient;

class COnOffRootService : public HBApplication::CHBRootServiceStub
{
public:
	COnOffRootService (COnOffCalculator &calculatorClient);
	virtual ~COnOffRootService();
	virtual HBServices::CHBVersion getImplVersion( void ) const;
	void requestBoot(const CHBBootParameter &);
private:
	COnOffCalculatorClient &mCalculatorClient;
};
