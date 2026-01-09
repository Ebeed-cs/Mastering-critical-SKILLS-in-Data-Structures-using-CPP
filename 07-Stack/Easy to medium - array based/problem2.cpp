#include <iostream>
#include <cassert>

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

    std::string problem2(std::string line) {
        std::string output = "";
        for (char input : line) {
            if (input == ' ') {
                while (!is_empty())
                    output += pop();
                output += " ";
            }
            else
                push(input);
        }
        while (!is_empty())
            output += pop();
        return output;
    }
};

int main() {

    Stack<char> stk(20);
    std::string line;
    std::getline(std::cin, line);
    std::cout << stk.problem2(line) << "\n";
    return 0;
}
