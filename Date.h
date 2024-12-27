#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#pragma once


class Date {
private:
    int day, month, year;

    bool isValidDate() const {
        if (year < 1 || month < 1 || month > 12 || day < 1)
            return false;
        static const int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        int maxDay = daysInMonth[month - 1];
        if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0))
            maxDay = 29;
        return day <= maxDay;
    }

public:
    Date(int d = 1, int m = 1, int y = 2000) : day(d), month(m), year(y) {
        if (!isValidDate()) {
            day = 1;
            month = 1;
            year = 2000;
        }
    }

    // Hàm parse chuyển chuỗi thành đối tượng Date
    static Date parse(const std::string& dateStr, char delim = '-') {
        int d, m, y;
        char delimiter;
        std::istringstream iss(dateStr);
        iss >> d >> delimiter >> m >> delimiter >> y;

        if (!iss || delimiter != '-' || d < 1 || m < 1 || y < 1) {
            std::cerr << "Ngay khong hop le! Dat mac dinh la 01/01/2000.\n";
            return Date();
        }
        Date parsedDate(d, m, y);
        if (!parsedDate.isValidDate()) {
            std::cerr << "Ngay khong hop le! Dat mac dinh la 01/01/2000.\n";
            return Date();
        }
        return parsedDate;
    }

    bool operator<(const Date& other) const {
        if (year != other.year) return year < other.year;
        if (month != other.month) return month < other.month;
        return day < other.day;
    }

    bool operator==(const Date& other) const {
        return day == other.day && month == other.month && year == other.year;
    }

    friend std::ostream& operator<<(std::ostream& os, const Date& date) {
        os << std::setw(2) << std::setfill('0') << date.day << "/"
           << std::setw(2) << std::setfill('0') << date.month << "/"
           << date.year;
        return os;
    }

    // Hàm >> vẫn giữ nhưng đơn giản hơn, không xử lý logic chuỗi
    friend std::istream& operator>>(std::istream& is, Date& date) {
        std::string dateStr;
        std::cout << "Nhap ngay (dd-mm-yyyy): ";
        is >> dateStr;
        date = Date::parse(dateStr);
        return is;
    }



    std::string toString() const {
        std::ostringstream oss;
        oss << (day < 10 ? "0" : "") << day << "/"
            << (month < 10 ? "0" : "") << month << "/"
            << year;
        return oss.str();
    }

//    friend std::istream& operator>>(std::istream& is, Date& date) {
//        std::cout << "Nhap ngay (dd mm yyyy): ";
//        is >> date.day >> date.month >> date.year;
//        if (!date.isValidDate()) {
//            std::cerr << "Ngay khong hop le! Dat mac dinh la 01/01/2000.\n";
//            date = Date();
//        }
//        return is;
//    }
};
