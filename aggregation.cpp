#include <cstring>

using namespace std;

class Teacher
{
private:
	string m_strName;
public:
	Teacher(string strName)
		: m_strName(strName)
	{
	}
	string GetName() { return m_strName;}
};

class Department
{
private:
	Teacher *m_pcTeacher;
public:
	Department(Teacher *pcTeacher = NULL)
		: m_pcTeacher(pcTeacher)
	{
	}
};

int main()
{
	Teacher *pTeacher = new Teacher("Bob");
	{
		Department cDept(pTeacher);
	}
	
}



