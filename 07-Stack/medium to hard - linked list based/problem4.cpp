#include<iostream>
#include<cassert>
using namespace std;

typedef char type;

class Stack {
private:
    int size{ };
    int top{ };
    type* array{ };
public:
    Stack(int size) :
        size(size), top(-1) {
        array = new type[size];
    }

    ~Stack() {
        delete[] array;
    }

    void push(type x) {
        assert(!isFull());
        array[++top] = x;
    }

    type pop() {
        assert(!isEmpty());
        return array[top--];
    }

    type peek() {
        assert(!isEmpty());
        return array[top];
    }

    int isFull() {
        return top == size - 1;
    }

    int isEmpty() {
        return top == -1;
    }
};

char sign(char a, char b) {
    if (a == b)
        return '+';
    return '-';
}

string problem4(string str) {
    Stack stk(str.size());
    stk.push('+');
    std::string res = "";
    for (int i = 0; i < str.size(); ++i) {
        char c = str[i];
        if (isdigit(c)) res += c;
        else if (c == '(' && i) {
            if (str[i - 1] != '(')
                stk.push(sign(stk.peek(), str[i - 1]));
            else // (())
                stk.push(stk.peek());
        }
        else if (c == '+' || c == '-')
            res += sign(stk.peek(), c);
        else
            stk.pop();
    }
    return res;
}

void test1() {
    cout << "\n\ntest1\n";
    string input = "1+2-3-4+5-6-7+8";
    string expected = "1+2-3-4+5-6-7+8";
    string result = problem4(input);

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test2() {
    cout << "\n\ntest2\n";
    string input = "9-(2+3)";
    string expected = "9-2-3";
    string result = problem4(input);

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test3() {
    cout << "\n\ntest3\n";
    string input = "9-(2-3)";
    string expected = "9-2+3";
    string result = problem4(input);

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test4() {
    cout << "\n\ntest4\n";
    string input = "9+(2-3)";
    string expected = "9+2-3";
    string result = problem4(input);

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test5() {
    cout << "\n\ntest5\n";
    string input = "1-(2-3-(4+5))-6-(7-8)";
    string expected = "1-2+3+4+5-6-7+8";
    string result = problem4(input);

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test6() {
    cout << "\n\ntest6\n";
    string input = "1-(2-3-(4+5)+6-7)";
    string expected = "1-2+3+4+5-6+7";
    string result = problem4(input);

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test7() {
    cout << "\n\ntest7\n";
    string input = "1-(2-3-(4+5-(6-7)))";
    string expected = "1-2+3+4+5-6+7";
    string result = problem4(input);

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test8() {
    cout << "\n\ntest8\n";
    // Hint: Extra closing bracket - may access str[i-1] when i=0 for '(' check
    string input = "1-((4+5)-(6-7)))";
    string expected = "1-4-5+6-7";
    string result = problem4(input);

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test9() {
    cout << "\n\ntest9\n";
    // Hint: Multiple consecutive opening brackets with extra closing brackets
    string input = "1-(((4-5)-(6-7))))";
    string expected = "1-4+5+6-7";
    string result = problem4(input);

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
    cout << "\n\nNO RTE\n";
    return 0;
}
