/*
    Right rotation
● Consider our Vector class. Add the member function: void right_rotate()
● The function shifts every element 1 step towards the right.
○ What about the rightmost element? It goes to the first idx
● Example
● Assume the array content is: 0 1 2 3 4
● After a right rotation it will be: 4 0 1 2 3
○ Notice how, in this case, the '4' has been rotated to the head of the array!
● Ensure you avoid expanding the array's capacity
*/

#include <iostream>
#include <cassert>

class Vector
{
private:
    int *ptr = nullptr;
    int captcity{};
    int size{};

public:
    Vector() = default;
    Vector(int s) : captcity(s * 2)
    {
        ptr = new int[captcity];
    }

    void print()
    {
        if (size == 0)
        {
            std::cout << "it's empty" << "\n";
            return;
        }
        else
            for (int i = 0; i < size; ++i)
                std::cout << ptr[i] << " ";
    }

    void resize()
    {
        captcity *= 2;
        int *ptr2 = new int[captcity]{};
        for (int i = 0; i < size; ++i)
            ptr2[i] = ptr[i];
        Clear();
        std::swap(ptr, ptr2);
    }

    void push_back(int val)
    {
        if (size == captcity)
            resize();
        ptr[size++] = val;
    }

    int &operator[](int ind)
    {
        assert(ind >= 0 && ind < size);
        return ptr[ind];
    }

    void insert(int val, int ind)
    {
        assert(ind >= 0 && ind < size);
        for (int i = size; i > ind; --i)
            ptr[i] = ptr[i - 1];
        ptr[ind] = val;
        size++;
    }

    void rightRotation()
    {
        insert(ptr[size - 1], 0);
        size--;
    }

    void Clear()
    {
        if (ptr != nullptr)
            delete[] ptr;
        ptr = nullptr;
    }

    ~Vector()
    {
        Clear();
    }
};

int main()
{
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
