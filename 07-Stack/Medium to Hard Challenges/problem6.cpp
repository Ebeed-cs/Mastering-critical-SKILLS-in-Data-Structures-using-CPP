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
};

void problem6(int v[], int len) {
    Stack<int> stk(len);
    for (int i = 0;i < len; ++i) {
        while (!stk.is_empty() && v[i] > v[stk.peek()])
            v[stk.pop()] = v[i];
        stk.push(i);
    }
    while (!stk.is_empty())
        v[stk.pop()] = -1;

    for (int i = 0; i < len; ++i)
        std::cout << v[i] << " ";
}

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

string array_to_string(int arr[], int len) {
    if (len == 0)
        return "";
    ostringstream oss;
    for (int i = 0; i < len; ++i) {
        oss << arr[i];
        if (i < len - 1)
            oss << " ";
    }
    return oss.str();
}

void test1() {
    cout << "\n\ntest1\n";
    int v[] = { 5, 10, 5, 7, 15, 11 };
    int len = 6;
    problem6(v, len);
    cout << "\n";
    string expected = "10 15 7 15 -1 -1";
    string result = array_to_string(v, len);
    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test2() {
    cout << "\n\ntest2\n";
    int v[] = { 73, 74, 75, 71, 69, 72, 76, 73 };
    int len = 8;
    problem6(v, len);
    cout << "\n";
    string expected = "74 75 76 72 72 76 -1 -1";
    string result = array_to_string(v, len);
    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test3() {
    cout << "\n\ntest3\n";
    int v[] = { 1, 2, 3, 4, 5 };
    int len = 5;
    problem6(v, len);
    cout << "\n";
    string expected = "2 3 4 5 -1";
    string result = array_to_string(v, len);
    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test4() {
    cout << "\n\ntest4\n";
    int v[] = { 5, 4, 3, 2, 1 };
    int len = 5;
    problem6(v, len);
    cout << "\n";
    string expected = "-1 -1 -1 -1 -1";
    string result = array_to_string(v, len);
    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test5() {
    cout << "\n\ntest5\n";
    int v[] = { 3, 3, 3, 3, 3 };
    int len = 5;
    problem6(v, len);
    cout << "\n";
    string expected = "-1 -1 -1 -1 -1";
    string result = array_to_string(v, len);
    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test6() {
    cout << "\n\ntest6\n";
    int v[] = { 1 };
    int len = 1;
    problem6(v, len);
    cout << "\n";
    string expected = "-1";
    string result = array_to_string(v, len);
    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test7() {
    cout << "\n\ntest7\n";
    int v[] = { 5, 3, 8, 2, 7 };
    int len = 5;
    problem6(v, len);
    cout << "\n";
    string expected = "8 8 -1 7 -1";
    string result = array_to_string(v, len);
    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test8() {
    cout << "\n\ntest8\n";
    int v[] = { 10, 5, 11, 7, 6, 8 };
    int len = 6;
    problem6(v, len);
    cout << "\n";
    string expected = "11 11 -1 8 8 -1";
    string result = array_to_string(v, len);
    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test9() {
    cout << "\n\ntest9\n";
    int v[] = { 2, 1, 2, 4, 3 };
    int len = 5;
    problem6(v, len);
    cout << "\n";
    string expected = "4 2 4 -1 -1";
    string result = array_to_string(v, len);
    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test10() {
    cout << "\n\ntest10\n";
    int v[] = { 100, 1, 2, 3, 99 };
    int len = 5;
    problem6(v, len);
    cout << "\n";
    string expected = "-1 2 3 99 -1";
    string result = array_to_string(v, len);
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
    test8();
    test9();
    test10();
    cout << "\n\nNO RTE\n";
    return 0;
}
