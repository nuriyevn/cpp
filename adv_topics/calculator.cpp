#include <iostream>
using namespace std;

class Calculator{
public:
    int Add(const int &a, const int &b){return a+b;}
    int Subtract(const int &a,const int &b){return a-b;}
    int Multiple(const int &a,const int &b){return a*b;}
    double Division(const double &a,const double &b){
        if(b!=0){
            return a/b;
        }else{
            throw invalid_argument("Zero Division");
        }
    }

};
int main(){
    Calculator calc;
    int result = calc.Add(3, 0);
    cout<<result<<" that was a result "<<endl;
    double theOtherResult = 0.0;
    double divisor = .0;
    try
    {
        divisor = 44;
        theOtherResult = calc.Division(divisor, 0);
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << e.what() << '\n';
        double newDivider = 0;
        cout << "Please enter new divider";
        cin >>  newDivider;
        theOtherResult = calc.Division(divisor, newDivider);
    }

    cout<<theOtherResult<<" that was the other result"<<endl;
}