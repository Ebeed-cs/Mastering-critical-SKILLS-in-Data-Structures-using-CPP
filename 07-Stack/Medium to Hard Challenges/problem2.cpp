#include <iostream>
#include <cassert>
#include <cmath>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

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
    ~Stack() {
        delete[] array;
    }

    string debug_to_string() {
        if (top == -1)
            return "";
        ostringstream oss;
        for (int i = top; i >= 0; --i) {
            oss << array[i];
            if (i > 0)
                oss << " ";
        }
        return oss.str();
    }

    void problem2(int x) { // o(n) time 
        if (is_empty()) {
            push(x);
            return;
        }
        push(array[top]);
        top -= 2;
        if (top == -1) {
            push(x);
            ++top;
            return;
        }
        problem2(x);
        ++top;
    }
};

string vector_to_string(const vector<int>& vec) {
    if (vec.empty())
        return "";
    ostringstream oss;
    for (size_t i = 0; i < vec.size(); ++i) {
        oss << vec[i];
        if (i < vec.size() - 1)
            oss << " ";
    }
    return oss.str();
}

void test1() {
    cout << "\n\ntest1\n";
    Stack<int> stack(5);
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);

    stack.problem2(10);

    string expected = "4 3 2 1 10";
    string result = stack.debug_to_string();

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test2() {
    cout << "\n\ntest2\n";
    Stack<int> stack(1);

    stack.problem2(5);

    string expected = "5";
    string result = stack.debug_to_string();

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test3() {
    cout << "\n\ntest3\n";
    Stack<int> stack(2);
    stack.push(1);

    stack.problem2(10);

    string expected = "1 10";
    string result = stack.debug_to_string();

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test4() {
    cout << "\n\ntest4\n";
    Stack<int> stack(4);
    stack.push(1);
    stack.push(2);
    stack.push(3);

    stack.problem2(-5);

    string expected = "3 2 1 -5";
    string result = stack.debug_to_string();

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test5() {
    cout << "\n\ntest5\n";
    Stack<int> stack(6);
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    stack.push(5);

    stack.problem2(0);

    string expected = "5 4 3 2 1 0";
    string result = stack.debug_to_string();

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test6() {
    cout << "\n\ntest6\n";
    Stack<int> stack(3);
    stack.push(1);
    stack.push(2);

    stack.problem2(100);

    string expected = "2 1 100";
    string result = stack.debug_to_string();

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test7() {
    cout << "\n\ntest7\n";
    Stack<int> stack(11);
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    stack.push(5);
    stack.push(6);
    stack.push(7);
    stack.push(8);
    stack.push(9);
    stack.push(10);

    stack.problem2(99);

    string expected = "10 9 8 7 6 5 4 3 2 1 99";
    string result = stack.debug_to_string();

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

int main() {
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();

    // must see it, otherwise RTE
    cout << "\n\nNO RTE\n";

    return 0;
}
