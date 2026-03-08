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

    void print_inorder() {
        if (left)
            left->print_inorder();
        cout << data << " ";
        if (right)
            right->print_inorder();
    }

    int problem3() {
        int res = 1;
        if (left)
            res += left->problem3();
        if (right)
            res += right->problem3();
        return res;
    }
};

string int_to_string(int val) {
    ostringstream oss;
    oss << val;
    return oss.str();
}

// Test 1: Single root node only
void testN1() {
    cout << "\n\ntestN1 - single root node, expected 1\n";
    BinaryTree* tree = new BinaryTree(10);

    string expected = "1";
    string result = int_to_string(tree->problem3());

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

// Test 2: Problem description example — 5 nodes
void testN2() {
    cout << "\n\ntestN2 - problem example tree, expected 5\n";
    BinaryTree* tree = new BinaryTree(7);
    tree->add({ 3 }, { 'L' });
    tree->add({ 13 }, { 'R' });
    tree->add({ 13, 10 }, { 'R', 'L' });
    tree->add({ 13, 15 }, { 'R', 'R' });

    string expected = "5";
    string result = int_to_string(tree->problem3());

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

// Test 3: Left-skewed tree — hint: only left pointers followed; right never visited
void testN3() {
    cout << "\n\ntestN3 - left-skewed 4 nodes, expected 4\n";
    BinaryTree* tree = new BinaryTree(10);
    tree->add({ 8 }, { 'L' });
    tree->add({ 8, 6 }, { 'L', 'L' });
    tree->add({ 8, 6, 4 }, { 'L', 'L', 'L' });

    string expected = "4";
    string result = int_to_string(tree->problem3());

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

// Test 4: Right-skewed tree — hint: only right pointers followed; left never visited
void testN4() {
    cout << "\n\ntestN4 - right-skewed 4 nodes, expected 4\n";
    BinaryTree* tree = new BinaryTree(2);
    tree->add({ 4 }, { 'R' });
    tree->add({ 4, 6 }, { 'R', 'R' });
    tree->add({ 4, 6, 8 }, { 'R', 'R', 'R' });

    string expected = "4";
    string result = int_to_string(tree->problem3());

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

// Test 5: Balanced complete binary tree — 3 levels, 7 nodes
void testN5() {
    cout << "\n\ntestN5 - complete binary tree 7 nodes, expected 7\n";
    BinaryTree* tree = new BinaryTree(1);
    tree->add({ 2 }, { 'L' });
    tree->add({ 3 }, { 'R' });
    tree->add({ 2, 4 }, { 'L', 'L' });
    tree->add({ 2, 5 }, { 'L', 'R' });
    tree->add({ 3, 6 }, { 'R', 'L' });
    tree->add({ 3, 7 }, { 'R', 'R' });

    string expected = "7";
    string result = int_to_string(tree->problem3());

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

// Test 6: Mixed direction path — root → L → R (3 nodes)
void testN6() {
    cout << "\n\ntestN6 - mixed direction path L then R, expected 3\n";
    BinaryTree* tree = new BinaryTree(10);
    tree->add({ 5 }, { 'L' });
    tree->add({ 5, 8 }, { 'L', 'R' });

    string expected = "3";
    string result = int_to_string(tree->problem3());

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

// Test 7: Perfect binary tree depth 4 — 15 nodes; hint: must equal 2^4 - 1
void testN7() {
    cout << "\n\ntestN7 - perfect binary tree depth 4, expected 15\n";
    BinaryTree* tree = new BinaryTree(1);
    tree->add({ 2 }, { 'L' });
    tree->add({ 3 }, { 'R' });
    tree->add({ 2, 4 }, { 'L', 'L' });
    tree->add({ 2, 5 }, { 'L', 'R' });
    tree->add({ 3, 6 }, { 'R', 'L' });
    tree->add({ 3, 7 }, { 'R', 'R' });
    tree->add({ 2, 4, 8 }, { 'L', 'L', 'L' });
    tree->add({ 2, 4, 9 }, { 'L', 'L', 'R' });
    tree->add({ 2, 5, 10 }, { 'L', 'R', 'L' });
    tree->add({ 2, 5, 11 }, { 'L', 'R', 'R' });
    tree->add({ 3, 6, 12 }, { 'R', 'L', 'L' });
    tree->add({ 3, 6, 13 }, { 'R', 'L', 'R' });
    tree->add({ 3, 7, 14 }, { 'R', 'R', 'L' });
    tree->add({ 3, 7, 15 }, { 'R', 'R', 'R' });

    string expected = "15";
    string result = int_to_string(tree->problem3());

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

// Test 8: Unbalanced — left subtree 3 nodes, right subtree 1 node; hint: must sum both, not max
void testN8() {
    cout << "\n\ntestN8 - unbalanced left=3 right=1, expected 5\n";
    BinaryTree* tree = new BinaryTree(10);
    tree->add({ 5 }, { 'L' });
    tree->add({ 5, 3 }, { 'L', 'L' });
    tree->add({ 5, 7 }, { 'L', 'R' });
    tree->add({ 20 }, { 'R' });

    string expected = "5";
    string result = int_to_string(tree->problem3());

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

// Test 9: Duplicate values — hint: count is structural; duplicates must NOT be deduplicated
void testN9() {
    cout << "\n\ntestN9 - all duplicate values, expected 4\n";
    BinaryTree* tree = new BinaryTree(5);
    tree->add({ 5 }, { 'L' });
    tree->add({ 5 }, { 'R' });
    tree->add({ 5, 5 }, { 'R', 'R' });

    string expected = "4";
    string result = int_to_string(tree->problem3());

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

int main() {
    testN1();
    testN2();
    testN3();
    testN4();
    testN5();
    testN6();
    testN7();
    testN8();
    testN9();

    cout << "\n\nNO RTE\n";
    return 0;
}
