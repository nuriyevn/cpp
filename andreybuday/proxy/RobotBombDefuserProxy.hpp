class RobotBombDefuserProxy : RobotBombDefuser
{
public:
	RobotBombDefuserProxy(int communicationWavelength)	
		: _robotBombRefuser(0), _connectionAttempts(3)
	{
		_communicationWavelength = communicationWavelength;
	}
	~RobotBombDefuserProxy()
	{
		if (_robotBombDefuser)
			delete _robotBombDefuser;
	}

	/*RobotBombDefuserProxy(const RobotBombDefuserProxy& obj)
	{
		_robotBombDefuser = new RobotBombDefuser();
		_connectionAttempts = obj._connectionAttempts;
		_communicationWavelength = obj._communicationWavelength();		
	}
	void init()
	{
		
	}*/
	virtual void WalkStraightForward(int steps)
	{	
		EnsureConnectedWithRobot();
		_robotBombDefuser->WalkStraightForward(steps);
	}
	virtual void TurnRight()
	{
		EnsureConnectedWithRobot();
		_robotBombDefuser->TurnRight();
	}
	virtual void TurnLeft()
	{
		EnsureConnectedWithRobot();
		_robotBombDefuser->TurnLeft()l
	}
	virtual void DefuseBomb()
	{
		EnsureConnectedWithRobot();
		_robotBombDefuser->DefuseBomb();
	}
	void EnsureConnectedWithRobot()
	{
		if (_robotBombDefuser == 0)
		{
			_robotBombDefuser = new RobotBombDefuser();
			_robotBombDefuser->ConnectWireless(_communicationWavelength);
		}
		for (int i = 0; i < _connectedAttempts; i++)
		{
			if (_robotBombDefuser.IsConnected() != true)
			{
				_robotBombDefuser.ConnectWireless(_communicationWavelength);
			}
			else
			{
				break;
			}
		}
		if (_robotBombDefuser.IsConnected() != true)
		{
			cout << "No connection with remote bomb diffuser robot could be made after few attempts.";
		}
	}


private:
	RobotBombDefuser *_robotBombDefuser;
	int _communicationWavelength;
	int _connectionAttempts;
	// Avoid usage of copy operations
	const RobotBombDefuserProxy& RobotBombDefuserProxy(const RobotBombDefuserProxy&);
	RobotBombDefuserProxy(const RobotBombDefuserProxy&);
};
