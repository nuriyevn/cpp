#include <iostream>
using namespace std;

//https://en.cppreference.com/w/cpp/language/value_category

/*

7.2     [expr.prop]
7.2.1   [basic.lval]

             expressions
             /         \
            /           \
         glvalue      rvalue
        /      \     /      \
    lvalue     xvalue      prvalue


Each C++ expression (an operator with its operands, a literal, a variable name, etc.) 
is characterized by two independent properties: a type and a value category. 
Each expression has some non-reference type, and each expression belongs 
to exactly one of the three primary value categories: prvalue, xvalue, and lvalue.

* - a glvalue (“generalized” lvalue) is an expression whose evaluation determines the identity 
of an object or function;

* - a prvalue (“pure” rvalue) is an expression whose evaluation
  - -  computes the value of an operand of a built-in operator (such prvalue has no result object), or
  - -  initializes an object (such prvalue is said to have a result object).
        The result object may be a variable, an object created by new-expression,
        a temporary created by temporary materialization, or a member thereof. 
        Note that non-void discarded expressions have a result object (the materialized temporary). 
        Also, every class and array prvalue has a result object except 
        when it is the operand of decltype;

* - an xvalue (an “eXpiring” value) is a glvalue that denotes an object whose resources can be reused;
* - an lvalue (so-called, historically, because lvalues could appear on the left-hand side of an assignment expression) 
    is a glvalue that is not an xvalue;
* - an rvalue (so-called, historically, because rvalues could appear on the right-hand side of an assignment expression) 
    is a prvalue or an xvalue.


Rvalue references are treated as lvalues and unnamed rvalue references to objects are treated as xvalues; rvalue references to functions are treated as lvalues whether named or not.
*/

int main()
{
    //  ----------------------- LVALUE
    // the name of a variable, a function, a template parameter object (since C++20), 
    // or a data member, regardless of type, such as std::cin or std::endl. 
    // Even if the variable's type is rvalue reference, the expression consisting
    //  of its name is an lvalue expression (but see Move-eligible expressions);

    std::string str = "Hello, ", str2 = "World";
    auto it = str.begin();
    int words_count;
    int *p_wc = &words_count;
    

    // a function call or an overloaded operator expression, whose return type is lvalue reference,
    // such as
    //std::getline(std::cin, str);
    //std::cout << str << "dded";
    // also 
    ++it;

    // all other built-in assignment and compound assignment expressions;
    str += str2;
    std::cout << str;

    // pre- and postincrements
    words_count++;
    ++words_count;
    // the built-in indirection expression;
    *p_wc; 
    // subscript
    int array[] = {4, 1, 5};
    array[words_count];
    // member of object or p->m , member of pointer expression
    struct A
    { int m; } a;
    a.m;
    // a.*mp
    // p->*mp
    // comma separated where b an lvalue
    int ia, ib;
    ia, ib = 5;
    cout << "a=" << ia << "b=" << ib;
    // more about comma operator
    // https://en.cppreference.com/w/cpp/language/operator_other#Built-in_comma_operator



}