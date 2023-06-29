#include <iostream>
using namespace std;

class Base 
{
public:
    virtual void foo()
    {
        cout << "base::foo" << endl;
    }
};

class Derived : public Base
{
public:
    virtual void foo()
    {
        cout << "derived::foo" << endl;
    }
};

int main(int argc, char ** argv)
{
    Base b;
    Derived d;
    d.foo();
    // We can cast from Derived to Base , we should use dynamic cast
    dynamic_cast<Base&>(d).foo();

    //dynamic_cast<Derived&>(b).foo();

   /* Base *pb;
    Derived *pd;

    pb = new Derived;  //Base* points to a Derived object
    pd = dynamic_cast<Derived*>(pb); 
    pd->foo();  //outputs foo

    pb = new Base;  //Base* points to a Base object
    pd = dynamic_cast<Derived*>(pb);  
    pd->foo();  //outputs foo, too. Why?*/

    return 0;
}