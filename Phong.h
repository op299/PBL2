#include <iostream>
#include <string>
#include "LinkedList.h"
#include "SinhVien.h"
#pragma once


class Phong {
private:
    std::string maPhong;
    bool loaiPhong;
    int sucChua;
    int tienPhong;
    LinkedList<std::string> danhSachSinhVien; // Lưu mã sinh viên
    LinkedList<std::string> danhSachHopDong;  // Lưu mã hợp đồng

public:
    Phong(const std::string& ma = "", bool loai = true, int sc = 4, int tien = 500000)
        : maPhong(ma), loaiPhong(loai), sucChua(sc), tienPhong(tien) {}

    std::string getMaPhong() const { return maPhong; }
    bool getLoaiPhong() const { return loaiPhong; }
    int getSucChua() const { return sucChua; }
    int getTienPhong() const { return tienPhong; }

    void input() {
        std::cout << "Nhap ma phong: ";
        std::cin >> maPhong;
        std::cout << "Loai phong (1: nam, 0: nu): ";
        std::cin >> loaiPhong;
        std::cout << "Suc chua: ";
        std::cin >> sucChua;
        std::cout << "Tien phong: ";
        std::cin >> tienPhong;
    }

    // Phương thức trả về danh sách sinh viên
    LinkedList<std::string>& getDanhSachSinhVien() {
        return danhSachSinhVien;
    }

    void addSinhVien(const std::string& maSV) {
        if (danhSachSinhVien.getSize() < sucChua)
            danhSachSinhVien.add(maSV);
        else
            std::cout << "Phong da day. Khong the them sinh vien.\n";
    }

    void removeSinhVien(const std::string& maSV) {
        danhSachSinhVien.remove(maSV);
    }

    void addHopDong(const std::string& maHD) {
        danhSachHopDong.add(maHD);
    }

    void removeHopDong(const std::string& maHD) {
        danhSachHopDong.remove(maHD);
    }

    void display() const {
        std::cout << "Ma phong: " << maPhong
                  << ", Loai phong: " << (loaiPhong ? "Nam" : "Nu")
                  << ", Suc chua: " << sucChua
                  << ", Tien phong: " << tienPhong
                  << "\nDanh sach sinh vien: ";
        danhSachSinhVien.display();
        std::cout << "Danh sach hop dong: ";
        danhSachHopDong.display();
        std::cout << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os, const Phong& p) {
        os << p.maPhong << " " << p.loaiPhong << " " << p.sucChua << " " << p.tienPhong << "\n";
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Phong& p) {
        is >> p.maPhong >> p.loaiPhong >> p.sucChua >> p.tienPhong;
        return is;
    }
};
