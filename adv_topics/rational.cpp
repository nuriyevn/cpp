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
    void setNumerator(int num) { _n = num;};
    void setDenominator(int den) { _d = den;};
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

// TODO for students: reducing the lowest common denominator for all arithmetics
Rational Rational::operator + ( const Rational & rhs ) const {
   
    return Rational((this->_n * rhs._d) + (this->_d * rhs._n), this->_d * rhs._d);
    //     Rational(   (2     * 10)     + (5        *  3)    ,  5 * 10)
    // Rational(35, 50);
}


std::ostream& operator<<(std::ostream &out, const Rational& obj)
{
    out << obj.numerator() << '/' << obj.denominator() << endl;
    return out;
}

std::istream& operator>>(std::istream &in, Rational& obj)
{
    int n, d;
    in >> n >> d;
    obj.setNumerator(n);
    obj.setDenominator(d);
    return in;
}

int main(){
    Rational first(2,5);
    Rational second(3,10);
    Rational third(4, 10);
    Rational fourth;
    fourth = (first + second) + third;


    cout << first + 8;
    
    return 0;
}