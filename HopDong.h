#include "Date.h"
#include "SinhVien.h"
#include "Phong.h"
#pragma once

class HopDong {
private:
    std::string maHopDong;
    std::string maSinhVien;
    std::string maPhong;
    Date ngayBatDau;
    Date ngayKetThuc;

public:
    HopDong(const std::string& maHD = "", const std::string& maSV = "", const std::string& maP = "",
            const Date& start = Date(), const Date& end = Date())
        : maHopDong(maHD), maSinhVien(maSV), maPhong(maP), ngayBatDau(start), ngayKetThuc(end) {}

    void input() {
        std::cout << "Nhap ma hop dong: ";
        std::cin >> maHopDong;
        std::cout << "Nhap ma sinh vien: ";
        std::cin >> maSinhVien;
        std::cout << "Nhap ma phong: ";
        std::cin >> maPhong;
        std::cout << "Nhap ngay bat dau hop dong:\n";
        std::cin >> ngayBatDau;
        std::cout << "Nhap ngay ket thuc hop dong:\n";
        std::cin >> ngayKetThuc;
    }

    void display() const {
        std::cout << "Ma HD: " << maHopDong
                  << ", Ma SV: " << maSinhVien
                  << ", Ma phong: " << maPhong
                  << ", Ngay bat dau: " << ngayBatDau
                  << ", Ngay ket thuc: " << ngayKetThuc << std::endl;
    }

    std::string getMaHopDong() const { return maHopDong; }
    std::string getMaSinhVien() const { return maSinhVien; }
    std::string getMaPhong() const { return maPhong; }

    Date getNgayBatDau() const { return ngayBatDau; }
    Date getNgayKetThuc() const { return ngayKetThuc; }

    friend std::ostream& operator<<(std::ostream& os, const HopDong& hd) {
        os << hd.maHopDong << " " << hd.maSinhVien << " " << hd.maPhong << " "
           << hd.ngayBatDau << " " << hd.ngayKetThuc << "\n";
        return os;
    }

    friend std::istream& operator>>(std::istream& is, HopDong& hd) {
        is >> hd.maHopDong >> hd.maSinhVien >> hd.maPhong >> hd.ngayBatDau >> hd.ngayKetThuc;
        return is;
    }
};
