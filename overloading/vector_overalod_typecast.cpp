// https://www2.cs.sfu.ca/CourseCentral/125/tjd/vector_example.html
// https://stackoverflow.com/questions/45322982/overloading-assignment-operator-in-order-to-return-stdvector


#include <iostream>
using namespace std;
class myvec
{
private:
    /* data */
public:
    myvec(/* args */);
    ~myvec();
    myvec(const myvec& rhs)
    {
        cout << "Copy constr" << endl;
    } 
    myvec& operator=(myvec& rhs) {
        cout << "Assignment constr" << endl;
        return *this;
    }

    
};

myvec::myvec(/* args */)
{
    cout << "Default Constr" << endl;
}

myvec::~myvec()
{
    cout << "Default Destr" << endl;
}


int foo()
{
    myvec v;
    return 1;
}


class Animal
{
private:
     string type;
     string name;
     string sound;


public:
      // Default Constructor Here
    Animal(string _t, string _n, string _s) 
        : type(_t), name(_n), sound(_s)
    {   
        
    }
    ~Animal() {

    }
};

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
    
};


int main()
{
    
    Student student("Mark Zuckerberg");

    student.addGrant(100);
    student.addGrant(200);
    student.printAllGrants();

    /*Animal dog1("dog", "lessy", "hav-hav");
    foo();
    myvec  v1; // Default const
    myvec v2(v1); // copy const
    myvec v3 = v1; // copy const
    v3 = v2; // copy assignment operator*/
}