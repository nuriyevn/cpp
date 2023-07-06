#include <cstdio>
#include <iostream>
using namespace std;

class A{
    string _value = "";
public:
    void setv( string a) {_value = a;};
    string getv () {return _value;};
};

int main(){
    A a;
    a.setv("nusrat");
    printf("a is %s", a.getv());
    return 0;
}