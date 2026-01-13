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

std::string problem5(std::string s) {
    Stack<char> stk(s.length());
    for (char c : s) {
        if (stk.is_empty() == 0 && stk.peek() == c)
            stk.pop();
        else
            stk.push(c);
    }
    std::string res = "";
    while (stk.is_empty() == 0) // zero means false "not empty" - don't confused
        res = stk.pop() + res;

    return res;
}
int main() {
    std::string res;
    std::cin >> res;
    std::cout << problem5(res) << "\n";
    return 0;
}
