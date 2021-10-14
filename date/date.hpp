#ifndef DATE_HPP
#define DATE_HPP

#include <iosfwd>
#include <ctime>
#include <string>
#include <exception>
#include <cstdint>

namespace project {
class Date {
public:
    static constexpr int year_base = 1900;  //1
    static constexpr int random_min_year = 1940;  //2
    static constexpr int random_max_year = 2020;  //3
    enum class Weekday {Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday}; //4

    Date() = default; //5
    Date(int d, int m, int y);  //6
    Date(const char* p);  //7
    Date(const std::time_t& timer); //8

    int get_month_day() const; //9
    int get_month() const; //10
    int get_year() const; //11
    int get_year_day() const; //12
    Weekday get_week_day() const; //13

    Date& set_month_day(int day); //14
    Date& set_month(int month); //15
    Date& set_year(int year); //16
    Date& set(int d, int m, int y); //17

    Date operator-(int day) const; //18
    Date& operator+=(int day); //19
    Date& operator-=(int day); //20
    Date& operator++(); //21
    Date operator++(int); //22
    Date& operator--(); //23
    Date operator--(int); //24

    static Date random_date(); //25
    static constexpr bool isleap(int y)
    {
        return (((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0));
    } //26

    friend bool operator<(const Date& d1, const Date& d2); //27
    friend bool operator==(const Date& d1, const Date& d2); //27

    friend std::ostream& operator<<(std::ostream& os, const Date& date); //31
    friend std::istream& operator>>(std::istream& is, Date& date); //32

private:
    int m_day{1};
    int m_month{1};
    int m_year{1900};
    Weekday m_weekday{Weekday::Monday};

    void set_weekday();

    static bool check_arguments(int d, int m, int y);
    static std::string convert_month(int m);
    static int convert_month(const std::string_view& m);
    static constexpr int year_table[4][13] = {
        { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
        { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
        { 0, 31, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30 },
        { 0, 31, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30 }
    };
};

bool operator<=(const Date& d1, const Date& d2); //27
bool operator>(const Date& d1, const Date& d2); //27
bool operator>=(const Date& d1, const Date& d2); //27
bool operator!=(const Date& d1, const Date& d2); //27

std::int64_t operator-(const Date& d1, const Date& d2); //28
Date operator+(const Date& date, int n); //29
Date operator+(int n, const Date& date); //29

Date::Weekday& operator++(Date::Weekday& r); //30
Date::Weekday operator++(Date::Weekday& r, int); //30
Date::Weekday& operator--(Date::Weekday& r); //30
Date::Weekday operator--(Date::Weekday& r, int); //30

std::ostream& operator<<(std::ostream& os, const Date::Weekday&_w);

class bad_day : public std::exception {
public:
    bad_day() = default;
    bad_day(std::string error) : m_error{std::move(error)}{ }

    const char* what() const noexcept override
    {
        return m_error.c_str();
    }
private:
    std::string m_error{"there is no such date!"};
};

}
#endif // DATE_HPP
