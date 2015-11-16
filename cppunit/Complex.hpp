#include <iostream>
#include <cstring>

using namespace std;


template <typename T>
class Complex 
{
public:  
   Complex();
   Complex(T r, T i);
   ~Complex();
   Complex(const Complex& right);
   const Complex& operator=(const Complex& right);
   bool operator==(const Complex& right) const;
   bool operator!=(const Complex& right) const;
   Complex& operator+(const Complex& right);
   Complex& operator-(const Complex& right);
   Complex& operator*(const Complex& right);
   Complex& operator/(const Complex& right);

   friend ostream& operator<< <T>(ostream& out, const Complex& right); //{}
   friend istream& operator>> <T>(istream& out, const Complex& right); //{}
private:
   T real;
   T im;
};
