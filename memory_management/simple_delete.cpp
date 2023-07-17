#include <iostream>
/*
The delete[] operator is used to delete arrays. The delete operator is used to delete non-array objects. 
It calls operator delete[] and operator delete function respectively to delete the memory that the array 
or non-array object occupied after (eventually) calling the destructors for the array's elements or the non-array object.
*/


typedef int array_type[1];

int main() {
    // create and destroy a int[1]
    array_type *a = new array_type;
    // For the new that creates an array (so, either the new type[] or new applied to an array type construct), 
    // the Standard looks for an operator new[] in the array's element type class or in the global scope, 
    // and passes the amount of memory requested. 
    // It may request more than N * sizeof(ElementType) 
    // if it wants (for instance to store the number of elements, 
    // so it later when deleting knows how many destructor calls to done). 
    // If the class declares an operator new[] that additional to the amount of memory accepts another size_t, 
    // that second parameter will receive the number of elements allocated - it may use this for any purpose it wants (debugging, etc...).
    delete [] a;

    // create and destroy an int
    int *b = new int;
    // For the new that creates a non-array object, 
    // it will look for an operator new in the element's class or in the global scope. 
    // It passes the amount of memory requested (exactly sizeof(T) always).

    delete b;
    // For the delete, if the pointer passed is a base class of the actual object's type, 
    // the base class must have a virtual destructor (otherwise, behavior is undefined). 
    // If it is not a base class, then the destructor of that class is called, 
    // and an operator delete in that class or the global operator delete is used. 
    // If a base class was passed, then the actual object type's destructor is called, 
    // and the operator delete found in that class is used, or if there is none, 
    // a global operator delete is called. If the operator delete in the class has a second parameter of type size_t, 
    // it will receive the number of elements to deallocate.


    // create and destroy an int[1]
    int *c = new int[1];
    delete[] c;
    // For the delete[], it looks into the arrays' element class type and calls their destructors. 
    // The operator delete[] function used is the one in the element type's class, 
    // or if there is none then in the global scope.

    // create and destroy an int[1][2]
    int (*d)[2] = new int[1][2];
    delete [] d;
};

