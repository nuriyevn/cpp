#include <cstdio>
/* #include <iostream> */
using namespace std;

class c1{
    int i = 0;
public:
    void setvalue(const int & value);
    int getvalue() const;
};

void c1::setvalue(const int & value)
{ 
    i = value;
}

int c1::getvalue() const
{
    return i;
}

int main(){
    const int i =47;
    c1 o1;
    o1.setvalue(i);
    printf("value is %d\n", o1.getvalue());
    return 0;
}
