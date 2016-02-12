#include <iostream>

using namespace std;


class Empty 
{
public:
    Empty() { cout << "default ctor\n"; }; // default ctor
    Empty(const Empty& rhs) { cout << "copy ctor\n"; }; // copy constructur
    ~Empty() { cout << "dtor\n" << endl; };  // dtor
    Empty& operator=(const Empty& rhs){ cout << "ass operator\n"; };  // assignment operator 
};

int main()
{
    Empty e1; // default ctor
    Empty e2(e1); // copy ctor
    e2 = e1; // ass op
    Empty e3;
    Empty e4 = e3; // copy ctor
        
}
