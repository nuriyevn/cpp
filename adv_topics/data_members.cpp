#include <cstdio>
#include <iostream>
using namespace std;

class Foo {
    int ia = 0;
    const char * sb = "";
    int ic = 0;
public:
    Foo (const int a, const char * b, const int c) : ia(a), sb(b), ic(c) {};
    void seta (const int a) {ia =a;}
    void setb (const char * b ) {sb=b;}
    void setc (const int c) {ic=c;}
    int geta() const {return ia;}
    const char * getb () const {return sb;}
    int getc() const {return ic;}
};
int main() {
    Foo foo(1, "two", 3);
    printf("ia is %d, sb is %s, ic is %d\n", foo.geta(), foo.getb(), foo.getc());
    Foo foo2(3, "five", 9);
    cout << "ia is " << foo2.geta() << " sb is " << foo2.getb() << " ic is " << foo2.getc();
    return 0;
}