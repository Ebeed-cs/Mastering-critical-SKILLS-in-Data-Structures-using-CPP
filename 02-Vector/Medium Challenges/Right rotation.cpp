#include <iostream>
#include <cassert>

class Vector {
private:
    int* ptr = nullptr;
    int captcity{};
    int size{};
public:
    Vector() = default;
    Vector(int s) : captcity(s * 2) {
        ptr = new int[captcity];
    }

    void print() {
        if (size == 0) {
            std::cout << "it's empty" << "\n";
            return;
        }
        else
            for (int i = 0; i < size; ++i)
                std::cout << ptr[i] << " ";
    }

    void resize() {
        captcity *= 2;
        int* ptr2 = new int[captcity] {};
        for (int i = 0; i < size; ++i) ptr2[i] = ptr[i];
        Clear();
        std::swap(ptr, ptr2);
    }


    void push_back(int val) {
        if (size == captcity) resize();
        ptr[size++] = val;
    }

    int& operator[](int ind) {
        assert(ind >= 0 && ind < size);
        return ptr[ind];
    }

    void insert(int val, int ind) {
        assert(ind >= 0 && ind < size);
        for (int i = size; i > ind; --i)
            ptr[i] = ptr[i - 1];
        ptr[ind] = val;
        size++;
    }

    void rightRotation() {
        insert(ptr[size - 1], 0);
        size--;
    }

    void Clear() {
        if (ptr != nullptr)
            delete[] ptr;
        ptr = nullptr;
    }

    ~Vector() {
        Clear();
    }
};

int main() {
    Vector v(10);
    v.push_back(0);
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.print();

    std::cout << "\nAfter roration right \n";
    v.rightRotation();

    v.print();

    return 0;
}
