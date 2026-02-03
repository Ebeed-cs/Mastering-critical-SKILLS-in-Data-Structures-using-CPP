#include <iostream>
#include <cassert>
#include <sstream>
using namespace std;

typedef char type;

class Stack {
private:
    struct Node {
        type data{ };
        Node* next{ };
        Node(int data) :
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

    void push(type value) {
        Node* item = new Node(value);
        item->next = head;
        head = item;
    }

    type pop() {
        assert(!isEmpty());
        int element = head->data;
        Node* temp = head;
        head = head->next;
        delete temp;
        return element;
    }

    type peek() {
        assert(!isEmpty());
        int element = head->data;
        return element;
    }

    int isEmpty() {
        return !head;
    }
};

int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    if (op == '^')
        return 3;
    return 0;
}

string problem1(string infix) {
    string to_post = "";
    for (int i = 0; i < 26; ++i) {
        to_post += (char)(i + 'a');
        to_post += (char)(i + 'A');
        if (i < 10)
            to_post += (char)(i + '0');
    }

    Stack operators;
    string postfix;

    infix += '-';
    operators.push('#');

    for (int i = 0; i < (int)infix.size(); ++i) {
        if (to_post.find(infix[i]) != string::npos)
            postfix += infix[i];
        else if (infix[i] == '(')
            operators.push(infix[i]);
        else if (infix[i] == ')') {
            while (operators.peek() != '(')
                postfix += operators.pop();
            operators.pop();
        }
        else {
            while (precedence(operators.peek()) > precedence(infix[i]) ||
                precedence(operators.peek()) == precedence(infix[i]) && infix[i] != '^')
                postfix += operators.pop();
            operators.push(infix[i]);
        }
    }

    return postfix;
}

void test1() {
    cout << "\n\ntest1\n";
    string result = problem1("4^3^2");
    string expected = "432^^";

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test2() {
    cout << "\n\ntest2\n";
    string result = problem1("5+4^3^2-9");
    string expected = "5432^^+9-";

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test3() {
    cout << "\n\ntest3\n";
    string result = problem1("a+b*(c^d-e)^(f+G*h)-i");
    string expected = "abcd^e-fGh*+^*+i-";

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test4() {
    cout << "\n\ntest4\n";
    string result = problem1("1+2^3^4*5-6");
    string expected = "1234^^5*+6-";

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test5() {
    cout << "\n\ntest5\n";
    string result = problem1("1+2");
    string expected = "12+";

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test6() {
    cout << "\n\ntest6\n";
    string result = problem1("2*3+4");
    string expected = "23*4+";

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test7() {
    cout << "\n\ntest7\n";
    string result = problem1("(1+2)*3");
    string expected = "12+3*";

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test8() {
    cout << "\n\ntest8\n";
    string result = problem1("a+B");
    string expected = "aB+";

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test9() {
    cout << "\n\ntest9\n";
    string result = problem1("1+2*3-4/5");
    string expected = "123*+45/-";

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test10() {
    cout << "\n\ntest10\n";
    // Hint: Dummy '-' appended causes extra output
    string result = problem1("(a)");
    string expected = "a";

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test11() {
    cout << "\n\ntest11\n";
    string result = problem1("a+b*c");
    string expected = "abc*+";

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test12() {
    cout << "\n\ntest12\n";
    string result = problem1("a*b+c");
    string expected = "ab*c+";

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test13() {
    cout << "\n\ntest13\n";
    string result = problem1("2^3*4");
    string expected = "23^4*";

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test14() {
    cout << "\n\ntest14\n";
    string result = problem1("2*3^4");
    string expected = "234^*";

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test15() {
    cout << "\n\ntest15\n";
    // Hint: Dummy '-' appended causes extra output
    string result = problem1("((a+b))");
    string expected = "ab+";

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
    test11();
    test12();
    test13();
    test14();
    test15();

    cout << "\n\nNO RTE\n";
    return 0;
}
