#include <iostream>
#include <ctime>

using namespace std;

class Date
{
private:
    int day; //1 to 31
    int month; // 1 to 12
    int year; // from -2 billion to 2 billions years from now, should be enough
    bool isWithinInterval(const int x, const int lower, const int upper);
    bool isValid(const int day, const int month, const int year);

public:
    Date(): day(1), month(1), year(1970) {}
    int GetDay() const { return day;}
    int GetMonth() const { return month;}
    int GetYear() const { return year;}
    Date(const int day, const int month, const int year) { if (isValid(day, month, year)) { this->day = day, this->month = month, this->year = year; }};
    Date(const Date& rhs) { this->day = rhs.day; this->month = rhs.month; this->year = rhs.year; };
    friend ostream& operator<<(ostream& out, const Date& d);
    static Date now() {  time_t now = time(0); tm *gmtm = gmtime(&now); return Date(gmtm->tm_mday, gmtm->tm_mon + 1, gmtm->tm_year + 1900); }
};