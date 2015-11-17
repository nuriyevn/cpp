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
   
   cout << "right == " << right << endl;
   cout << "this == " << *this << endl;

   cout << "operator== called" << endl;
   return (isFloatEqual(right.im, this_im) 
            && 
           isFloatEqual(right.real, this_real));
}
bool Complex::operator!=(const Complex& right) const
{
}


Complex& Complex::operator+(const Complex& right)
{
   this->real += right.real;
   this->im += right.im;
   return *this;   
}

Complex& Complex::operator-(const Complex& right)
{
   this->real -= right.real;
   this->im -= right.im;
   return *this;
}

Complex& Complex::operator*(const Complex& right)
{
   //this->real = this->real * right.real - this->im * right.im;
   //this->im = this->real * right.im + this->im * right.real;

   double this_real = this->real;
   double this_im = this->im;
   
   this->real = this_real * right.real - this_im * right.im;
   this->im = this_real * right.im + this_im * right.real;

   //cout << *this << endl;
   return *this;
}

Complex& Complex::operator/(const Complex& right)
{
   double this_real = this->real;
   double this_im = this->im;
   double denom = right.real * right.real + right.im * right.im;
   

   this->real = (this_real * right.real + this_im * right.im) / denom;
   this->im = (right.real * this_im - right.im * this_real) / denom;
   return *this;
}

double Complex::getReal()
{
   return real;
}

double Complex::getImag()
{
   return im;
}

bool Complex::isFloatEqual(double d1, double d2)
{ 
   cout << "fabs(d1-d2)" << fabs(d1-d2) << endl; 
   return (fabs(d1-d2)<D_EPSILON);
}



