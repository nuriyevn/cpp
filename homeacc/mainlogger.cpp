#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "logger.h"
#include <ctime>
using namespace std;

int main()
{
	Logger *logger = Logger::Instance();
	logger->openLogFile("/tmp/mylog3.txt");
	(*logger) << "Hello" << endl;
	logger->closeLogFile();	
	system("gedit /tmp/mylog3.txt 2> /dev/null");
}

int oldmain()
{	
	srand(time(0));

	Logger *logger = Logger::Instance();
	string msg1 = "here is the first number:";
	int number = rand() % 100;
	msg1 = msg1 + to_string(number);
	
	string msg2 = "here is the second number:";
	int number2 = rand() % 100 - 200;
	msg2 = msg2 + to_string(number2);

	logger->openLogFile("/tmp/mylog2.txt");
	logger->writeToLogFile(msg1);
	logger->writeToLogFile(msg2);
	logger->closeLogFile();		
	system("gedit /tmp/mylog2.txt 2> /dev/null");
}
