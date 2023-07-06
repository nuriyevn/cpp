#include <iostream>


class Cents
{
private:
    int m_cents;
public:
    Cents(int cents=0)
        : m_cents{ cents }
    {
    }

    int getCents() const { return m_cents; }
    void setCents(int cents) { m_cents = cents; }

    operator int() const { return m_cents; }
    
};


void printInt(int value)
{
    std::cout << value;
}


class Dollars
{
private:
    int m_dollars;
public:
    Dollars(int dollars=0)
        : m_dollars{ dollars }
    {
    }

     // Allow us to convert Dollars into Cents
     operator Cents() const { return Cents{ m_dollars * 100 }; }
};

void printCents(Cents cents)
{
    std::cout << cents; // cents will be implicitly cast to an int here
}


/*

Converting constructors vs overloaded typecasts

Overloaded typecasts and converting constructors perform similar roles: 
an overloaded typecast allows us to define a function 
that converts some program-defined type A into some other type B.
 A converting constructor allows us to define a function that creates some program-defined type A 
from some other type B. So when should you use each?

In general, a converting constructor should be preferred to an overloaded typecast, 
as it allows the type being constructed to own the construction.
There are a few cases where an overloaded typecast should be used instead:

1.When providing a conversion to a fundamental type (since you can’t define constructors for these types). 
Most idiomatically, these are used to provide a conversion to bool for cases 
where it makes sense to be able to use an object in a conditional statement.
2. When providing a conversion to a type you can’t add members to 
(e.g. a conversion to std::vector, since you can’t define constructors for these types either).
3. When you do not want the type being constructed to be aware of the type being converted to. 
This can be helpful for avoiding circular dependencies. For example, std::string provides an overloaded typecast to std::string_view so that std::string_view doesn’t have to #include <string>.
*/

int main()
{
    Cents cents{ 7 };
    printInt(cents.getCents()); // print 7
    printInt(cents); // print 7

    int c { static_cast<int>(cents) };
    int d = cents;

    std::cout << '\n';

    Dollars dollars{ 9 };
    printCents(dollars);

    return 0;
}