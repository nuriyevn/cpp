#include <iostream>
using namespace std;

class Empty
{
};


class Derived: Empty { int a; };

class Another
{
    int a;
};

int main()
{
    Empty a, b;
    if (&a == &b)
        cout << "impossible" << endl;
    else
        cout << "Fine" << endl;


    Empty *p1 = new Empty;
    Empty *p2 = new Empty;

    if (p1 == p2)
        cout << "impossible" << endl;
    else
        cout << "Fine" << endl;

    cout << sizeof(Derived) << endl;
    cout << sizeof(Another) << endl;
    
    return 0;
}


