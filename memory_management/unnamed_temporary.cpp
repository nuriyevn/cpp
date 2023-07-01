#include <iostream>

struct S {
    S() { std::cout << "S()" << std::endl; }
    S(const S&) { std::cout << "S(const S&)" << std::endl; }
    ~S() { std::cout << "~S()" << std::endl; }
    operator bool() const { return true; }
    void print() { std::cout << "prtin called\n"; }
};

int main() {
    std::cout << "main 1" << std::endl;

 /*
§6.4:
selection-statement:
  if ( condition ) statement
  if ( condition) statement else statement
  switch ( condition ) statement

condition:
  expression
  type-specifier-seq declarator = assignment-expression
*/
   
    if (S s = S()) {
        std::cout << "if 1" << std::endl;

        s.print();
    }
    else {
        std::cout << "else 1" << std::endl;
        s.print();
    }

    std::cout << "main 2" << std::endl;

    if (S()) {
        std::cout << "if 2" << std::endl;
    }
    else {
        std::cout << "else 2" << std::endl;
    }

    std::cout << "main 3" << std::endl;
}