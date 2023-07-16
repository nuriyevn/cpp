#include <iostream>
#include <cstdio>
using namespace std;

class Rational {
    int _n = 0;
    int _d = 1;
public:
    Rational (int numerator =0, int denominator = 1): _n(numerator), _d(denominator){};
    Rational(const Rational & rhs): _n(rhs._n), _d(rhs._d){};
    ~Rational (){};
    int numerator() const { return _n;};
    int denominator() const {return _d;};
    Rational & operator = (const Rational &);
    Rational operator + (const Rational &) const;
    Rational operator - (const Rational &) const;
    Rational operator * (const Rational &) const;
    Rational operator / (const Rational &) const;
};

Rational & Rational::operator=(const Rational & rhs){
    if(this != &rhs){
        _n = rhs.numerator();
        _d = rhs.denominator();
    }
    return *this;
}
Rational Rational::operator + ( const Rational & rhs ) const {
   
    return Rational((this->_n * rhs._d) + (this->_d * rhs._n), this->_d * rhs._d);
}
int main(){
    Rational first(2,5);
    Rational second(3,10);
    Rational third;
    third = first + second;
    cout<<third.numerator()<<'/'<<third.denominator()<<endl;
    return 0;
}