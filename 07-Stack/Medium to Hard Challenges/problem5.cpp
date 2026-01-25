#include <iostream>
#include <cassert>
#include <cmath>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;
//          [Explanation video]
template <class T>
class Stack
{
private:
    T *array{};
    int top{};
    int length{};

public:
    Stack(int size) : length(size), top(-1)
    {
        array = new T[length];
    }
    void push(T val)
    {
        assert(!is_full());
        array[++top] = val;
    }
    T pop()
    {
        assert(!is_empty());
        return array[top--];
    }
    T peek()
    {
        assert(!is_empty());
        return array[top];
    }
    inline bool is_full() { return top == length - 1; }
    inline bool is_empty() { return top == -1; }
    void print()
    {
        for (int i = top; i >= 0; --i)
            std::cout << array[i] << " ";
    }
    ~Stack()
    {
        delete[] array;
    }
    string debug_to_string()
    {
        if (top == -1)
            return "";
        ostringstream oss;
        for (int i = top; i >= 0; --i)
        {
            oss << array[i];
            if (i > 0)
                oss << " ";
        }
        return oss.str();
    }
};

int problem5(string str)
{
    Stack<int> stk(str.length());
    stk.push(0);
    for (char c : str)
    {
        if (c == '(')
            stk.push(0);
        else
        {
            int last = stk.pop();
            if (last == 0)
                last = 1;
            else
                last *= 2;
            int parent = last + stk.pop();
            stk.push(parent);
        }
    }
    return stk.pop();
}

string vector_to_string(const vector<int> &vec)
{
    if (vec.empty())
        return "";
    ostringstream oss;
    for (size_t i = 0; i < vec.size(); ++i)
    {
        oss << vec[i];
        if (i < vec.size() - 1)
            oss << " ";
    }
    return oss.str();
}

void test1()
{
    cout << "\n\ntest1\n";
    int result = problem5("()");
    int expected = 1;
    if (expected != result)
    {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test2()
{
    cout << "\n\ntest2\n";
    int result = problem5("(())");
    int expected = 2;
    if (expected != result)
    {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test3()
{
    cout << "\n\ntest3\n";
    int result = problem5("()()");
    int expected = 2;
    if (expected != result)
    {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test4()
{
    cout << "\n\ntest4\n";
    int result = problem5("((()))");
    int expected = 4;
    if (expected != result)
    {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test5()
{
    cout << "\n\ntest5\n";
    int result = problem5("(()())");
    int expected = 4;
    if (expected != result)
    {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test6()
{
    cout << "\n\ntest6\n";
    int result = problem5("()(())");
    int expected = 3;
    if (expected != result)
    {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test7()
{
    cout << "\n\ntest7\n";
    int result = problem5("(()(()))");
    int expected = 6;
    if (expected != result)
    {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test8()
{
    cout << "\n\ntest8\n";
    int result = problem5("(())(())");
    int expected = 4;
    if (expected != result)
    {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test9()
{
    cout << "\n\ntest9\n";
    int result = problem5("((()()))");
    int expected = 8;
    if (expected != result)
    {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test10()
{
    cout << "\n\ntest10\n";
    int result = problem5("((((()))))");
    int expected = 16;
    if (expected != result)
    {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test11()
{
    cout << "\n\ntest11\n";
    int result = problem5("()()()()()");
    int expected = 5;
    if (expected != result)
    {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test12()
{
    cout << "\n\ntest12\n";
    int result = problem5("(()(()()))");
    int expected = 10;
    if (expected != result)
    {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

int main()
{
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
    test11();
    test12();

    cout << "\n\nNO RTE\n";
    return 0;
}
