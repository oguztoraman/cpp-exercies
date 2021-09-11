#include <iostream>
#include <algorithm>
#include <random>

#include "date.hpp"

namespace project {

Date::Date(const int& _d, const int& _m, const int& _y)
{
    set(_d, _m, _y);
}

Date::Date(const char* _p)
{
    if (std::string date{_p}; std::count(date.begin(), date.end(), '/') == 2) {
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

Date::Date(const std::time_t& _timer)
{
    std::string date{std::ctime(&_timer)};
    int d = std::stoi(date.substr(8, date.find_first_of(' ', 8)));
    int m = Date::convert_month(date.substr(4, 3));
    int y = std::stoi(date.substr(date.find_last_of(' ')));
    set(d, m, y);
}

bool Date::check_arguments(const int& _d, const int& _m, const int& _y)
{
    if ((_y >= year_base) && (_m >= 1 && _m <= 12)){
        if (_m == 4 || _m == 6 || _m == 9 || _m == 11){
            return (_d >= 1 && _d <= 30);
        } else if (_m == 2){
            if (isleap(_y)){
                return (_d >= 1 && _d <= 29);
            } else {
                return (_d >= 1 && _d <= 28);
            }
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

std::string Date::convert_month(const int& _m)
{
    switch (_m){
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

int Date::convert_month(const std::string& _m)
{
    if (_m == "Jan"){ return 1;}
    if (_m == "Feb"){ return 2;}
    if (_m == "Mar"){ return 3;}
    if (_m == "Apr"){ return 4;}
    if (_m == "May"){ return 5;}
    if (_m == "Jun"){ return 6;}
    if (_m == "Jul"){ return 7;}
    if (_m == "Aug"){ return 8;}
    if (_m == "Sep"){ return 9;}
    if (_m == "Oct"){ return 10;}
    if (_m == "Nov"){ return 11;}
    if (_m == "Dec"){ return 12;}
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
            if (isleap(m_year)){
                days += 29;
            } else {
                days += 28;
            }
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
        if (isleap(i)){
            days += 366;
        } else {
            days += 365;
        }
    }
    days += get_year_day();
    days %= 7;
    m_weekday = static_cast<Weekday>(days);
}

Date& Date::set_month_day(const int& _day)
{
    set(_day, m_month, m_year);
    return *this;
}

Date& Date::set_month(const int& _month)
{
    set(m_day, _month, m_year);
    return *this;
}

Date& Date::set_year(const int& _year)
{
    set(m_day, m_month, _year);
    return *this;
}

Date& Date::set(const int& _d, const int& _m, const int& _y)
{
    if (check_arguments(_d, _m, _y)){
        m_day = _d;
        m_month = _m;
        m_year = _y;
        set_weekday();
    } else {
        std::cerr << "wrong argument(s)\n";
    }
    return *this;
}

Date Date::operator-(const int& _day) const
{
    Date temp{*this};
    for(auto i = 0; i < _day; ++i){
        --temp;
    }
    return temp;
}

Date& Date::operator+=(const int& _day)
{
    for(auto i = 0; i < _day; ++i){
        operator++();
    }
    return *this;
}

Date& Date::operator-=(const int& _day)
{
    for(auto i = 0; i < _day; ++i){
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
        if (isleap(m_year)){
            set(29, m_month - 1, m_year);
        } else {
            set(28, m_month - 1, m_year);
        }
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

bool operator<(const Date& _d1, const Date& _d2)
{
    if (_d1.m_year < _d2.m_year){
        return true;
    }
    if (_d1.m_year == _d2.m_year){
        if ( _d1.m_month < _d2.m_month){
            return true;
        } else if (_d1.m_month == _d2.m_month){
            return (_d1.m_day < _d2.m_day);
        }
    }
    return false;
}

bool operator==(const Date& _d1, const Date& _d2)
{
    return (_d1.m_year == _d2.m_year &&
            _d1.m_month == _d2.m_month &&
            _d1.m_day == _d2.m_day);
}

bool operator<=(const Date& _d1, const Date& _d2)
{
    return !(_d1 > _d2);
}

bool operator>(const Date& _d1, const Date& _d2)
{
    return (_d2 < _d1);
}

bool operator>=(const Date& _d1, const Date& _d2)
{
    return !(_d1 < _d2);
}

bool operator!=(const Date& _d1, const Date&_d2)
{
    return !( _d1 == _d2);
}

long operator-(const Date& _d1, const Date& _d2)
{
    if (_d1 == _d2){ return 0;}
    if (_d1.get_year() == _d2.get_year()){
        return (_d1.get_year_day() - _d2.get_year_day());
    } else {
        bool smaller{false};
        int year_diff = _d1.get_year() - _d2.get_year();
        if (year_diff < 0){
            smaller = true;
            year_diff *= -1;
        }
        long day_diff{};
        for (auto i = 0; i < year_diff; ++i){
            if (Date::isleap(i)){
                day_diff += 366;
            } else {
                day_diff += 365;
            }
        }
        if (smaller){
            day_diff += _d2.get_year_day() - _d1.get_year_day();
            return (day_diff * -1);
        } else {
            day_diff += _d1.get_year_day() - _d2.get_year_day();
            return day_diff;
        }
    }
}

Date operator+(const Date& _date, const int& _n)
{
    Date temp{_date};
    for (auto i = 0; i < _n; ++i){
        ++temp;
    }
    return temp;
}

Date operator+(const int& _n, const Date& _date)
{
    return operator+(_date, _n);
}

Date::Weekday& operator++(Date::Weekday& _r)
{
    int weekday = static_cast<int>(_r);
    if (weekday == 6) {
        _r = Date::Weekday::Sunday;
    } else {
        ++weekday;
        _r = static_cast<Date::Weekday>(weekday);
    }
    return _r;
}

Date::Weekday operator++(Date::Weekday& _r, int)
{
    Date::Weekday temp{_r};
    operator++(_r);
    return temp;
}

Date::Weekday& operator--(Date::Weekday& _r)
{
    int weekday = static_cast<int>(_r);
    if (weekday == 0) {
        _r = Date::Weekday::Saturday;
    } else {
        --weekday;
        _r = static_cast<Date::Weekday>(weekday);
    }
    return _r;
}

Date::Weekday operator--(Date::Weekday& _r, int)
{
    Date::Weekday temp{_r};
    operator--(_r);
    return temp;
}

Date Date::random_date()
{
    std::mt19937 gen(std::random_device{}());
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

std::ostream& operator<<(std::ostream& _os, const Date& _date)
{
    _os << _date.m_day << " " << Date::convert_month(_date.m_month)
        << " " << _date.m_year << " " << _date.m_weekday;
    return _os;
}

std::ostream& operator<<(std::ostream& _os, const Date::Weekday& _w)
{
    switch (_w){
    case Date::Weekday::Sunday:    _os << "Pazar"; break;
    case Date::Weekday::Monday:    _os << "Pazartesi"; break;
    case Date::Weekday::Tuesday:   _os << "Sali"; break;
    case Date::Weekday::Wednesday: _os << "Carsamba"; break;
    case Date::Weekday::Thursday:  _os << "Persembe"; break;
    case Date::Weekday::Friday:    _os << "Cuma"; break;
    case Date::Weekday::Saturday:  _os << "Cumartesi"; break;
    }
    return _os;
}

std::istream& operator>>(std::istream& _is, Date& _date)
{
    std::string input;
    _is >> input;
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
    return _is;
}

} //namespace
