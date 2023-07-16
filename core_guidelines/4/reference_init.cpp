#include <vector>
#include <iostream>
using namespace std;
// This example shows that, in case of references, they must be initialized via consturtor's initialization list
class MyClass
{
private:
   vector<int>& vint;
public:
   MyClass(vector<int>&);   
   
};

// OK
MyClass::MyClass(vector<int>& _vint)
:vint(_vint) 
{
};
// Does not even compile
/*MyClass::MyClass(vector<int>& _vint)
{
   vint(_vint);

}*/

int main()
{

   vector<int> myvector;
   myvector.push_back(5);
   MyClass mc(myvector);  
}
