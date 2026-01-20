#include <iostream>
#include <cassert>
#include <cmath>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

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
};

vector<int> problem1(vector<int> &asteroids)
{
    Stack<int> stk(asteroids.size());
    for (int v : asteroids)
    {
        if (stk.is_empty() != 1 && stk.peek() > 0 && v < 0)
        {
            bool put = true;
            while (stk.is_empty() != 1 && stk.peek() > 0 && v < 0)
            {
                if (stk.peek() >= abs(v))
                {
                    put = false;
                    if (stk.peek() == abs(v))
                        stk.pop();
                    break;
                }
                else
                    stk.pop();
            }
            if (put)
                stk.push(v);
        }
        else
            stk.push(v);
    }
    asteroids.clear();
    while (stk.is_empty() != 1)
        asteroids.push_back(stk.pop());
    reverse(asteroids.begin(), asteroids.end()); // faster than if i push in front -> o(n) time "in each time i will shift the elements right"
    return asteroids;
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
    vector<int> asteroids = {5, 10, -5};
    vector<int> result = problem1(asteroids);

    string expected = "5 10";
    string result_str = vector_to_string(result);

    if (expected != result_str)
    {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result_str << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test2()
{
    cout << "\n\ntest2\n";
    vector<int> asteroids = {8, -8};
    vector<int> result = problem1(asteroids);

    string expected = "";
    string result_str = vector_to_string(result);

    if (expected != result_str)
    {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result_str << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test3()
{
    cout << "\n\ntest3\n";
    vector<int> asteroids = {10, 2, -5};
    vector<int> result = problem1(asteroids);

    string expected = "10";
    string result_str = vector_to_string(result);

    if (expected != result_str)
    {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result_str << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test4()
{
    cout << "\n\ntest4\n";
    vector<int> asteroids = {-2, -1, 1, 2};
    vector<int> result = problem1(asteroids);

    string expected = "-2 -1 1 2";
    string result_str = vector_to_string(result);

    if (expected != result_str)
    {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result_str << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test5()
{
    cout << "\n\ntest5\n";
    vector<int> asteroids = {};
    vector<int> result = problem1(asteroids);

    string expected = "";
    string result_str = vector_to_string(result);

    if (expected != result_str)
    {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result_str << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test6()
{
    cout << "\n\ntest6\n";
    vector<int> asteroids = {5};
    vector<int> result = problem1(asteroids);

    string expected = "5";
    string result_str = vector_to_string(result);

    if (expected != result_str)
    {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result_str << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test7()
{
    cout << "\n\ntest7\n";
    vector<int> asteroids = {-5, -10};
    vector<int> result = problem1(asteroids);

    string expected = "-5 -10";
    string result_str = vector_to_string(result);

    if (expected != result_str)
    {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result_str << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test8()
{
    cout << "\n\ntest8\n";
    vector<int> asteroids = {5, 10};
    vector<int> result = problem1(asteroids);

    string expected = "5 10";
    string result_str = vector_to_string(result);

    if (expected != result_str)
    {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result_str << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test9()
{
    cout << "\n\ntest9\n";
    vector<int> asteroids = {-5, 5};
    vector<int> result = problem1(asteroids);

    string expected = "-5 5";
    string result_str = vector_to_string(result);

    if (expected != result_str)
    {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result_str << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test10()
{
    cout << "\n\ntest10\n";
    vector<int> asteroids = {5, -5};
    vector<int> result = problem1(asteroids);

    string expected = "";
    string result_str = vector_to_string(result);

    if (expected != result_str)
    {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result_str << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test11()
{
    cout << "\n\ntest11\n";
    vector<int> asteroids = {1, -2};
    vector<int> result = problem1(asteroids);

    string expected = "-2";
    string result_str = vector_to_string(result);

    if (expected != result_str)
    {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result_str << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test12()
{
    cout << "\n\ntest12\n";
    vector<int> asteroids = {10, -5, -10};
    vector<int> result = problem1(asteroids);

    string expected = "";
    string result_str = vector_to_string(result);

    if (expected != result_str)
    {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result_str << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test13()
{
    cout << "\n\ntest13\n";
    vector<int> asteroids = {1, 2, 3, -10};
    vector<int> result = problem1(asteroids);

    string expected = "-10";
    string result_str = vector_to_string(result);

    if (expected != result_str)
    {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result_str << "\n";
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
    test13();

    // must see it, otherwise RTE
    cout << "\n\nNO RTE\n";

    return 0;
}
