#ifndef __COMPLEX_HPP__
#define __COMPLEX_HPP__

#include <iostream>
#include <cstring>
#include <cmath>
const double D_EPSILON = 0.000001;

using namespace std;

class Complex 
{
public:  
   Complex();
   Complex(double r);
   Complex(double r, double i);
   ~Complex();
   Complex(const Complex& right);
   const Complex& operator=(const Complex& right);
   bool operator==(const Complex& right);
   bool operator!=(const Complex& right) const;
   Complex& operator+(const Complex& right);
   Complex& operator-(const Complex& right);
   Complex& operator*(const Complex& right);
   Complex& operator/(const Complex& right);

   friend ostream& operator<<(ostream& out, const Complex& cnum)
   {
      out << "(" << cnum.real << ", "  << cnum.im << ")";
      return out;
   }
   friend istream& operator>>(istream& in, Complex& cnum)
   {
      in >> cnum.real >> cnum.im;
      return in;
   }
private:
   bool isFloatEqual(double d1, double d2);
   double real;
   double im;
};

#endif // __COMPLEX_HPP__
