#include <iostream>
#include <string.h>
#include <vector>
#include <cstdlib>

using namespace std;

class String
{
	char *m_string;
public:
	String() 
	{
		cout << "String()" << endl;
	}
	
	String(const String& str)
	{
		cout << "String(String& str)" << endl;
		m_string = new char[strlen(str.getString()) + 1];
		strcpy(m_string, str.getString());
	}
	String(char *str)
	{
		cout << "String(char *str)" << endl;
		m_string = new char[strlen(str) + 1];
		strcpy(m_string, str);			
	}
	~String()
	{
		delete [] m_string;		
	}
	const char *getString() const
	{
		return m_string;
	}
};
/*
class A
{
private:
	vector<String> m_vec;	
public:
	A(const int a) 
	{
		char str[10];
		for (i = 0; i < 20; i++)
		{
			itoa(i, str, 10);
			strcpy(m_vec[i].)
		}
	}
	~A()	
};
*/

int main()
{
	cout << "=======" << endl;
// 	String test; // error because of destrcutor delete operator
	String str = "Hello";
	String rstr = str;

	String astr("World");
	String bstr(str);
	cout << "str = " << str.getString() << endl
		<< "rstr = " << rstr.getString() << endl;			
	String str2(str);
	String str3 = str2;
}
