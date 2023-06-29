#include <iostream>
using namespace std;

class Date
{
private:
    int day; //1 to 31
    int month; // 1 to 12
    int year; // from -2 billion to 2 billions years from now, should be enough
    inline bool isWithinInterval(const int x, const int lower, const int upper)
    {
        return if (x >= lower && x <= upper);
    }
    bool isValid(const int day, const int month, const int year)
    {
        // assuming that year is always valid from negative numbers

        if (month > 12 || month < 1)
            throw std::runtime_error("Wrong month");
        if (month % 2 == 1)
        {
            if (!isWithinInterval(day, 1, 31) 
            {
                throw std::runtime_error("wrong day");
            }
        }
        else // even months
        {
            if (month == 2) // february case
            {
                // 1600 - include, 1700 exclude , 1800 exclude, 1900 exclude, 2000 include
                int upper = 28;
                if (year % 4 == 0)
                {
                    upper = 29;
                    if (year % 100 == 0 && year % 400 == 0)
                    {
                        upper = 29;
                    }
                    else if (year % 100 == 0 && year % 400 != 0)
                    {
                        upper = 28;
                    }
                }
                if (!isWithinInterval(day, 1, upper))
                {
                    throw std::runtime_error("wrong feb day");
                }
            }
            else // non-feb even months
            {
                if (!isWithinInterval(day, 1, 30))
                {
                    throw std::runtime_error("wrong day");
                }
            }
        }
    }

public:
    Date(): day(1), month(1), year(1970) {}
    int GetDay() const { return day;}
    int GetMonth() const { return month;}
    int GetYear() const { return year;}
    Date(const int day, const int month, const int year) {

    }
    Date(const Date& rhs)
    {
        
    }
};

ostream& operator<<(ostream& out, const Date& date)
{
    out << "Day = " << date.GetDay() << "; Month = " << date.GetMonth() << "; Year = " << date.GetYear() << endl;
    return out;
}

int main(int argc, char **argv)
{
    Date d;
    cout << d;
    Date second(d);
    cout << second;
}