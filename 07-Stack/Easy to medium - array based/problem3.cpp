#include <iostream>
#include <cassert>
#include <cmath>

template<class T>
class Stack {
private:
    T* array{};
    int top{};
    int length{};
public:
    Stack(int size) : length(size), top(-1) {
        array = new T[length];
    }
    void push(T val) {
        assert(!is_full());
        array[++top] = val;
    }
    T pop() {
        assert(!is_empty());
        return array[top--];
    }
    T peek() {
        assert(!is_empty());
        return array[top];
    }
    inline bool is_full() { return top == length - 1; }
    inline bool is_empty() { return top == -1; }
    void print() {
        for (int i = top; i >= 0; --i)
            std::cout << array[i] << " ";
    }

};
int countDigits(int n) {
    if (n < 0) n = -n;
    if (n == 0) return 1;
    return std::floor(std::log10(n)) + 1;
}

int problem3(int num) {
    int result = 0;
    Stack<int> stk(countDigits(num));
    while (num) {
        stk.push(num % 10);
        num /= 10;
    }
    int mul = 1;
    while (!stk.is_empty()) {
        result += stk.pop() * mul;
        mul *= 10;
    }
    return result;
}

int main() {
    int num;
    std::cin >> num;
    std::cout << problem3(num) << "\n";
    return 0;
}
