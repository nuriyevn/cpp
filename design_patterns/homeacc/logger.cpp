#include "logger.h"
Logger *Logger::m_pInstance = NULL;

Logger* Logger::Instance()
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

void Logger::writeToLogFile(std::string text)
{
    fs << text << endl;
	cout << text << endl;
}

bool Logger::closeLogFile()
{
    fs.close();
    return true;
}

ostream& operator<<(ostream& out,string& str)
{
	out << "tes";
	return out;	
}


