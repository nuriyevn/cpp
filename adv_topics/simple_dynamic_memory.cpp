#include <iostream>
using namespace std;
class Student 
{
    string name;
    int *grants;
    int currentGrant;


    public:
    Student(string _n)
        : name(_n), grants(new int[9]), currentGrant(0)
    {
        
    }

    ~Student()
    {
        delete []grants;
    }

    void addGrant(int amount)
    {
        if (currentGrant < 9)   
        {
            grants[currentGrant] = amount;
            currentGrant++;
        }
    }
    
    void printAllGrants()
    {
        for (int i = 0; i < currentGrant; i++)
        {
            cout << grants[i] << endl;
        }
    }
    int sumUpAllGrants(){
        int result = 0;
        for (int i =0; i < currentGrant; i++){
            result += grants[i];
        }
        return result;
    }
    string getName(){
        return name;
    }
};


int main()
{
    Student student("Mark Zuckerberg");
    Student student2("Elon Musk");

    student.addGrant(100);
    student.addGrant(200);
    student.printAllGrants();

    student2.addGrant(300);
    student2.addGrant(400);

    student2.printAllGrants();
    cout << "sum for " << student2.getName() << " is " << student2.sumUpAllGrants() << endl;
    cout << "sum for " << student.getName() << " is " << student.sumUpAllGrants() << endl;
}