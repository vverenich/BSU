#include <iostream>

class IntUniquePtr {
public:
    IntUniquePtr() {
        ptr_ = new int;
    }

    explicit IntUniquePtr(int* ptr) : ptr_(ptr) {}

    IntUniquePtr(const IntUniquePtr&) = delete;
    IntUniquePtr& operator=(const IntUniquePtr&) = delete;

    IntUniquePtr(IntUniquePtr&& unique_ptr) {
        ptr_ = unique_ptr.ptr_;
        unique_ptr.ptr_ = nullptr;
    }
    IntUniquePtr& operator=(IntUniquePtr&& unique_ptr) {
        if (this == &unique_ptr) {
            return *this;
        }
        delete ptr_;
        ptr_ = unique_ptr.ptr_;
        unique_ptr.ptr_ = nullptr;
        return *this;
    }

    virtual ~IntUniquePtr() {
        delete ptr_;
    }

    const int& Value() const {
        return *ptr_;
    }

    int& Value() {
        return *ptr_;
    }
private:
    int* ptr_;
};

IntUniquePtr MakeUnique(int x) {
    int* temp_ptr = new int;
    *temp_ptr = x;
    return IntUniquePtr(temp_ptr);
}

int main() {
    IntUniquePtr unique_ptr = MakeUnique(5);
    std::cout << unique_ptr.Value() << "\n";

    IntUniquePtr unique_ptr2(std::move(unique_ptr));
    std::cout << unique_ptr2.Value() << "\n";

    IntUniquePtr unique_ptr3;
    unique_ptr3 = std::move(unique_ptr2);
    std::cout << unique_ptr3.Value() << "\n";
    int p;
    if (!p) {
        std::cout << "zhopa";
    }
    else {
        std::cout << "zaebok";
    }


     
return 0;
}