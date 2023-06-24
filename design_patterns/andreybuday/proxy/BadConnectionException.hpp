#include <iostream>
#include <exception>

using namespace std;


class BadConnectionException : public exception
{
public:
	BadConnectionException(const char* c_str) throw()
		: message(c_str)
	{
	}
	~BadConnectionException() throw()
	{
	}
	//BadConnectionException(const BadConnectionException&){}
	const char *what() const throw()
	{
		return message.c_str(); 
	}
private:
	string message;
};
