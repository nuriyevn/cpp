#include <iostream>
using namespace std;

//#define UNDEF_SYM  // For undef symbol error generating


class HomeForSale 
{
public:


#ifdef UNDEF_SYM
    HomeForSale(){};
    HomeForSale copy(void)
    {
        HomeForSale h5;  
        HomeForSale h2(h5); // claiming for this code undef symbol
    }
#endif

// Creating assop and cctor
// But made them private so noone except members can call it.
// Even if members will call it, LINKER will say: no matching function undefined symbol, 
// as there is no definition for methods
private:
    HomeForSale(const HomeForSale&);
    HomeForSale& operator=(const HomeForSale&); 
};

int main()
{

#ifndef UNDEF_SYM
    HomeForSale h1;
    HomeForSale h2;
    HomeForSale h3(h1); // must not be compiled
    h1 = h2;     // must not be compiled
#else

    HomeForSale h;
    h.copy(); // undefined symbol
#endif
}
