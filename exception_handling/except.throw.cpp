// 14.2 Throwing an exception [except.throw]
// when an exception is thrown, control is transferred to the nearest handler with a matching type.
// "nearest" means the handler for which the compound-statement or ctor-initializer following the try keyword was most recently 
// entered by the thread of control and not yet exited.
// ???
#include <iostream>
using namespace std;
struct C {
    C() { cout << "def CTOR" << endl; }
    C(const C&) {
        if (std::uncaught_exceptions()) {
            throw 0; // throwing during copy to handler's exception declaration object (14.4)
        }
    }
};

int main() {
    #ifdef __cpp_guaranteed_copy_elision
        cout << "__cpp_guaranteed_copy_elision " << endl;
    #else
        cout << " copy elision is not guaranteed." << endl;
    #endif
    try {
        throw C(); // calls std::terminate if construction of the handler's 
                   // exception-declaration object is not elided.
    } catch(C) {}  // should probably use C& instead of C in catch because copy ctor is not elided otherwise for sime reason.
}