#include <iostream>
using namespace std;
class Complex
{
public:
	Complex()
		: re(0), im(0)
	{
	}
	Complex(int r, int i)
		: re(r), im(i)
	{
			
	}
	~Complex() {}
	Complex& operator=(const Complex& rhs)
	{
		if (this == &rhs)
			return *this;
		re = rhs.re;
		im = rhs.im;
		return *this;	
	}
	Complex(const Complex& rhs)
		: re(rhs.re), im(rhs.im)
	{
	}

	void print(void)
	{
		cout << "(" << re << " , " << im << ")" << endl;	
	}
	void setRe(double re)
	{
		this->re = re;	
	}
	void setIm(double im)
	{
		this->im = im;
	}
	double getRe(void)
	{
		return re;
	}
	double getIm(void)
	{
		return im;
	}
	friend ostream& operator<<(ostream& out, const Complex& c)
	{
		out << "( " << c.re << " , " << c.im << " )" << endl;
		return out;
	}	
	friend istream& operator>>(istream& in, Complex& c)
	{
		double r, i;
		in >> r >> i;
		c.setRe(r);
		c.setIm(i);
		return in;	
	}
private:
	double im, re;
};

int main()
{
	Complex c[4];
	cin >> c[0];
	c[2] = c[0];
	c[0].setRe(c[0].getRe() * 2);	
	cout << c[0];

	cin >> c[1];
	c[3] = c[1];
	c[1].setIm(c[1].getIm() * 2);
	cout << c[1];
	cout << "=====FullOutput====" << endl;
	for (int i = 0; i < 4; i++)
		cout << c[i] << endl;
	return 0;
}

