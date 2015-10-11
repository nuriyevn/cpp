#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;
#include <unistd.h>

typedef short WORD;
class AlarmClockImpl;
// Abstraction interface
class AlarmClock
{
private:
	virtual void toWake() = 0;
protected:
	AlarmClockImpl *bridge;
public:
	virtual void start() = 0;
	virtual void stop() = 0;
};

// implementation realization
class AlarmClockImpl 
{
public:
	virtual void ring() = 0;
	virtual void notify() = 0;
};

// Clarification of abstraction alarm as derived
class LockupAlarmClock : public AlarmClock
{
private:
	WORD hourAlarm;
	WORD minutesAlarm;
	bool waitForWake;
	virtual void toWake();
protected:
public:
	LockupAlarmClock(AlarmClockImpl& bridgeImpl, WORD hour, WORD minutes);
	virtual void start();
	virtual void stop();
};

LockupAlarmClock::LockupAlarmClock(AlarmClockImpl& bridgeImpl, WORD hour, WORD minutes)
{
	this->bridge = &bridgeImpl;
	this->waitForWake = false;
	this->hourAlarm = hour;
	this->minutesAlarm = minutes;
}

void LockupAlarmClock::toWake()
{
	this->bridge->notify();
	this->bridge->ring();
}

void LockupAlarmClock::start()
{
	//SYSTEMTIME time;
	time_t now;
	tm *ltm = NULL;	

	waitForWake= true;
	while (waitForWake)
	{
		now = time(0);
		ltm = localtime(&now);
	
		if (ltm->tm_hour == this->hourAlarm &&
			ltm->tm_min == this->minutesAlarm)
		{
			waitForWake = false;
		}
		usleep(100000);
		//Sleep(100);
	}
	toWake();
}

void LockupAlarmClock::stop()
{
	waitForWake = false;
}

class ShellMP3AlarmClock : public AlarmClockImpl
{
private:
	string cmdplay;
protected:
public:
	ShellMP3AlarmClock(const string& cmd);
	~ShellMP3AlarmClock() {} ;
	virtual void ring();
	virtual void notify();
};

ShellMP3AlarmClock::ShellMP3AlarmClock(const string& cmd)
{
	this->cmdplay = cmd;
}

void ShellMP3AlarmClock::ring()
{
	system(cmdplay.c_str());

}

void ShellMP3AlarmClock::notify()
{
	cout << "ALARMING!" << endl;
}

int main(int argc, char *argv[])
{

	string cmd("su -c \"vlc /tmp/frank.mp3\" nusik");
	//system(cmd.c_str());
	ShellMP3AlarmClock impl(cmd);
	LockupAlarmClock lac(impl, 1, 15);
	lac.start();
	return 0;
}
