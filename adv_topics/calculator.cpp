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
            return 0;
        }
    }

};
int main(){
    Calculator calc;
    int result = calc.Add(3, 0);
    cout<<result<<" that was a result "<<endl;
    double theOtherResult = calc.Division(44, 3);
    cout<<theOtherResult<<" that was the other result"<<endl;
}