#include <iostream>
#include <string>
#include "QuanLyKiTucXa.h"
#include "SinhVien.h"
#include "Phong.h"
#include "HopDong.h"
#include "Date.h"
#include "LinkedList.h"

using namespace std;
int main() {
    QuanLyKiTucXa qlktx;
    string fileName = "data.txt";
    qlktx.loadFromFile(fileName);

    if (!qlktx.dangNhap()) {
        std::cout << "Dang nhap that bai. Thoat chuong trinh.\n";
        return 0;
    }

    int choice;
    do {
        std::cout << "\n===== Quan Ly Ki Tuc Xa =====\n";
        std::cout << "1. Them hop dong\n";
        std::cout << "2. Xem danh sach sinh vien\n";
        std::cout << "3. Xem danh sach phong\n";
        std::cout << "4. Them sinh vien\n";
        std::cout << "5. Them phong\n";
        std::cout << "6. Xem danh sach cho xep phong\n";
        std::cout << "7. Xem danh sach hop dong\n";
        std::cout << "8admin. Thoat\n";
        std::cout << "Lua chon: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                qlktx.themHopDong();
                break;
            case 2:
                qlktx.xemDanhSachSinhVien();
                break;
            case 3:
                qlktx.xemDanhSachPhong();
                break;
            case 4:
                qlktx.themSinhVien();
                break;
            case 5:
                qlktx.themPhong();
                break;
            case 6:
                qlktx.xemDanhSachCho();
                break;
            case 7:
                qlktx.xemDanhSachHopDong();
                break;
            case 8:
                qlktx.saveToFile(fileName);
                std::cout << "Da luu du lieu va thoat.\n";
                break;
            default:
                std::cout << "Lua chon khong hop le.\n";
        }
    } while (choice != 8);

    return 0;
}
