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

    int problem4() {
        bool is_leaf = true;
        int res = 0;
        if (left) {
            is_leaf = false;
            res += left->problem4();
        }
        if (right) {
            is_leaf = false;
            res += right->problem4();
        }
        if (is_leaf)
            res++;
        return res;
    }
};

string int_to_string(int val) {
    ostringstream oss;
    oss << val;
    return oss.str();
}

// Test L1: Single root node — root itself is a leaf; must return 1 not 0
void testL1() {
    cout << "\n\ntestL1 - single root node (is a leaf), expected 1\n";
    BinaryTree* tree = new BinaryTree(10);

    string expected = "1";
    string result = int_to_string(tree->problem4());

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

// Test L2: Problem description example — 3 leaf nodes
void testL2() {
    cout << "\n\ntestL2 - problem example tree, expected 3\n";
    BinaryTree* tree = new BinaryTree(7);
    tree->add({ 3 }, { 'L' });
    tree->add({ 13 }, { 'R' });
    tree->add({ 13, 10 }, { 'R', 'L' });
    tree->add({ 13, 15 }, { 'R', 'R' });

    string expected = "3";
    string result = int_to_string(tree->problem4());

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

// Test L3: Left-skewed 4 nodes — hint: only deepest node is leaf; intermediate nodes must not be counted
void testL3() {
    cout << "\n\ntestL3 - left-skewed 4 nodes, expected 1\n";
    BinaryTree* tree = new BinaryTree(10);
    tree->add({ 8 }, { 'L' });
    tree->add({ 8, 6 }, { 'L', 'L' });
    tree->add({ 8, 6, 4 }, { 'L', 'L', 'L' });

    string expected = "1";
    string result = int_to_string(tree->problem4());

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

// Test L4: Right-skewed 4 nodes — hint: only deepest right node is leaf; mirrors left-skew
void testL4() {
    cout << "\n\ntestL4 - right-skewed 4 nodes, expected 1\n";
    BinaryTree* tree = new BinaryTree(2);
    tree->add({ 4 }, { 'R' });
    tree->add({ 4, 6 }, { 'R', 'R' });
    tree->add({ 4, 6, 8 }, { 'R', 'R', 'R' });

    string expected = "1";
    string result = int_to_string(tree->problem4());

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

// Test L5: Perfect binary tree 3 levels — all 4 bottom nodes are leaves; no internal node counted
void testL5() {
    cout << "\n\ntestL5 - perfect binary tree 3 levels, expected 4\n";
    BinaryTree* tree = new BinaryTree(1);
    tree->add({ 2 }, { 'L' });
    tree->add({ 3 }, { 'R' });
    tree->add({ 2, 4 }, { 'L', 'L' });
    tree->add({ 2, 5 }, { 'L', 'R' });
    tree->add({ 3, 6 }, { 'R', 'L' });
    tree->add({ 3, 7 }, { 'R', 'R' });

    string expected = "4";
    string result = int_to_string(tree->problem4());

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

// Test L6: Root with two children each having two children — 4 leaves across both subtrees
void testL6() {
    cout << "\n\ntestL6 - balanced 3-level tree, expected 4\n";
    BinaryTree* tree = new BinaryTree(10);
    tree->add({ 5 }, { 'L' });
    tree->add({ 15 }, { 'R' });
    tree->add({ 5, 3 }, { 'L', 'L' });
    tree->add({ 5, 7 }, { 'L', 'R' });
    tree->add({ 15, 12 }, { 'R', 'L' });
    tree->add({ 15, 18 }, { 'R', 'R' });

    string expected = "4";
    string result = int_to_string(tree->problem4());

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

// Test L7: Root with left child only — left child is sole leaf; absent right must not inflate count
void testL7() {
    cout << "\n\ntestL7 - root + left child only, expected 1\n";
    BinaryTree* tree = new BinaryTree(10);
    tree->add({ 5 }, { 'L' });

    string expected = "1";
    string result = int_to_string(tree->problem4());

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

// Test L8: Root with right child only — right child is sole leaf; absent left must not inflate count
void testL8() {
    cout << "\n\ntestL8 - root + right child only, expected 1\n";
    BinaryTree* tree = new BinaryTree(10);
    tree->add({ 15 }, { 'R' });

    string expected = "1";
    string result = int_to_string(tree->problem4());

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

// Test L9: Unbalanced — left depth 3, right depth 1; hint: leaf counts from both subtrees must be summed
void testL9() {
    cout << "\n\ntestL9 - unbalanced left=3 levels right=1 level, expected 3\n";
    BinaryTree* tree = new BinaryTree(10);
    tree->add({ 5 }, { 'L' });
    tree->add({ 5, 3 }, { 'L', 'L' });
    tree->add({ 5, 7 }, { 'L', 'R' });
    tree->add({ 5, 3, 1 }, { 'L', 'L', 'L' });
    tree->add({ 20 }, { 'R' });

    string expected = "3";
    string result = int_to_string(tree->problem4());

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

// Test L10: All duplicate values — hint: leaf count is purely structural; duplicates must not cause merging
void testL10() {
    cout << "\n\ntestL10 - all duplicate values, expected 2\n";
    BinaryTree* tree = new BinaryTree(5);
    tree->add({ 5 }, { 'L' });
    tree->add({ 5 }, { 'R' });

    string expected = "2";
    string result = int_to_string(tree->problem4());

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

int main() {
    testL1();
    testL2();
    testL3();
    testL4();
    testL5();
    testL6();
    testL7();
    testL8();
    testL9();
    testL10();

    cout << "\n\nNO RTE\n";
    return 0;
}
