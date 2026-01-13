#include <iostream>
#include <cassert>
#include <cmath>

template<class T>
class Stack {
private:
    T* array{};
    int top_left{};
    int top_right{};
    int length{};
public:
    Stack(int size) : length(size), top_left(-1), top_right(size) {
        array = new T[length];
    }
    void push(int id, T val) {
        assert(!is_full());
        if (id == 1)
            array[++top_left] = val;
        else
            array[--top_right] = val;
    }
    T pop(int id) {
        assert(!is_empty(id));
        if (id == 1)
            return array[top_left--];
        return array[top_right++];
    }
    T peek(int id) {
        assert(!is_empty(id));
        if (id == 1) return array[top_left];
        return array[top_right];
    }
    inline bool is_full() { return (top_left + 1) == top_right; }
    inline bool is_empty(int id) { if (id == 1) return top_left == -1; return top_right == length; }
    void print() {
        for (int i = top_left; i >= 0; --i)
            std::cout << array[i] << " ";
        std::cout << "\n";
        for (int i = top_right; i < length; ++i)
            std::cout << array[i] << " ";
    }
};

int main() {
    Stack<int> stk(10);
    stk.push(2, 5);
    stk.push(2, 6);
    stk.pop(2);
    stk.push(2, 7);
    stk.push(2, 9);

    stk.push(1, 4);
    std::cout << stk.peek(1) << "\n"; // 4
    std::cout << stk.peek(2) << "\n"; // 9
    stk.push(1, 6);
    stk.push(1, 8);
    stk.push(2, 3);
    stk.print();
    return 0;
}
