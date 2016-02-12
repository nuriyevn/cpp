#include <iostream>
using namespace std;

// This example moves the error detection of illegal assop and cctor calls
// to the compile-time stage from linker-time stage, so mistake can be 
// detected and eliminated faster


class Uncopyable
{
protected:
    Uncopyable(){};
    ~Uncopyable(){};
private:
    Uncopyable(const Uncopyable&);
    Uncopyable& operator=(const Uncopyable&);
};

class HomeForSale : private Uncopyable
{

/* HomeForSale()
 *      : Uncopyable() 
 * {
 *
 * };
 * HomeForSale(const HomeForSale& hfs) 
 *      : Uncopyable(const Uncopyable&) // is prv
 * { 
 *
 * };
 *
 * HomeForSale& operator=(const HomeForSale& hfs) 
 *      : Uncopyable::operator=(const Uncopyable&) // is implicit prv
 * {
 *
 * };  
 *
 */


};

int main()
{

    HomeForSale h1;
    HomeForSale h2(h1), h3;
    h3 = h1;         
}
