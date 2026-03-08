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

    int problem2() {
        int res = 0;
        if (left)
            res = 1 + left->problem2();
        if (right)
            res = std::max(1 + right->problem2(), res);
        return res;
    }
};

string int_to_string(int val) {
    ostringstream oss;
    oss << val;
    return oss.str();
}

// ===== problem2() Tests =====

// Test H1: Single node — root only
void testH1() {
    cout << "\n\ntestH1 - single node (root only), expected height 0\n";
    BinaryTree* tree = new BinaryTree(1);

    string expected = "0";
    string result = int_to_string(tree->problem2());

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

// Test H2: Root with left child only
void testH2() {
    cout << "\n\ntestH2 - root + left child only, expected height 1\n";
    BinaryTree* tree = new BinaryTree(10);
    tree->add({ 5 }, { 'L' });

    string expected = "1";
    string result = int_to_string(tree->problem2());

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

// Test H3: Root with right child only
void testH3() {
    cout << "\n\ntestH3 - root + right child only, expected height 1\n";
    BinaryTree* tree = new BinaryTree(10);
    tree->add({ 15 }, { 'R' });

    string expected = "1";
    string result = int_to_string(tree->problem2());

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

// Test H4: Balanced tree matching problem description — height comes from right branch
void testH4() {
    cout << "\n\ntestH4 - balanced tree (problem example), expected height 2\n";
    BinaryTree* tree = new BinaryTree(7);
    tree->add({ 3 }, { 'L' });
    tree->add({ 13 }, { 'R' });
    tree->add({ 13, 10 }, { 'R', 'L' });
    tree->add({ 13, 15 }, { 'R', 'R' });

    string expected = "2";
    string result = int_to_string(tree->problem2());

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

// Test H5: Left-skewed tree depth 5 — hint: only left path exists; right is never visited
void testH5() {
    cout << "\n\ntestH5 - left-skewed tree depth 5, expected height 5\n";
    BinaryTree* tree = new BinaryTree(1);
    tree->add({ 2 }, { 'L' });
    tree->add({ 2, 3 }, { 'L', 'L' });
    tree->add({ 2, 3, 4 }, { 'L', 'L', 'L' });
    tree->add({ 2, 3, 4, 5 }, { 'L', 'L', 'L', 'L' });
    tree->add({ 2, 3, 4, 5, 6 }, { 'L', 'L', 'L', 'L', 'L' });

    string expected = "5";
    string result = int_to_string(tree->problem2());

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

// Test H6: Right-skewed tree depth 5 — hint: only right path exists; verifies right recursion depth
void testH6() {
    cout << "\n\ntestH6 - right-skewed tree depth 5, expected height 5\n";
    BinaryTree* tree = new BinaryTree(1);
    tree->add({ 2 }, { 'R' });
    tree->add({ 2, 3 }, { 'R', 'R' });
    tree->add({ 2, 3, 4 }, { 'R', 'R', 'R' });
    tree->add({ 2, 3, 4, 5 }, { 'R', 'R', 'R', 'R' });
    tree->add({ 2, 3, 4, 5, 6 }, { 'R', 'R', 'R', 'R', 'R' });

    string expected = "5";
    string result = int_to_string(tree->problem2());

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

// Test H7: Left subtree deeper than right — must return max, not right-side default
void testH7() {
    cout << "\n\ntestH7 - left depth 3, right depth 1, expected height 3\n";
    BinaryTree* tree = new BinaryTree(10);
    tree->add({ 5 }, { 'L' });
    tree->add({ 5, 3 }, { 'L', 'L' });
    tree->add({ 5, 3, 1 }, { 'L', 'L', 'L' });
    tree->add({ 20 }, { 'R' });

    string expected = "3";
    string result = int_to_string(tree->problem2());

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

// Test H8: Complete binary tree height 3 — symmetric, no ambiguity
void testH8() {
    cout << "\n\ntestH8 - complete binary tree height 3, expected height 3\n";
    BinaryTree* tree = new BinaryTree(1);
    tree->add({ 2 }, { 'L' });
    tree->add({ 3 }, { 'R' });
    tree->add({ 2, 4 }, { 'L', 'L' });
    tree->add({ 2, 5 }, { 'L', 'R' });
    tree->add({ 3, 6 }, { 'R', 'L' });
    tree->add({ 3, 7 }, { 'R', 'R' });
    tree->add({ 3, 7, 8 }, { 'R', 'R', 'R' });

    string expected = "3";
    string result = int_to_string(tree->problem2());

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

// Test H9: Right deeper than left — confirms max selection over left-priority
void testH9() {
    cout << "\n\ntestH9 - right depth 3, left depth 1, expected height 3\n";
    BinaryTree* tree = new BinaryTree(10);
    tree->add({ 5 }, { 'L' });
    tree->add({ 20 }, { 'R' });
    tree->add({ 20, 25 }, { 'R', 'R' });
    tree->add({ 20, 25, 30 }, { 'R', 'R', 'R' });

    string expected = "3";
    string result = int_to_string(tree->problem2());

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}
int main() {
    // problem2() tests
    testH1();
    testH2();
    testH3();
    testH4();
    testH5();
    testH6();
    testH7();
    testH8();
    testH9();

    cout << "\n\nNO RTE\n";
    return 0;
}
