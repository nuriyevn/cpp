#include <iostream>

using namespace std;

class FahrenheitSensor
{
public:
	float getFahrenheitTemp() 
	{
		float t = 32.0;
		//
		return t;
	}
protected:
	void adjust() {};	// adjusting sensor (protected method);
};


class Sensor
{
public:
	virtual ~Sensor() {}
	virtual float getTemperature() = 0;
	virtual void adjust() = 0;
};

class Adapter : public Sensor, private FahrenheitSensor
{
public:
	Adapter() {}
	float getTemperature() 
	{
		return (getFahrenheit() - 32.0)*5.0/9.0;	
	}
	void adjust() {
		FahrenheitSensor::adjust();
	}
};

int main()
{
	Sensor *p = new Adapter();
	p->adjust();
	cout << "Celsius temperature = " 
		 << p->getTemperature() << endl;
	delete p;
	return 0;	
}


