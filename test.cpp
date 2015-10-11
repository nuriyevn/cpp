#include <iostream>

using namespace std;

class Person
{

public:
	
	Person(string n, int a, bool s, bool m)
	{
		name = n;
		age = a;
		sex = s;
		marriage_status = m;
	}
	~Person(){}
	void setName(string n) { name = n; }
	void setAge(int a) { age = a;}
	void setMarriage(bool m) { marriage_status = m;}
	void setSex(bool s) { sex = s;};
	int getAge(void) { return age; }
	string getName(void) { return name; } 
private:
	string name;
	int age;
	bool sex;
	bool marriage_status;
};

class Student : public Person
{
public:
	Student(string addr, bool exam_s, bool is_h)
	: Person("", 0, 1, 0)
	{
		dorm_address = addr;
		exam_status = exam_s;
		is_hungry = is_h; 
	}
	void showInfo(void)
	{
		cout << "Hi , I'm " << this->getName() << ". I'm " << this->getAge() << " years old" << endl;
	}
	bool exam_status;
	bool is_hungry;
	string dorm_address;	
};

int main()
{
	string addr;
	cout << "Please, input dorm address:" << endl;
	cin >> addr;
	cout << "Exam status: 0 - failed, 1 - passed" << endl;
	bool es, ih;	
	cin >>  es;
	cout << "Have you had your breakfast today?" << endl;
	cin >> ih;
	Student *s =  new Student(addr, es, ih );

	cout << "Input your age" << endl;
	int age;
	cin >> age;
	s->setAge(age);	
	string name;
	cout << "Input your name " << endl;
	cin >> name;
	s->setName(name);
		
	s->showInfo();
	
	delete s;	
}
