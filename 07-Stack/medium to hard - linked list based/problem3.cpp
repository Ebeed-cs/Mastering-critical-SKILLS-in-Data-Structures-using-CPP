#include <iostream>
#include <cassert>
#include <algorithm>
#include <sstream>
#include <string>
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

std::string fixParanthesis(std::string reversedInfix) {
    for (char& c : reversedInfix) {
        if (c == '(') c = ')';
        else if (c == ')') c = '(';
    }
    return reversedInfix;
}

string problem3(string infix) {
    string to_post = "";
    for (int i = 0; i < 26; ++i) {
        to_post += (char)(i + 'a');
        to_post += (char)(i + 'A');
        if (i < 10)
            to_post += (char)(i + '0');
    }

    std::reverse(infix.begin(), infix.end());
    infix = fixParanthesis(infix);

    Stack operators;
    string prefix;

    infix += '%';       // any other operators = 0 precedence
    operators.push('#');

    for (int i = 0; i < (int)infix.size(); ++i) {
        if (to_post.find(infix[i]) != string::npos)
            prefix += infix[i];
        else if (infix[i] == '(')
            operators.push(infix[i]);
        else if (infix[i] == ')') {
            while (operators.peek() != '(')
                prefix += operators.pop();
            operators.pop();
        }
        else {
            while (precedence(operators.peek()) > precedence(infix[i]) ||
                precedence(operators.peek()) == precedence(infix[i]) && infix[i] == '^')
                prefix += operators.pop();
            operators.push(infix[i]);
        }
    }
    std::reverse(prefix.begin(), prefix.end());
    return prefix;
}

void test1() {
    cout << "\n\ntest1\n";
    string result = problem3("1+2");
    string expected = "+12";

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test2() {
    cout << "\n\ntest2\n";
    string result = problem3("9-2+3");
    string expected = "+-923";

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        // Hint: Check left-to-right associativity for same precedence operators
        assert(false);
    }
    cout << "PASS\n";
}

void test3() {
    cout << "\n\ntest3\n";
    string result = problem3("4^3^2");
    string expected = "^4^32";

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test4() {
    cout << "\n\ntest4\n";
    string result = problem3("1+2+3");
    string expected = "++123";

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test5() {
    cout << "\n\ntest5\n";
    string result = problem3("1+2*3");
    string expected = "+1*23";

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test6() {
    cout << "\n\ntest6\n";
    string result = problem3("2*3+4");
    string expected = "+*234";

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test7() {
    cout << "\n\ntest7\n";
    string result = problem3("1+3*5-8/2");
    string expected = "-+1*35/82";

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test8() {
    cout << "\n\ntest8\n";
    string result = problem3("(1+2)*3");
    string expected = "*+123";

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

void test9() {
    cout << "\n\ntest9\n";
    string result = problem3("1");
    string expected = "1";

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        // Hint: Check handling of single operand with extra operator appended
        assert(false);
    }
    cout << "PASS\n";
}

void test10() {
    cout << "\n\ntest10\n";
    string result = problem3("((1+2))");
    string expected = "+12";

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
