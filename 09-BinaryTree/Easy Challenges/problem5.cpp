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

    bool problem5(int value) {
        bool is_found = (value == this->data);
        if (!is_found && left)
            is_found = left->problem5(value);
        if (!is_found && right)
            is_found = right->problem5(value);
        return is_found;
    }
};

string int_to_string(int val) {
    ostringstream oss;
    oss << val;
    return oss.str();
}

string bool_to_string(bool val) {
    return val ? "true" : "false";
}

BinaryTree* build_standard_tree() {
    BinaryTree* tree = new BinaryTree(7);
    tree->add({ 3 }, { 'L' });
    tree->add({ 13 }, { 'R' });
    tree->add({ 13, 10 }, { 'R', 'L' });
    tree->add({ 13, 15 }, { 'R', 'R' });
    return tree;
}

// Test E1: Problem example — search existing value 13
void testE1() {
    cout << "\n\ntestE1 - problem5(13) on standard tree, expected true\n";
    BinaryTree* tree = build_standard_tree();

    string expected = "true";
    string result = bool_to_string(tree->problem5(13));

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

// Test E2: Problem example — search absent value 70
void testE2() {
    cout << "\n\ntestE2 - problem5(70) on standard tree, expected false\n";
    BinaryTree* tree = build_standard_tree();

    string expected = "false";
    string result = bool_to_string(tree->problem5(70));

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

// Test E3: Search for root value — must be found without any child traversal
void testE3() {
    cout << "\n\ntestE3 - problem5(root=7), expected true\n";
    BinaryTree* tree = build_standard_tree();

    string expected = "true";
    string result = bool_to_string(tree->problem5(7));

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

// Test E4: Search for deepest left leaf — confirms full left traversal
void testE4() {
    cout << "\n\ntestE4 - problem5(deepest left leaf=3), expected true\n";
    BinaryTree* tree = build_standard_tree();

    string expected = "true";
    string result = bool_to_string(tree->problem5(3));

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

// Test E5: Search for deepest right leaf — confirms full right traversal
void testE5() {
    cout << "\n\ntestE5 - problem5(deepest right leaf=15), expected true\n";
    BinaryTree* tree = build_standard_tree();

    string expected = "true";
    string result = bool_to_string(tree->problem5(15));

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

// Test E6: Single node tree — search for root value; root is only node
void testE6() {
    cout << "\n\ntestE6 - single node, problem5(root=42), expected true\n";
    BinaryTree* tree = new BinaryTree(42);

    string expected = "true";
    string result = bool_to_string(tree->problem5(42));

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

// Test E7: Single node tree — search absent value; no children to traverse, must not crash
void testE7() {
    cout << "\n\ntestE7 - single node, problem5(99), expected false\n";
    BinaryTree* tree = new BinaryTree(42);

    string expected = "false";
    string result = bool_to_string(tree->problem5(99));

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

// Test E8: Left-skewed tree — search deepest left node; validates full left-only path traversal
void testE8() {
    cout << "\n\ntestE8 - left-skewed tree, problem5(deepest=1), expected true\n";
    BinaryTree* tree = new BinaryTree(10);
    tree->add({ 7 }, { 'L' });
    tree->add({ 7, 4 }, { 'L', 'L' });
    tree->add({ 7, 4, 1 }, { 'L', 'L', 'L' });

    string expected = "true";
    string result = bool_to_string(tree->problem5(1));

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

// Test E9: Right-skewed tree — search deepest right node; validates full right-only path traversal
void testE9() {
    cout << "\n\ntestE9 - right-skewed tree, problem5(deepest=8), expected true\n";
    BinaryTree* tree = new BinaryTree(2);
    tree->add({ 4 }, { 'R' });
    tree->add({ 4, 6 }, { 'R', 'R' });
    tree->add({ 4, 6, 8 }, { 'R', 'R', 'R' });

    string expected = "true";
    string result = bool_to_string(tree->problem5(8));

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

// Test E10: Near-miss value — hint: off-by-one must never produce false positive
void testE10() {
    cout << "\n\ntestE10 - problem5(14) where 13 exists, expected false\n";
    BinaryTree* tree = build_standard_tree();

    string expected = "false";
    string result = bool_to_string(tree->problem5(14));

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

// Test E11: Duplicate values — hint: must return true on first match without infinite loop
void testE11() {
    cout << "\n\ntestE11 - duplicate value 5 in multiple nodes, expected true\n";
    BinaryTree* tree = new BinaryTree(10);
    tree->add({ 5 }, { 'L' });
    tree->add({ 15 }, { 'R' });
    tree->add({ 15, 5 }, { 'R', 'L' });

    string expected = "true";
    string result = bool_to_string(tree->problem5(5));

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

// Test E12: Negative value present — must not be skipped or mishandled
void testE12() {
    cout << "\n\ntestE12 - problem5(-3) where -3 exists, expected true\n";
    BinaryTree* tree = new BinaryTree(-10);
    tree->add({ -5 }, { 'L' });
    tree->add({ -3 }, { 'R' });
    tree->add({ -3, -1 }, { 'R', 'R' });

    string expected = "true";
    string result = bool_to_string(tree->problem5(-3));

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

// Test E13: Negative value absent — confirms false returned correctly for negative miss
void testE13() {
    cout << "\n\ntestE13 - problem5(-99) where -99 absent, expected false\n";
    BinaryTree* tree = new BinaryTree(-10);
    tree->add({ -5 }, { 'L' });
    tree->add({ -3 }, { 'R' });
    tree->add({ -3, -1 }, { 'R', 'R' });

    string expected = "false";
    string result = bool_to_string(tree->problem5(-99));

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

int main() {
    testE1();
    testE2();
    testE3();
    testE4();
    testE5();
    testE6();
    testE7();
    testE8();
    testE9();
    testE10();
    testE11();
    testE12();
    testE13();

    cout << "\n\nNO RTE\n";
    return 0;
}
