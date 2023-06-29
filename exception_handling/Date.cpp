#include <iostream>
#include "Date.hpp"


bool Date::isWithinInterval(const int x, const int lower, const int upper)
{
    return (x >= lower && x <= upper);
}

bool Date::isValid(const int day, const int month, const int year)
{
    // assuming that year is always valid from negative numbers

    if (month > 12 || month < 1)
        throw std::runtime_error("Wrong month");
    if (month % 2 == 1)
    {
        if (!isWithinInterval(day, 1, 31)) 
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

std::ostream& operator<<(std::ostream& out, const Date& date)
{
    out << "Day = " << date.GetDay() << "; Month = " << date.GetMonth() << "; Year = " << date.GetYear() << endl;
    return out;
}