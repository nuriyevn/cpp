// 14.3 Constructor and destrcutor [except.ctor]
// As control passes from the point where an exception is thrown to a handler, 
// objects are destroyed by a process, specified in this subclause, called stack unwinding
// Each object with auto storage duration is destroyed if it has been constructed, but not yet destroyed,
// since the try block was entered. If and exception is thrown during the destruction of temporaries or local 
// varaiables for a return statement , the destructor for the returned object (if any) is also invoked. 
// The objects are desetroyed in the reverse order of  the completion of their construction

struct A { };
struct Y  { ~Y() noexcept(false) { throw 0; }};

A f() {

    try {
        A a;
        Y y;
        A b;
        return {}; // #1
    } catch (...) {

    }
    return {}; // #2

    // At #1, the returned object of type A is constructed. 
    // Then, the local variable b is destroyed (8.7). Next, the local variable y is destroyed, 
    // causing stack unwinding, resulting in the destruction of the returned object, 
    // followed by the destruction of the local variable a. 
    // Finally, the returned object is constructed again at #2. —end example]
}

