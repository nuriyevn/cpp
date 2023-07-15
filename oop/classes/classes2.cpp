#include <iostream>
using namespace std;
class Example
{
public:
    int total;
    void accumulate(int x) { total += x; }
};

class Example2 
{
public:
    int total;
    Example2 (int initial_value) : total(initial_value) {};
    void accumulate(int x) { total += x;};
};

class Example3
{
    string data;
public:
    //And when any constructor is explicitly declared in a class, 
    // no implicit default constructors is automatically provided.
    Example3 (const string& str) : data(str) {} 
    // so we have to define empty constr if we want to define
    Example3() {}
    const string& content() const { return data; }
};

// Destructor with a resource cleanup
class Example4 {
    string *ptr;
public:
    Example4() : ptr(new string) {}
    Example4(const string& str) : ptr(new string(str)) {}
    ~Example4() { delete ptr; }
    const string& content() const { return *ptr; }
};

// copy constructor

class MyClass {
public:
    int a, b;
    string c;
    // f a class has no custom copy nor move constructors 
    // (or assignments) defined, an implicit copy constructor 
    // is provided
    // An implicit copy constructor is automatically defined.
    // The definition assumed for this function performs a shallow copy, roughly equivalent to:
    MyClass::MyClass(const MyClass& x) : a(x.a), b(x.b), c(x.c) {}
};

class Example5 {
    string *ptr;
  public:
    Example5 ( const string& str) : ptr(new string(str)) {}
    ~Example5() { delete ptr; }
    // copy constr;
    //The deep copy performed by this copy constructor allocates 
    // storage for a new string, which is initialized to contain 
    // a copy of the original object. In this way, both objects 
    // (copy and original) have distinct copies of the content 
    // stored in different locations.
    Example5( const Example5& x) : ptr(new string(x.content())) {}
    // access content
    const string& content() const { return *ptr; }

    // In this case, not only the class incurs the risk of 
    // deleting the pointed object twice, but the assignment 
    // creates memory leaks by not deleting the object pointed 
    // by the object before the assignment.
    Example5& operator=(const Example5& x)
    {
        delete ptr;                     // delete currently pointed string
        ptr = new string(x.content());  // allocate space for new string, and copy
        return *this;
    };

    // Or even better, since its string member is not constant, it could re-utilize the same string object:
    /*
    Example5& operator= (const Example5& x) {
        *ptr = x.content();
        return *this;
    }*/

    // This moving only happens when the source of the value is an unnamed object.
    // Unnamed objects are objects that are temporary in nature, and thus haven't even been given a name.
    // Typical examples of unnamed objects are return values of functions or type-casts.
    // Using the value of a temporary object such as these to initialize another object or to assign its value,
    // does not really require a copy: the object is never going to be used for anything else, and thus, its value can be moved into the destination object. 
    // These cases trigger the move constructor and move assignments:
    // The move constructor is called when an object is initialized on construction using an unnamed temporary.
    // Likewise, the move assignment is called when an object is assigned the value of an unnamed temporary:

    /*
    MyClass fn();            // function returning a MyClass object
    MyClass foo;             // default constructor
    MyClass bar = foo;       // copy constructor
    MyClass baz = fn();      // move constructor
    foo = bar;               // copy assignment
    baz = MyClass();         // move assignment 
    */
    // MyClass (MyClass&&);             // move-constructor
    // MyClass& operator= (MyClass&&);  // move-assignment 
};

class Example6 {
    string *ptr;
  public:
    Example6 (const string& str) : ptr(new string(str)) {

    }
    ~Example6 () { 
        delete ptr; 
        }
    // move constr
    Example6 (Example6&& x) { 
        cout << "MOve constr" << endl;
        ptr = x.ptr;
        x.ptr = nullptr; 
    }
    // move assignment
    Example6& operator=(Example6&& x) {
        delete ptr;
        ptr = x.ptr;
        x.ptr = nullptr;
        return *this;
    }

    // access content:
    const string& content() const { return *ptr; }
    // addition:
    Example6 operator+ (const Example6& rhs) {
        return Example6(content() + rhs.content());
    }
};

int main()
{
    Example ex;
    Example2 ex2(100);
    // Example2 ex22; //not valid because it has been replaced with the implicit defalut constr;

    Example3 foo;
    Example3 bar("Exaample");
    cout << "bar's content " << bar.content() << '\n';

    Example4 foo2;
    Example4 bar2("example");

    cout << "bar's content " << bar2.content() << '\n';

    Example5 foo3("Example");
    Example5 bar3 = foo3;
    Example5 baz3("Numune");


    baz3 = foo3 = bar3;

    cout << "bar's content: " << bar3.content() << '\n';
    Example6 foo6("Exam");
    Example6 bar6 = Example6("ple"); //move construction;

    foo6 = foo6 + bar6; // move assingment
    cout << "foo's content: " << foo.content() << '\n';
    
    return 0;
}

