#include <iostream>
#include <cstring>
using namespace std;

class Person
{
public:
   int age;
   char *name;
   int sex;
   char *occupation;
   char *address;
   char *education;

   Person(int age, char *name, int sex);
   Person(int age, char* name, int sex, char* occupation );
   Person(int age, char* name, int sex, char* occupation, char *address);
   Person(int age, char* name, int sex, char* occupation, char *address, char *education);  
   ~Person();
private:
   void init(void);

};

void Person::init()
{
   age = 18;
   name = new char[32];
   strcpy(name, "Name Surname");
   sex = 0;  
}
Person::Person(int arg, char *name, int sex)
{
   init();
}

Person::~Person()
{
   delete[] name;
}



int main()
{
   Person p(25, "Nusrat", 0);
}
