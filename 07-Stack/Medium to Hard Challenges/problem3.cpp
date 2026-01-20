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
    void insert_at_bottom(int x) { // o(n) time , o(n) space 
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
        insert_at_bottom(x);
        ++top;
    }
    void problem3() {
        if (is_empty())
            return;
        else {
            int prev = pop();
            problem3();
            insert_at_bottom(prev);
        }
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
    Stack<int> stk(10);
    stk.push(1);
    stk.push(2);
    stk.push(3);
    stk.push(4);
    stk.problem3();
    string expected = "1 2 3 4";
    string result = stk.debug_to_string();
    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test2() {
    cout << "\n\ntest2\n";
    Stack<int> stk(10);
    stk.push(5);
    stk.problem3();
    string expected = "5";
    string result = stk.debug_to_string();
    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test3() {
    cout << "\n\ntest3\n";
    Stack<int> stk(10);
    stk.problem3();
    string expected = "";
    string result = stk.debug_to_string();
    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test4() {
    cout << "\n\ntest4\n";
    Stack<int> stk(10);
    stk.push(1);
    stk.push(2);
    stk.problem3();
    string expected = "1 2";
    string result = stk.debug_to_string();
    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test5() {
    cout << "\n\ntest5\n";
    Stack<int> stk(10);
    stk.push(10);
    stk.push(20);
    stk.push(30);
    stk.push(40);
    stk.push(50);
    stk.push(60);
    stk.problem3();
    string expected = "10 20 30 40 50 60";
    string result = stk.debug_to_string();
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

    // must see it, otherwise RTE
    cout << "\n\nNO RTE\n";
    return 0;
}
