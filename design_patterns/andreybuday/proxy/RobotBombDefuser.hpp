#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class RobotBombDefuser
{
public:
	RobotBombDefuser()
	{
		srand(time(0));
		_robotConfiguredWavelength = 41;
		_isConnected = false;
	}
	~RobotBombDefuser()	{}
	RobotBombDefuser(const RobotBombDefuser&) {}

	void ConnectWireless(int communicationWavelength)
	{	
		if (communicationWaveLength == _robotConfiguredWavelength)
		{
			_isConnected = IsConnectedImmitatingConnectivityIssues();
		}
	}

	bool IsConnected()
	{
		_isConnected = IsConnectedImitatingConnectivityIssues();
		return _isConnected;
	}

	bool IsConnectedImitatingConnectivityIssues()
	{
		int r = rand() % 10;
		return r < 4;
	}
	virtual void WalkStraightForward(int steps)
	{
		cout << "Did {0} steps forward...", steps);
	}
	virtual void TurnRight()
	{
		cout << "Turned right";
	}
	virtual void TurnLeft()
	{
		cout << "Turned left";
	}
	virtual void DefuseBomb()
	{
		cout << "Cut red of green or blue wire...";
	}
private:
	int _robotConfiguredWavelength;
	bool _isConnected;
};
