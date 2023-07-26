#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>

using namespace std;
void line(int lines);

class Polynomial
{
    private:
        int degree;
        double* coeffs;
    public:
        //constructors
        Polynomial() {degree=0;coeffs=new double[1];}
        Polynomial(int deg) {degree=deg;coeffs=new double[deg+1];}
        Polynomial(const Polynomial& A);
        ~Polynomial() { delete []coeffs;}

        //mutators
        void GetCoeffs(istream& in);
        void EditCoeff(int deg);
        void ResetCoeffs();
        int Coeff(int deg);
        void Randomize(int max);

        //accessors
        void Show(ostream& out);
        int Degree() {return degree;}

        //operators
        Polynomial operator+(const Polynomial& B) const; //Polynomial + Polynomial
        
        friend Polynomial operator +(double c, const Polynomial& A); //c + Polynomial
        Polynomial operator +(double c); //Polynomial + c
        void operator +=(const Polynomial& B); //Polynomial+=Polynomial
        void operator =(const Polynomial& A);
        Polynomial operator*(int k);
        Polynomial operator*(Polynomial& A);
};

Polynomial Polynomial::operator*(int k) 
{
    Polynomial C(degree);
    C=*this;
    for (int i=degree; i>=0; i--)
        C.coeffs[i]*=k;
    return C;
}

Polynomial operator +(double c, const Polynomial& A)
{
    Polynomial C=A;
    C.coeffs[0]+=c;
    return C;
}

Polynomial Polynomial::operator +(double c) 
{
    Polynomial C=*this;
    C.coeffs[0]+=c;
    return C;
}

void Polynomial::Randomize(int max)
{
    for (int i=degree; i>=0; i--)
    {
        coeffs[i]=rand()%(max+1) + 1;
        if ((rand()%(101) + 1)%2 == 0)
            coeffs[i]*=-1;
    }
}

void Polynomial::operator =(const Polynomial& A)
{
    if (degree==A.degree)
    {
        for (int i=degree; i>=0; i--)
        {
            coeffs[i]=A.coeffs[i];
        }
    }
}

Polynomial Polynomial::operator+(const Polynomial& B) const
{
    if (degree>=B.degree)
    {
        Polynomial C(degree);
        C=*this;

        for (int i=B.degree; i>=0; i--)
        {
            C.coeffs[i]=coeffs[i]+B.coeffs[i];
        }
        return C;
    }
    else
    {
        Polynomial C=B;

        for (int i=degree; i>=0; i--)
        {
            C.coeffs[i]=coeffs[i]+B.coeffs[i];
        }
        return C;

    }
}

void Polynomial::operator+=(const Polynomial& B)
{
    *this = (*this + B);
}

int Polynomial::Coeff(int deg)
{
    return coeffs[deg];
}

void line(int lines)
{
    for (int i=0; i<lines; i++)
        cout << endl;
}

void Polynomial::GetCoeffs(istream& in)
{
    for (int i=degree; i>=0; i--)
    {
        in >> coeffs[i];
    }
    in.ignore();
}

void Polynomial::Show(ostream& out)
{

    if (coeffs[degree]>0)
                cout << "   ";
    for (int i=degree; i>=0; i--)
    {


        if (coeffs[i]>=0)
        {
            if (i!=degree)
                out << " + ";
            out << coeffs[i];


        }
        else
        {
            if (coeffs[i]<0)
                out << " - ";
                out << 0-coeffs[i];
        }
        if (i>1)
            out << "x^" << i;
        else if (i==1)
            out << "x";

    }
}

Polynomial::Polynomial(const Polynomial& A)
{
    coeffs=new double[A.degree+1];
    degree=A.degree;
    for (int i=A.degree; i>=0; i--)
    {
        coeffs[i]=A.coeffs[i];

    }

}

Polynomial Polynomial::operator*(Polynomial& A)
{
    int deg=A.degree+degree;
    Polynomial P(deg);

    for (int i=deg; i>=0; i--)
        P.coeffs[i]=0;



    for (int i=deg; i>=0; i--)
    {
        for (int j=A.degree; j>=0; j--)
        {
            P.coeffs[i+j]+=coeffs[i]*A.coeffs[j];
        }
    }

    return P;


}

int main()
{
    Polynomial A(5);
    A.Randomize(4);
    A.Show(cout);
    line(2);

    Polynomial B=A+8;
    B.Show(cout);
    line(2);

    Polynomial C(5);
    C.Randomize(6);
    C.Show(cout);

    line(2);
    Polynomial D(B + C);
    D.Show(cout);

    return 0;
}