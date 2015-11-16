#include "Complex.hpp"

Complex::Complex()
   : real(0.0), im(0.0)
{
}

Complex::Complex(double r)
   : real(r), im(0.0)
{
}

Complex::Complex(double r, double i)
   : real(r), im(i)
{   
}

Complex::~Complex()
{
}

Complex::Complex(const Complex& right)
   : real(right.real), im(right.im)
{
}

const Complex& Complex::operator=(const Complex& right)
{
}


bool Complex::operator==(const Complex& right)
{
   
   double this_im = this->im;
   double this_real = this->real;

   return (isFloatEqual(right.im, this_im) 
            && 
           isFloatEqual(right.real, this_real));
}
bool Complex::operator!=(const Complex& right) const
{
}


Complex& Complex::operator+(const Complex& right)
{
   
}

Complex& Complex::operator-(const Complex& right)
{
}

Complex& Complex::operator*(const Complex& right)
{
}

Complex& Complex::operator/(const Complex& right)
{
}

bool Complex::isFloatEqual(double d1, double d2)
{  
   return (fabs(d1-d2)<D_EPSILON);
}



