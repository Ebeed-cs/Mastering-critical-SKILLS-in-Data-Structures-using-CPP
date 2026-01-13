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

bool problem4(std::string str) {
    Stack<char> stk(str.length());
    for (char c : str) {
        if (c == '(' || c == '{' || c == '[')
            stk.push(c);
        else {
            if (!stk.is_empty() && stk.peek() == '(' && c == ')')
                stk.pop();
            else if (!stk.is_empty() && stk.peek() == '{' && c == '}')
                stk.pop();
            else if (!stk.is_empty() && stk.peek() == '[' && c == ']')
                stk.pop();
            else
                return false;
        }
    }
    return stk.is_empty();
}

int main() {
    std::string str;
    std::cin >> str;

    if (problem4(str))
        std::cout << "valid" << "\n";
    else
        std::cout << "not valid" << "\n";
    return 0;
}
