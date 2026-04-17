# University Human Resources Management System (C++ OOP)

Dự án cuối kỳ môn Lập trình hướng đối tượng (OOP) - Chuẩn chuyên nghiệp.

## 🌟 Tính năng nổi bật
- **Mô hình MVC**: Tách biệt hoàn toàn Logic (Model), Giao diện (View) và Điều khiển (Controller).
- **Tính Đa hình (Polymorphism)**: Sử dụng Virtual Functions và Abstract Class để quản lý danh sách hỗn hợp (Student, Lecturer).
- **Quản lý bộ nhớ hiện đại**: Sử dụng `std::unique_ptr` và `std::shared_ptr` thay cho con trỏ thô (raw pointers), đảm bảo không Memory Leak.
- **SOLID Principles**: Áp dụng Single Responsibility Principle (SRP) - mỗi class chỉ làm một nhiệm vụ duy nhất.
- **STL & Algorithms**: Sử dụng `std::vector`, `std::sort`, `std::remove_if` và Lambda functions.

## 🛠 Cấu trúc Project
- `include/`: Chứa các file định nghĩa (.h)
- `src/`: Chứa các file thực thi (.cpp)
- `main.cpp`: Entry point của ứng dụng.

## 🚀 Cách chạy dự án trên VS Code
1. Cài đặt extension **C/C++** của Microsoft.
2. Mở thư mục dự án.
3. Nhấn `Ctrl+Shift+B` để build.
4. Chạy file `UniversityManagement` được tạo ra.

## 📝 Tác giả
- Sinh viên: [Tên của bạn]
- Lớp: [Lớp của bạn]
