#include <cstdio>
using namespace std;

class c1 {
    int _value = 0;
public:
    explicit c1 (const int & value) : _value(value) {}
    void setvalue( const int & value ) { _value = value; }
    int getvalue() const { return _value; }
};

void func(const c1 & o) {
    printf("value is %d\n", o.getvalue());
}

int main() {
    c1 o(5);
    /* printf("value is %d\n", o.getvalue()); */
    func(o);
    return 0;
}
