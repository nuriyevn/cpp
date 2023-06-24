#include <string>
#include <stddef.h>
#include <fstream>
#include <iostream>
using namespace std;
class Logger {
public:
	static Logger* Instance();
	bool openLogFile(std::string logFile);
	void writeToLogFile(std::string text);
	bool closeLogFile();
private:
	Logger(){};
	Logger(Logger const&) {};
	Logger& operator=(Logger const&) {};
	static Logger* m_pInstance;
	std::fstream fs;
};


Logger *Logger::m_pInstance = NULL;

Logger *Logger::Instance()
{
	if (!m_pInstance)
		m_pInstance = new Logger;
	return m_pInstance;
}

bool Logger::openLogFile(std::string _logFile)
{
	fs.open(_logFile.c_str(), fstream::out);		
	if (!fs.is_open())
		return false;
	else
		return true;
}

bool Logger::closeLogFile()
{
	fs.close();
	return true;
}

void Logger::writeToLogFile(std::string text)
{
	fs << text << endl;
}

int main()
{
	Logger* logger = Logger::Instance();
	if (logger->openLogFile("/tmp/log"))
	{ 
		string line;
		getline(cin, line);
		logger->writeToLogFile(line);
		logger->closeLogFile();	
	}
	else
		cout << "Error while opening file" << endl;
	return 0;
}

