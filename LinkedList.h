#include <functional>
#pragma once


template <typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };
    Node* head;
    Node* tail;
    int size;

public:
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}
    ~LinkedList() { clear(); }

    // Phương thức them (thêm phần tử vào cuối danh sách)

    void add(const T& value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    void remove(const T& value) {
        Node* current = head;
        Node* previous = nullptr;
        while (current) {
            if (current->data == value) {
                if (current == head) {
                    head = head->next;
                } else {
                    previous->next = current->next;
                }
                if (current == tail) {
                    tail = previous;
                }
                delete current;
                size--;
                return;
            }
            previous = current;
            current = current->next;
        }
    }


 
    // Tìm kiếm phần tử theo predicate (trả về con trỏ nếu tìm thấy)
    T* findIf(const std::function<bool(const T&)>& predicate) {
        Node* current = head;
        while (current) {
            if (predicate(current->data)) {
                return &(current->data);
            }
            current = current->next;
        }
        return nullptr;
    }

    // Duyệt qua danh sách và thực thi hành động
    void forEach(const std::function<void(const T&)>& action) const {
        Node* current = head;
        while (current) {
            action(current->data);
            current = current->next;
        }
    }

    // Kiểm tra xem danh sách có chứa giá trị cho trước hay không
    bool contains(const T& value) const {
        Node* current = head;
        while (current) {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void clear() {
        Node* current = head;
        while (current) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        head = tail = nullptr;
        size = 0;
    }

    int getSize() const { return size; }

    // Phương thức isEmpty() để kiểm tra danh sách có rỗng không
    bool isEmpty() const {
        return head == nullptr;
    }

    void display() const {
        Node* current = head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    Node* getHead() const {
        return head;
    }

    // Thêm phương thức begin() và end() cho phép dùng vòng lặp range-based
    Node* begin() {
        return head; // Trả về con trỏ đến phần tử đầu tiên
    }

    Node* end() {
        return nullptr; // Trả về nullptr cho phần tử sau cuối cùng
    }

    // Phương thức const begin() và end() cho phép duyệt danh sách trong vòng lặp const range-based
    const Node* begin() const {
        return head;
    }

    const Node* end() const {
        return nullptr;
    }
};

