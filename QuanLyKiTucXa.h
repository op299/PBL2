#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>
#include "Date.h"
#include "LinkedList.h"
#include "SinhVien.h"
#include "Phong.h"
#include "HopDong.h"
#pragma once

class QuanLyKiTucXa {
private:
    LinkedList<SinhVien> danhSachSinhVien;
    LinkedList<SinhVien> danhSachCho;
    LinkedList<Phong> danhSachPhong;
    LinkedList<HopDong> danhSachHopDong;
    std::string tenDangNhap;
    std::string matKhau;

public:
    QuanLyKiTucXa() : tenDangNhap("admin"), matKhau("1234") {}

    void menu();

//     Hàm ghi dữ liệu vào file
//     void saveToFile(const std::string& fileName);

    bool dangNhap() {
        std::string user, pass;

        std::cout << "Nhap ten dang nhap: ";
        std::cin >> user;
        std::cout << "Nhap mat khau: ";
        std::cin >> pass;

        if (user == tenDangNhap && pass == matKhau) {
            std::cout << "Dang nhap thanh cong.\n";
            return true;
        } else {
            std::cout << "Ten dang nhap hoac mat khau sai. Thu lai.\n";
            return false;
        }
    }


    void themHopDong() {
        HopDong hd;
        hd.input();

        // Tìm sinh viên và phòng
        SinhVien* sv = danhSachSinhVien.findIf([&](const SinhVien& s) {
            return s.getMaSinhVien() == hd.getMaSinhVien();
        });

        Phong* phong = danhSachPhong.findIf([&](const Phong& p) {
            return p.getMaPhong() == hd.getMaPhong();
        });

        if (sv != nullptr) {
            std::cout << "Sinh vien duoc tim thay: " << sv->getMaSinhVien() << std::endl;
        } else {
            std::cout << "Khong tim thay sinh vien!" << std::endl;
        }

        if (phong != nullptr) {
            std::cout << "Phong duoc tim thay: " << phong->getMaPhong() << std::endl;
        } else {
            std::cout << "Khong tim thay phong!" << std::endl;
        }


        danhSachHopDong.add(hd);
        phong->addSinhVien(sv->getMaSinhVien());
        phong->addHopDong(hd.getMaHopDong());
        std::cout << "Them hop dong thanh cong.\n";
    }
    
    void xemDanhSachHopDong() const {
        if (danhSachHopDong.isEmpty()) {
            std::cout << "Danh sach hop dong trong.\n";
            return;
        }

        std::cout << "\n=== Danh Sach Hop Dong ===\n";
        danhSachHopDong.forEach([](const HopDong& hd) {
            hd.display(); // Gọi phương thức hiển thị thông tin hợp đồng trong lớp HopDong
        });
    }

    void xemDanhSachCho() const {
        if (danhSachCho.isEmpty()) {
            std::cout << "Danh sach cho xep phong trong.\n";
            return;
        }

        std::cout << "\n=== Danh Sach Cho Xep Phong ===\n";
        danhSachCho.forEach([](const SinhVien& sv) {
            sv.display(); // Hàm `display()` hiển thị thông tin sinh viên
        });
    }

    void themSinhVien() {
        SinhVien sv;
        sv.input(); // Hàm `input()` nhập thông tin sinh viên

        // Kiểm tra mã sinh viên đã tồn tại hay chưa
        if (danhSachSinhVien.findIf([&](const SinhVien& s) { return s.getMaSinhVien() == sv.getMaSinhVien(); })) {
            std::cout << "Ma sinh vien da ton tai. Khong the them moi.\n";
            return;
        }

        // Thêm sinh viên vào danh sách chính
        danhSachSinhVien.add(sv);

            danhSachCho.add(sv); // Thêm vào danh sách chờ nếu mã phòng trống
            std::cout << "Da them vao danh sach cho.\n";
    }

    void xemDanhSachSinhVien() const {
        if (danhSachSinhVien.isEmpty()) {
            std::cout << "Danh sach sinh vien.\n";
            return;
        }

        auto current = danhSachSinhVien.begin();  // Lấy con trỏ đầu danh sách
        while (current != danhSachSinhVien.end()) {
            current->data.display();  // Gọi display trên dữ liệu (SinhVien)
            current = current->next;  // Chuyển sang Node tiếp theo
        }
    }

    void themPhong() {
        Phong phong;
        phong.input(); 

        // Kiểm tra mã phòng đã tồn tại hay chưa
       if (danhSachPhong.findIf([&](const Phong& p) { return p.getMaPhong() == phong.getMaPhong(); })) {
            std::cout << "Ma phong da ton tai. Khong the them moi.\n";
            return;
        }

        danhSachPhong.add(phong); // Thêm vào danh sách phòng
        std::cout << "Them phong thanh cong.\n";
    }



    void xemDanhSachPhong() const {
        if (danhSachPhong.isEmpty()) {
            std::cout << "Danh sach phong.\n";
            return;
        }

        // Duyệt qua danh sách bằng con trỏ Node*
        auto current = danhSachPhong.begin();  // Lấy con trỏ đầu danh sách
        while (current != danhSachPhong.end()) {
            current->data.display();           // Gọi phương thức display của từng phòng
            current = current->next;           // Di chuyển đến phần tử tiếp theo
        }
    }

    void loadFromFile(const std::string& fileName) {
        std::ifstream file(fileName);
        if (!file.is_open()) {
            throw std::runtime_error("Khong mo duoc file: " + fileName);
        }

        std::string line;
        std::string section;

        while (std::getline(file, line)) {
            if (line.empty() || line[0] == '#') {
                section = line; // Ghi nhận phần tiêu đề (#SINHVIEN, #PHONGO, #HOPDONG)
                continue;
            }

            std::istringstream iss(line);
            if (section == "#SINHVIEN") {
                // Đọc thông tin sinh viên
                std::string maSV, tenSV, sdt, ngaySinh, gioiTinh, maPhong, maHopDong;
                std::getline(iss, maSV, '|');
                std::getline(iss, tenSV, '|');
                std::getline(iss, sdt, '|');
                std::getline(iss, ngaySinh, '|');
                std::getline(iss, gioiTinh, '|');
                std::getline(iss, maPhong, '|');
                std::getline(iss, maHopDong, '|');

                SinhVien sv(maSV, tenSV, sdt, Date::parse(ngaySinh, '-'), gioiTinh == "Nam", maPhong, maHopDong);
                danhSachSinhVien.add(sv);

            } else if (section == "#PHONG") {
                // Đọc thông tin phòng
            
                std::string maPhong;
                bool loaiPhong; 
                int sucChua, tienPhong;

//                std::string maPhong, loaiPhong, sucChua, tienPhong;
               std::getline(iss, maPhong, '|');
//                bool getline(iss, loaiPhong, '|');
//                int getline(iss, sucChua, '|');
//                int getline(iss, tienPhong, '|');
                
                iss >> loaiPhong; 
                iss.ignore();
                iss >> sucChua;
                iss.ignore(); 
                iss >> tienPhong;

                Phong phong(maPhong, loaiPhong, sucChua, tienPhong);
                danhSachPhong.add(phong);
  
            } else if (section == "#HOPDONG") {
                // Đọc thông tin hợp đồng
                std::string maHD, maSV, maPhong, ngayBatDau, ngayKetThuc;
                std::getline(iss, maHD, '|');
                std::getline(iss, maSV, '|');
                std::getline(iss, maPhong, '|');
                std::getline(iss, ngayBatDau, '|');
                std::getline(iss, ngayKetThuc, '|');

                HopDong hd(maHD, maSV, maPhong, Date::parse(ngayBatDau, '-'), Date::parse(ngayKetThuc, '-'));
                danhSachHopDong.add(hd);
            }
        }

        file.close();
    }


    void saveToFile(const std::string& fileName) {
        std::ofstream file(fileName, std::ios::trunc);
        if (!file.is_open()) {
            throw std::runtime_error("Khong the mo file de ghi: " + fileName);
        }

        // Lưu thông tin người dùng (admin, password) - có thể thêm vào nếu cần
        // file << "admin\n123456\n";

        // Lưu danh sách sinh viên
        file << "#SINHVIEN\n";
        auto nodeSV = danhSachSinhVien.getHead();
        while (nodeSV != nullptr) {
            SinhVien& sv = nodeSV->data; // Giả sử `data` chứa đối tượng SinhVien
            file << sv.getMaSinhVien() << "|"
                 << sv.getTenSinhVien() << "|"
                 << sv.getSoDienThoai() << "|"
                 << sv.getNgaySinh().toString() << "|"
                 << (sv.isGioiTinh() ? "Nam" : "Nu") << "|"
                 << sv.getMaPhong() << "|"
                 << sv.getMaHopDong() << "\n";
            nodeSV = nodeSV->next;
        }


        // Lưu danh sách phòng
        file << "#PHONG\n";
        auto nodeP = danhSachPhong.getHead(); // Giả sử getHead() trả về con trỏ đến node đầu tiên
        while (nodeP != nullptr) {
            Phong& phong = nodeP->data; // Lấy đối tượng phòng từ node
            file << phong.getMaPhong() << "|"
                 << phong.getLoaiPhong() << "|"
                 << phong.getSucChua() << "|"
                 << phong.getTienPhong() << "\n";
            nodeP = nodeP->next; // Chuyển đến node tiếp theo
        }

        // Lưu danh sách hợp đồng
        file << "#HOPDONG\n";
        auto nodeHD = danhSachHopDong.getHead(); // Giả sử getHead() trả về con trỏ đến node đầu tiên
        while (nodeHD != nullptr) {
            HopDong& hopDong = nodeHD->data; // Lấy đối tượng hợp đồng từ node
            file << hopDong.getMaHopDong() << "|"
                 << hopDong.getMaSinhVien() << "|"
                 << hopDong.getMaPhong() << "|"
                 << hopDong.getNgayBatDau().toString() << "|"
                 << hopDong.getNgayKetThuc().toString() << "\n";
            nodeHD = nodeHD->next; // Chuyển đến node tiếp theo
        }

        file.close();
    }


};

