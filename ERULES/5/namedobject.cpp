#include <iostream>
using namespace std;

template<typename T>
class NamedObject
{
public:
    NamedObject(const char* name, const T& value)
        : nameValue(name), objectValue(value)
    {
        cout << "ctor with char" << endl;
    };
    NamedObject(std::string& name, const T& value)
        : nameValue(name), objectValue(value)
    {
        cout << "ctor with string" << endl;
    };
    NamedObject(const NamedObject& obj)
        : nameValue(obj.nameValue), objectValue(obj.objectValue)
    {
        cout << "copy ctor" << endl;
    };
    void print(void)
    {
        cout << nameValue << ":" << objectValue << endl;
    }
private:
    std::string nameValue;
    T objectValue;
};

int main()
{
    //NamedObject<int>no1("Smallest Prime number", 2);
    //NamedObject<int>no2(no1);

    std::string newDog("Persephone");
    std::string oldDog("Satch");

    NamedObject<int> p(newDog, 2);
    NamedObject<int> s(oldDog, 36);

    p = s;
    p.print(); s.print(); 

}
