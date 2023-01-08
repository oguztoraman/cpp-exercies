/*
 * date.hpp
 *
 * date class C++ header file.
 *
 * Copyright (C) 2022 Oğuz Toraman <oguz.toraman@protonmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#ifndef DATE_HPP
#define DATE_HPP

#include <ctime>
#include <iosfwd>
#include <string>
#include <cstdint>
#include <exception>

namespace date_time {
class Date {
public:
    static_assert (__cplusplus >= 202002L, "c++20 required!");

    static constexpr int year_base = 1900;  //1
    static constexpr int random_min_year = 1940;  //2
    static constexpr int random_max_year = 2020;  //3
    enum class Weekday {
        Sunday, Monday, Tuesday,
        Wednesday, Thursday, Friday, Saturday
    }; //4

    Date() = default; //5
    Date(int d, int m, int y);  //6
    Date(const char* p);  //7
    Date(const std::time_t& timer); //8

    [[nodiscard]]
    int get_month_day() const; //9

    [[nodiscard]]
    int get_month() const; //10

    [[nodiscard]]
    int get_year() const; //11

    [[nodiscard]]
    int get_year_day() const; //12

    [[nodiscard]]
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

    [[nodiscard]]
    static Date random_date(); //25

    [[nodiscard]]
    static constexpr bool isleap(int y)
    {
        return (((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0));
    } //26

    bool operator==(const Date&) const = default; //27

    [[nodiscard]]
    constexpr auto operator<=>(const Date& other) const noexcept //27
    {
        if (auto result = m_year <=> other.m_year; result != 0){
            return result;
        }
        if (auto result = m_month <=> other.m_month; result != 0){
            return result;
        }
        return m_day <=> other.m_day;
    }

    [[nodiscard]]
    std::string to_string() const;

    friend std::ostream& operator<<(std::ostream& os, const Date& date); //31
    friend std::istream& operator>>(std::istream& is, Date& date); //32

private:
    int m_day{1};
    int m_month{1};
    int m_year{1900};
    Weekday m_weekday{Weekday::Monday};

    void set_weekday();

    [[nodiscard]]
    static bool check_arguments(int d, int m, int y);

    [[nodiscard]]
    static std::string convert_month(int m);

    [[nodiscard]]
    static int convert_month(const std::string_view& m);

    static constexpr int year_table[4][13] = {
        { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
        { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
        { 0, 31, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30 },
        { 0, 31, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30 }
    };
};

[[nodiscard]]
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

    [[nodiscard]]
    const char* what() const noexcept override
    {
        return m_error.c_str();
    }
private:
    std::string m_error{"there is no such date!"};
};

} /* namespace date_time */

#endif /* DATE_HPP */
