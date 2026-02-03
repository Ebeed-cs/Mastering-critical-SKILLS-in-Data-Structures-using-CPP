#include <iostream>
#include <cassert>
#include <sstream>
#include <cmath>
using namespace std;

template<typename T>
class Stack {
private:
    struct Node {
        T data{ };
        Node* next{ };
        Node(T data) :
            data(data) {
        }
    };
    Node* head{ };
public:
    ~Stack() {
        while (!isEmpty())
            pop();
    }
    void display() {
        for (Node* cur = head; cur; cur = cur->next)
            cout << cur->data << " ";
        cout << "\n";
    }
    void push(T value) {
        Node* item = new Node(value);
        item->next = head;
        head = item;
    }
    T pop() {
        assert(!isEmpty());
        T element = head->data;
        Node* temp = head;
        head = head->next;
        delete temp;
        return element;
    }
    T peek() {
        assert(!isEmpty());
        T element = head->data;
        return element;
    }
    int isEmpty() {
        return !head;
    }
};

double do_operation(double ope1, double ope2, char op) {
    if (op == '^')
        return pow(ope1, ope2);
    if (op == '*')
        return ope1 * ope2;
    if (op == '/')
        return ope1 / ope2;
    if (op == '+')
        return ope1 + ope2;
    if (op == '-')
        return ope1 - ope2;
    return 0;
}

double problem2(string postfix) {
    Stack<double> stk;
    std::string operators = "^*/-+";
    for (char c : postfix) {
        if (operators.find(c) == string::npos)
            stk.push(c - '0');
        else {
            double operator2 = stk.pop();
            double operator1 = stk.pop();
            stk.push(do_operation(operator1, operator2, c));
        }
    }
    return stk.pop();
}

void test1() {
    cout << "\n\ntest1\n";
    double result = problem2("52/");
    double expected = 2.5;

    if (abs(expected - result) > 0.0001) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test2() {
    cout << "\n\ntest2\n";
    double result = problem2("12+3+");
    double expected = 6;

    if (abs(expected - result) > 0.0001) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test3() {
    cout << "\n\ntest3\n";
    double result = problem2("123*+");
    double expected = 7;

    if (abs(expected - result) > 0.0001) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test4() {
    cout << "\n\ntest4\n";
    double result = problem2("23*4+");
    double expected = 10;

    if (abs(expected - result) > 0.0001) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test5() {
    cout << "\n\ntest5\n";
    // Hint: Stack stores int, loses precision on division
    double result = problem2("135*+72/-");
    double expected = 12.5;

    if (abs(expected - result) > 0.0001) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test6() {
    cout << "\n\ntest6\n";
    // Hint: Stack stores int, overflow or truncation on large pow results
    double result = problem2("432^^");
    double expected = 262144;

    if (abs(expected - result) > 0.0001) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test7() {
    cout << "\n\ntest7\n";
    double result = problem2("3");
    double expected = 3;

    if (abs(expected - result) > 0.0001) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test8() {
    cout << "\n\ntest8\n";
    double result = problem2("34+");
    double expected = 7;

    if (abs(expected - result) > 0.0001) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test9() {
    cout << "\n\ntest9\n";
    double result = problem2("50-");
    double expected = 5;

    if (abs(expected - result) > 0.0001) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test10() {
    cout << "\n\ntest10\n";
    double result = problem2("21-");
    double expected = 1;

    if (abs(expected - result) > 0.0001) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test11() {
    cout << "\n\ntest11\n";
    double result = problem2("42/");
    double expected = 2;

    if (abs(expected - result) > 0.0001) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test12() {
    cout << "\n\ntest12\n";
    double result = problem2("23^");
    double expected = 8;

    if (abs(expected - result) > 0.0001) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test13() {
    cout << "\n\ntest13\n";
    double result = problem2("99*");
    double expected = 81;

    if (abs(expected - result) > 0.0001) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test14() {
    cout << "\n\ntest14\n";
    double result = problem2("12+34+*");
    double expected = 21;

    if (abs(expected - result) > 0.0001) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test15() {
    cout << "\n\ntest15\n";
    double result = problem2("12-34-*");
    double expected = 1;

    if (abs(expected - result) > 0.0001) {
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
    test11();
    test12();
    test13();
    test14();
    test15();

    cout << "\n\nNO RTE\n";
    return 0;
}
