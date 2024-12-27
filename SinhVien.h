#include <iostream>
#include <string>
#include "Date.h"
#include "LinkedList.h"
#pragma once


using namespace std;
class SinhVien {
private:
    std::string maSinhVien;
    std::string tenSinhVien;
    std::string soDienThoai;
    Date ngaySinh;
    bool gioiTinh;
    std::string maPhong;
    std::string maHopDong;

public:
    SinhVien() = default;

    SinhVien(const std::string& maSV, const std::string& tenSV, const std::string& sdt, const Date& ns, bool gt, const std::string& maP, const std::string& maHD)
    :maSinhVien(maSV), tenSinhVien(tenSV), soDienThoai(sdt), ngaySinh(ns), gioiTinh(gt), maPhong(maP), maHopDong(maHD) {}

    std::string getMaSinhVien() const { return maSinhVien; }
    std::string getTenSinhVien() const { return tenSinhVien; }
    std::string getSoDienThoai() const { return soDienThoai; }
    Date getNgaySinh() const { return ngaySinh; }
    bool isGioiTinh() const { return gioiTinh; }

    std::string getMaPhong() const { return maPhong; }
    void setMaPhong(const std::string& ma) { maPhong = ma; }

    std::string getMaHopDong() const { return maHopDong; }
    void setMaHopDong(const std::string& ma) { maHopDong = ma; }

    void input() {
        std::cout << "Nhap ma sinh vien: ";
        std::cin >> maSinhVien;
        std::cout << "Nhap ten sinh vien: ";
        std::cin.ignore();
        std::getline(std::cin, tenSinhVien);
        std::cout << "Nhap so dien thoai: ";
        std::cin >> soDienThoai;
        std::cout << "Nhap ngay sinh:\n";
        std::cin >> ngaySinh;
        std::cout << "Nhap gioi tinh (1: nam, 0: nu): ";
        std::cin >> gioiTinh;
//        std::cout << "Nhap ma phong: ";
//        std::cin >> maPhong;
//        std::cout << "Nhap ma hop dong: ";
//        std::cin >> maHopDong;
    }

    void display() const {
        std::cout << "Ma SV: " << maSinhVien
                  << ", Ten: " << tenSinhVien
                  << ", So DT: " << soDienThoai
                  << ", Ngay sinh: " << ngaySinh
                  << ", Gioi tinh: " << gioiTinh
                  << ", Ma phong: " << maPhong
                  << ", Ma hop dong: " << maHopDong << std::endl;
    }

//    std::string getMaSV() const { return maSinhVien; }

    operator std::string() const {
        return maSinhVien;
    }
};
