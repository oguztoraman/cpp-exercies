#ifndef DATE_H
#define DATE_H

#include <iosfwd>
#include <ctime>
#include <string>

namespace project {
class Date {
public:
    static constexpr int year_base = 1900;  //1
    static constexpr int random_min_year = 1940;  //2
    static constexpr int random_max_year = 2020;  //3
    enum class Weekday {Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday}; //4

    Date() = default; //5
    Date(const int& _d, const int& _m, const int& _y);  //6
    Date(const char* _p);  //7
    Date(const std::time_t& _timer); //8

    int get_month_day() const; //9
    int get_month() const; //10
    int get_year() const; //11
    int get_year_day() const; //12
    Weekday get_week_day() const; //13

    Date& set_month_day(const int& _day); //14
    Date& set_month(const int& _month); //15
    Date& set_year(const int& _year); //16
    Date& set(const int& _d, const int& _m, const int& _y); //17

    Date operator-(const int& _day) const; //18
    Date& operator+=(const int& _day); //19
    Date& operator-=(const int& _day); //20
    Date& operator++(); //21
    Date operator++(int); //22
    Date& operator--(); //23
    Date operator--(int); //24

    static Date random_date(); //25
    static constexpr bool isleap(const int& _y)
    {
        if (((_y % 4 == 0) && (_y % 100 != 0)) || (_y % 400 == 0)){
            return true;
        }
        return false;
    } //26

    friend bool operator<(const Date& _d1, const Date& _d2); //27
    friend bool operator==(const Date& _d1, const Date& _d2); //27

    friend std::ostream& operator<<(std::ostream& _os, const Date& _date); //31
    friend std::istream& operator>>(std::istream& _is, Date& _date); //32

private:
    int m_day{1};
    int m_month{1};
    int m_year{1900};
    Weekday m_weekday{Weekday::Monday};

    void set_weekday();

    static bool check_arguments(const int& _d, const int& _m, const int& _y);
    static std::string convert_month(const int& _m);
    static int convert_month(const std::string& _m);
};

bool operator<=(const Date& _d1, const Date& _d2); //27
bool operator>(const Date& _d1, const Date& _d2); //27
bool operator>=(const Date& _d1, const Date& _d2); //27
bool operator!=(const Date& _d1, const Date& _d2); //27

long operator-(const Date& _d1, const Date& _d2); //28
Date operator+(const Date& _date, const int& _n); //29
Date operator+(const int& _n, const Date& _date); //29

Date::Weekday& operator++(Date::Weekday& r); //30
Date::Weekday operator++(Date::Weekday& r, int); //30
Date::Weekday& operator--(Date::Weekday& r); //30
Date::Weekday operator--(Date::Weekday& r, int); //30

std::ostream& operator<<(std::ostream& _os, const Date::Weekday& _w);
}
#endif
