#include <iostream>


class Rational
{
public:
	Rational(int numerator = 0, int denominator = 1);
	int numerator() const;
	int denominator() const;

private:
	int num;
	int denom;
};

Rational::Rational(int numerator, int denominator)
	: num(numerator), denom(denominator)
{
	
}

int Rational::numerator() const
{
	return num;
}
int Rational::denominator() const
{
	return denom;
}

const Rational operator*(const Rational& lhs, const Rational& rhs)
{
	
}

int main()
{
	Rational r1, r2, r3;
	(r1*r2) = r3; // this madness is legal if return type of operator* for Rational class has const modificator

}
