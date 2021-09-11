#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

#include "date.hpp"

int main()
{
    using namespace project;
    /* 5 */
    Date d1;
    /* 31 */
    std::cout << "d1; " << d1 << "\n";
    /* 6 */
    Date d2{16,1,1999};
    std::cout << "d2; " << d2 << "\n";
    /* 7 */
    Date d3{"29/2/2000"};
    std::cout << "d3; " << d3 << "\n";
    /* 8 */
    Date d4{std::time(nullptr)};
    std::cout << "d4; " << d4 << "\n";
    /* 9 */
    std::cout << "d4 get month day; " << d4.get_month_day() << "\n";
    /* 10 */
    std::cout << "d4 get month; " << d4.get_month() << "\n";
    /* 11 */
    std::cout << "d4 get year; " << d4.get_year() << "\n";
    /* 12 */
    std::cout << "d4 get year day; " << d4.get_year_day() << "\n";
    /* 13 */
    std::cout << "d4 get week day; " << d4.get_week_day() << "\n";
    /* 14 */
    d4.set_month_day(15);
    std::cout << "d4 set month day(15); " << d4 << "\n";
    /* 15 */
    d4.set_month(12);
    std::cout << "d3 set month(12); " << d4 << "\n";
    /* 16 */
    d4.set_year(2010);
    std::cout << "d4 set year(2010); " << d4 << "\n";
    /* 17 */
    d1.set(12, 12, 2012);
    std::cout << "d1 set(12, 12, 2012); " << d1 << "\n";
    /* 18 */
    std::cout << "d1 - 12; " << d1 - 12 << " d1: " << d1 << "\n";
    /* 19 */
    d1 += 40;
    std::cout << "d1 += 40; " << d1 << "\n";
    /* 20 */
    d1 -= 40;
    std::cout << "d1 -= 40; " << d1 << "\n";
    /* 21, 22 */
    std::cout << "d2 before d2++; " << d2++ << "\n";
    for (auto i = 0; i < 410; ++i){
        std::cout << "d2; " << d2++ << "\n";
    }
    /* 23, 24 */
    std::cout << "d2 before d2--; " << d2-- << "\n";
    for (auto i = 0; i < 410; ++i){
        std::cout << "d2; " << d2-- << "\n";
    }
    std::cout << "d2; " << d2 << "\n";
    /* 26 */
    std::cout << "d2.get_year(); " << d2.get_year() << "\n";
    std::cout << "Date::isleap(d2.get_year()); " << std::boolalpha << Date::isleap(d2.get_year()) << "\n";
    /* 25 */
    std::vector<Date> dvec;
    dvec.reserve(1'000'000);
    for (auto i = 0; i < 1'000'000; ++i){
        dvec.push_back(Date::random_date());
    }
    std::sort(dvec.begin(), dvec.end());
    {
        auto new_end = std::unique(dvec.begin(), dvec.end());
        dvec.erase(new_end, dvec.end());
    }
    std::ofstream ofs{ "random_dates.txt" };
    if (!ofs) {
        std::cerr << "file open error\n";
        return 1;
    }
    for (const auto& d : dvec){
        ofs << d << "\n";
    }
    /* 28, 29 */
    std::cout << "dvec.front(); " << dvec.front() << "\n";
    std::cout << "dvec.back(); " << dvec.back() << "\n";
    std::cout << "dvec.size(); " << dvec.size() << "\n";
    std::cout << "dvec.front() - dvec.back(); " << dvec.front() - dvec.back() << "\n";
    std::cout << "dvec.front() + dvec.size() - 1; " << dvec.front() + dvec.size() - 1 << "\n";
    /* 27 */
    if (Date{} == Date{}){
        std::cout << Date{} << " == " << Date{} << "\n";
    }
    if (Date{} < Date{1, 2, 1900}){
        std::cout << Date{} << " < " << Date{1,2,1900} << "\n";
    }
    if (Date{1, 12, 2101} > Date{1, 12, 2100}){
        std::cout << Date{1, 12, 2101} << " > " << Date{1, 12, 2100} << "\n";
    }
    if (Date{1, 12, 2101} >= Date{1, 12, 2101}){
        std::cout << Date{1, 12, 2101} << " >= " << Date{1, 12, 2101} << "\n";
    }
    if (Date{1, 12, 2101} <= Date{1, 12, 2101}){
        std::cout << Date{1, 12, 2101} << " <= " << Date{1, 12, 2101} << "\n";
    }
    if (Date d5{Date::random_date()}, d6{Date::random_date()}; d5 != d6){
        std::cout << d5 << " != " << d6 << "\n";
    } else {
        std::cout << d5 << " == " << d6 << "\n";
    }
    /* 32 */
    Date d7;
    std::cout << "enter date: ";
    std::cin >> d7;
    std::cout << "d7; " << d7 << "\n";
    /* 30 */
    Date::Weekday w{Date::Weekday::Friday};
    std::cout << "w before w++; " << w++ << "\n";
    for (auto i = 0; i < 10; ++i){
        std::cout << "w; " << w++ << "\n";
    }
    std::cout << "w; " << w << "\n";
    std::cout << "w before w--; " << w-- << "\n";
    for (auto i = 0; i < 10; ++i){
        std::cout << "w; " << w-- << "\n";
    }
    std::cout << "w; " << w << "\n";
    return 0;
}

