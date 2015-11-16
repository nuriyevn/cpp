#include "Complex.hpp"

template <typename T>
Complex<T>::Complex()
   : real((T)0), im((T)0)
{
}

template <typename T>
Complex<T>::Complex(T r, T i)
   : real(r), im(i)
{   
}

template <typename T>
Complex<T>::~Complex()
{
}

template <typename T>
Complex<T>::Complex(const Complex& right)
   : real(right.real), im(right.im)
{
}

template <typename T>
const Complex<T>& Complex<T>::operator=(const Complex& right)
{
}



template <typename T>
bool Complex<T>::operator==(const Complex& right) const
{
}

template <typename T>
bool Complex<T>::operator!=(const Complex& right) const
{
}


template <typename T>
Complex<T>& Complex<T>::operator+(const Complex& right)
{
}

template <typename T>
Complex<T>& Complex<T>::operator-(const Complex& right)
{
}

template <typename T>
Complex<T>& Complex<T>::operator*(const Complex& right)
{
}

template <typename T>
Complex<T>& Complex<T>::operator/(const Complex& right)
{
}

template <typename T>
ostream& operator<<(ostream& out, const Complex<T>& right)
{
}
template <typename T>
istream& operator>>(istream& out, const Complex<T>& right)
{
}



