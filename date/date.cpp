#include <iostream>
#include <algorithm>
#include <random>

#include "date.hpp"

namespace project {

Date::Date(int d, int m, int y)
{
    set(d, m, y);
}

Date::Date(const char* p)
{
    if (std::string date{p}; std::count(date.begin(), date.end(), '/') == 2) {
        auto index = date.find('/');
        int d = std::stoi(date.substr(0, index));
        date.erase(0, index + 1);
        index = date.find('/');
        int m = std::stoi(date.substr(0, index));
        date.erase(0, index + 1);
        int y = std::stoi(date);
        set(d, m, y);
    } else {
        std::cerr << "wrong input format\n";
    }
}

Date::Date(const std::time_t& timer)
{
    std::string date{std::ctime(&timer)};
    int d = std::stoi(date.substr(8, date.find_first_of(' ', 8)));
    int m = Date::convert_month(date.substr(4, 3));
    int y = std::stoi(date.substr(date.find_last_of(' ')));
    set(d, m, y);
}

bool Date::check_arguments(int d, int m, int y)
{
    if ((y >= year_base) && (m >= 1 && m <= 12)){
        if (m == 4 || m == 6 || m == 9 || m == 11){
            return (d >= 1 && d <= 30);
        } else if (m == 2){
            return (d >= 1 && february[isleap(y)]);
        } else {
            return (_d >= 1 && _d <= 31);
        }
    }
    return false;
}

int Date::get_month_day() const
{
    return m_day;
}

int Date::get_month() const
{
    return m_month;
}

std::string Date::convert_month(int m)
{
    switch (m){
    case 1:  return "Ocak";
    case 2:  return "Subat";
    case 3:  return "Mart";
    case 4:  return "Nisan";
    case 5:  return "Mayis";
    case 6:  return "Haziran";
    case 7:  return "Temmuz";
    case 8:  return "Agustos";
    case 9:  return "Eylul";
    case 10: return "Ekim";
    case 11: return "Kasim";
    case 12: return "Aralik";
    default: return ""; // wrong argument
    }
}

int Date::convert_month(const std::string& m)
{
    if (m == "Jan"){ return 1;}
    if (m == "Feb"){ return 2;}
    if (m == "Mar"){ return 3;}
    if (m == "Apr"){ return 4;}
    if (m == "May"){ return 5;}
    if (m == "Jun"){ return 6;}
    if (m == "Jul"){ return 7;}
    if (m == "Aug"){ return 8;}
    if (m == "Sep"){ return 9;}
    if (m == "Oct"){ return 10;}
    if (m == "Nov"){ return 11;}
    if (m == "Dec"){ return 12;}
    return -1; // wrong argument
}

int Date::get_year() const
{
    return m_year;
}

int Date::get_year_day() const
{
    int days{};
    for (auto i = 1; i < m_month; ++i){
        if (i == 4 || i == 6 || i == 9 || i == 11){
            days += 30;
        } else if (i == 2){
            days += february[isleap(m_year)];
        } else {
            days += 31;
        }
    }
    days += m_day;
    return days;
}

Date::Weekday Date::get_week_day() const
{
    return m_weekday;
}

void Date::set_weekday()
{
    unsigned long long days{};
    for (auto i = year_base; i < m_year; ++i){
        isleap(i) ? days += 366 : days += 365;
    }
    days += get_year_day();
    days %= 7;
    m_weekday = static_cast<Weekday>(days);
}

Date& Date::set_month_day(int _day)
{
    set(_day, m_month, m_year);
    return *this;
}

Date& Date::set_month(int _month)
{
    set(m_day, _month, m_year);
    return *this;
}

Date& Date::set_year(int _year)
{
    set(m_day, m_month, _year);
    return *this;
}

Date& Date::set(int d, int m, int y)
{
    if (check_arguments(d, m, y)){
        m_day = d;
        m_month = m;
        m_year = y;
        set_weekday();
    } else {
        std::cerr << "wrong argument(s)\n";
    }
    return *this;
}

Date Date::operator-(int day) const
{
    Date temp{*this};
    for(auto i = 0; i < day; ++i){
        --temp;
    }
    return temp;
}

Date& Date::operator+=(int day)
{
    for(auto i = 0; i < day; ++i){
        operator++();
    }
    return *this;
}

Date& Date::operator-=(int day)
{
    for(auto i = 0; i < day; ++i){
        operator--();
    }
    return *this;
}

Date& Date::operator++()
{
    bool inc_month{false}, inc_year{false};
    if ((m_month == 4 || m_month == 6 || m_month == 9 || m_month == 11) && m_day == 30){
        inc_month = true;
    } else if (m_month == 2 && ((isleap(m_year) && m_day == 29) || (!isleap(m_year) && m_day == 28))){
        inc_month = true;
    } else if (m_month == 12 && m_day == 31){
        inc_year = true;
    } else if (m_day == 31){
        inc_month = true;
    }
    if (inc_month){
        set(1, m_month + 1, m_year);
    } else if (inc_year){
        set(1, 1, m_year + 1);
    } else {
        set_month_day(m_day + 1);
    }
    return *this;
}

Date Date::operator++(int)
{
    Date temp{*this};
    operator++();
    return temp;
}

Date& Date::operator--() //ok
{
    bool dec_month_31{false}, dec_month_30{false};
    bool dec_year{false}, dec_day{true};
    if ((m_month == 5 || m_month == 7 || m_month == 10 || m_month == 12) && m_day == 1){
        dec_month_30 = true;
    } else if (m_month == 3 && m_day == 1){
        set(february[isleap(m_year)]), m_month - 1, m_year);
        dec_day = false;
    } else if (m_month == 1 && m_day == 1){
        dec_year = true;
    } else if (m_day == 1){
        dec_month_31 = true;
    }
    if (dec_month_30){
        set(30, m_month - 1, m_year);
    } else if (dec_month_31){
        set(31, m_month - 1, m_year);
    } else if (dec_year){
        set(31, 12, m_year - 1);
    } else if (dec_day){
        set_month_day(m_day - 1);
    }
    return *this;
}

Date Date::operator--(int)
{
    Date temp{*this};
    operator--();
    return temp;
}

bool operator<(const Date& d1, const Date& d2)
{
    return (std::tuple{d1.m_year, d1.m_month, d1.m_day} < 
           std::tuple{d2.m_year, d2.m_month, d2.m_day});
}

bool operator==(const Date& d1, const Date& d2)
{
    return (d1.m_year == d2.m_year &&
            d1.m_month == d2.m_month &&
            d1.m_day == d2.m_day);
}

bool operator<=(const Date& d1, const Date& d2)
{
    return !(d1 > d2);
}

bool operator>(const Date& d1, const Date& d2)
{
    return (d2 < d1);
}

bool operator>=(const Date& d1, const Date& d2)
{
    return !(d1 < d2);
}

bool operator!=(const Date& d1, const Date& d2)
{
    return !( d1 == d2);
}

long operator-(const Date& d1, const Date& d2)
{
    if (d1 == d2){ return 0;}
    if (d1.get_year() == d2.get_year()){
        return (d1.get_year_day() - d2.get_year_day());
    } else {
        bool negative{false};
        int year_diff = d1.get_year() - d2.get_year();
        if (year_diff < 0){
            negative = true;
            year_diff *= -1;
        }
        long day_diff{};
        for (auto i = 0; i < year_diff; ++i){
            Date::isleap(i) ? day_diff += 366 : day_diff += 365;
        }
        if (negative){
            day_diff += _d2.get_year_day() - _d1.get_year_day();
            return (-day_diff);
        } else {
            day_diff += _d1.get_year_day() - _d2.get_year_day();
            return day_diff;
        }
    }
}

Date operator+(const Date& date, int n)
{
    Date temp{date};
    for (auto i = 0; i < n; ++i){
        ++temp;
    }
    return temp;
}

Date operator+(int n, const Date& date)
{
    return operator+(date, n);
}

Date::Weekday& operator++(Date::Weekday& r)
{
    int weekday = static_cast<int>(r);
    if (weekday == 6) {
        r = Date::Weekday::Sunday;
    } else {
        ++weekday;
        r = static_cast<Date::Weekday>(weekday);
    }
    return r;
}

Date::Weekday operator++(Date::Weekday& r, int)
{
    Date::Weekday temp{r};
    operator++(r);
    return temp;
}

Date::Weekday& operator--(Date::Weekday& r)
{
    int weekday = static_cast<int>(r);
    if (weekday == 0) {
        r = Date::Weekday::Saturday;
    } else {
        --weekday;
        r = static_cast<Date::Weekday>(weekday);
    }
    return r;
}

Date::Weekday operator--(Date::Weekday& r, int)
{
    Date::Weekday temp{r};
    operator--(r);
    return temp;
}

Date Date::random_date()
{
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution rand_d(1, 31);
    std::uniform_int_distribution rand_m(1, 12);
    std::uniform_int_distribution rand_y(random_min_year, random_max_year);
    int d{}, m{}, y{};
    while (!check_arguments(d, m, y)){
        d = rand_d(gen);
        m = rand_m(gen);
        y = rand_y(gen);
    }
    return Date{d, m, y};
}

std::ostream& operator<<(std::ostream& os, const Date& date)
{
    std::ostringstream oss;
    oss << date.m_day << " " << Date::convert_month(date.m_month)
        << " " << date.m_year << " " << date.m_weekday;
    return os << oss.str();
}

std::ostream& operator<<(std::ostream& os, const Date::Weekday& w)
{
    switch (w){
    case Date::Weekday::Sunday:    os << "Pazar"; break;
    case Date::Weekday::Monday:    os << "Pazartesi"; break;
    case Date::Weekday::Tuesday:   os << "Sali"; break;
    case Date::Weekday::Wednesday: os << "Carsamba"; break;
    case Date::Weekday::Thursday:  os << "Persembe"; break;
    case Date::Weekday::Friday:    os << "Cuma"; break;
    case Date::Weekday::Saturday:  os << "Cumartesi"; break;
    }
    return os;
}

std::istream& operator>>(std::istream& is, Date& date)
{
    std::string input;
    is >> input;
    int nondigits{};
    for (auto& c : input){
        if (!std::isdigit(c)){
            ++nondigits;
        }
    }
    if (nondigits == 2){
        int d = std::stoi(input.substr(0, input.find_first_not_of("0123456789")));
        input.erase(0, input.find_first_not_of("0123456789") + 1);
        int m = std::stoi(input.substr(0, input.find_first_not_of("0123456789")));
        input.erase(0, input.find_first_not_of("0123456789") + 1);
        int y = std::stoi(input);
        _date.set(d, m, y);
    } else {
        std::cout << "wrong input format\n";
    }
    return is;
}

} //namespace
