#include <iostream>
#include <cassert>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <algorithm>
#include <sstream>
using namespace std;

class BinaryTree {
private:
    int data{ };
    BinaryTree* left{ };
    BinaryTree* right{ };

public:

    BinaryTree(int data) :
        data(data) {
    }

    void add(vector<int> values, vector<char> direction) {
        assert(values.size() == direction.size());
        BinaryTree* current = this;
        for (int i = 0; i < (int)values.size(); ++i) {
            if (direction[i] == 'L') {
                if (!current->left)
                    current->left = new BinaryTree(values[i]);
                else
                    assert(current->left->data == values[i]);
                current = current->left;
            }
            else {
                if (!current->right)
                    current->right = new BinaryTree(values[i]);
                else
                    assert(current->right->data == values[i]);
                current = current->right;
            }
        }
    }

    int problem1() {
        int max_num = INT_MIN;
        if (left)
            max_num = std::max(left->problem1(), max_num);
        if (right)
            max_num = std::max(right->problem1(), max_num);
        max_num = std::max(this->data, max_num);
        return max_num;
    }

    void print_inorder() {
        if (left)
            left->print_inorder();
        cout << data << " ";
        if (right)
            right->print_inorder();
    }
};

string int_to_string(int val) {
    ostringstream oss;
    oss << val;
    return oss.str();
}

// Test 1: Full tree — max is in rightmost leaf
void test1() {
    cout << "\n\ntest1 - max in rightmost leaf (multi-level tree)\n";
    BinaryTree* tree = new BinaryTree(7);
    tree->add({ 3 }, { 'L' });
    tree->add({ 3, 1 }, { 'L', 'L' });
    tree->add({ 3, 5 }, { 'L', 'R' });
    tree->add({ 13 }, { 'R' });
    tree->add({ 13, 10 }, { 'R', 'L' });
    tree->add({ 13, 15 }, { 'R', 'R' });

    string expected = "15";
    string result = int_to_string(tree->problem1());

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

// Test 2: Single node tree
void test2() {
    cout << "\n\ntest2 - single node\n";
    BinaryTree* tree = new BinaryTree(42);

    string expected = "42";
    string result = int_to_string(tree->problem1());

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

// Test 3: Left-skewed tree — max is at root
void test3() {
    cout << "\n\ntest3 - left-skewed tree, max at root\n";
    BinaryTree* tree = new BinaryTree(10);
    tree->add({ 8 }, { 'L' });
    tree->add({ 8, 6 }, { 'L', 'L' });
    tree->add({ 8, 6, 4 }, { 'L', 'L', 'L' });

    string expected = "10";
    string result = int_to_string(tree->problem1());

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

// Test 4: Right-skewed tree — max at deepest right node
void test4() {
    cout << "\n\ntest4 - right-skewed tree, max at deepest right\n";
    BinaryTree* tree = new BinaryTree(2);
    tree->add({ 4 }, { 'R' });
    tree->add({ 4, 6 }, { 'R', 'R' });
    tree->add({ 4, 6, 8 }, { 'R', 'R', 'R' });

    string expected = "8";
    string result = int_to_string(tree->problem1());

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

// Test 5: Root is maximum
void test5() {
    cout << "\n\ntest5 - root is the maximum value\n";
    BinaryTree* tree = new BinaryTree(100);
    tree->add({ 50 }, { 'L' });
    tree->add({ 50, 25 }, { 'L', 'L' });
    tree->add({ 50, 75 }, { 'L', 'R' });

    string expected = "100";
    string result = int_to_string(tree->problem1());

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

// Test 6: All negative values — hint: INT_MIN init is safe here; verify no accidental 0 return
void test6() {
    cout << "\n\ntest6 - all negative values\n";
    BinaryTree* tree = new BinaryTree(-5);
    tree->add({ -10 }, { 'L' });
    tree->add({ -3 }, { 'R' });
    tree->add({ -3, -1 }, { 'R', 'R' });

    string expected = "-1";
    string result = int_to_string(tree->problem1());

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

// Test 7: Mixed negative and positive — matches problem description example
void test7() {
    cout << "\n\ntest7 - mixed negative and positive (problem example: max=13)\n";
    BinaryTree* tree = new BinaryTree(2);
    tree->add({ 3 }, { 'L' });
    tree->add({ 13 }, { 'R' });
    tree->add({ 13, 8 }, { 'R', 'R' });
    tree->add({ 13, 7 }, { 'R', 'L' });

    string expected = "13";
    string result = int_to_string(tree->problem1());

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

// Test 8: Duplicate values — hint: duplicates are structurally valid; assert in add() guards mismatched reuse
void test8() {
    cout << "\n\ntest8 - duplicate values\n";
    BinaryTree* tree = new BinaryTree(7);
    tree->add({ 7 }, { 'L' });
    tree->add({ 7 }, { 'R' });

    string expected = "7";
    string result = int_to_string(tree->problem1());

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

// Test 9: Max buried deep in left subtree
void test9() {
    cout << "\n\ntest9 - max buried deep in left subtree\n";
    BinaryTree* tree = new BinaryTree(10);
    tree->add({ 5 }, { 'L' });
    tree->add({ 5, 99 }, { 'L', 'R' });
    tree->add({ 3 }, { 'R' });

    string expected = "99";
    string result = int_to_string(tree->problem1());

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
