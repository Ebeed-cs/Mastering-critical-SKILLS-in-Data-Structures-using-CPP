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

    int tree_height() {
        int res = 0;
        if (left)
            res = 1 + left->tree_height();
        if (right)
            res = max(res, 1 + right->tree_height());
        return res;
    }

    int total_nodes() {
        int res = 1;
        if (left)
            res += left->total_nodes();
        if (right)
            res += right->total_nodes();
        return res;
    }

    bool problem6_formula() {
        // # nodes = 2^(levels) - 1 , levels = h + 1

        int left_side = total_nodes();
        int h = tree_height();

        int right_side = std::pow(2, h + 1) - 1;

        return (left_side == right_side);
    }

    bool problem6() {
        if ((!left && right) || (!right && left))
            return false;

        int left_height = (left) ? left->tree_height() : 0;
        int right_height = (right) ? right->tree_height() : 0;
        if (left_height != right_height)
            return false;

        if (left && !left->problem6())
            return false;
        if (right && !right->problem6())
            return false;
        return true;
    }
};

// TC2: single root only
void test1() {
    cout << "\n\ntest1 - Single root node only\n";
    BinaryTree tree(1);

    string expected = "1";
    string result = tree.problem6() ? "1" : "0";

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

// TC3: root with only left child
void test2() {
    cout << "\n\ntest2 - Root with only left child\n";
    BinaryTree tree(1);
    tree.add({ 1 }, { 'L' });

    string expected = "0";
    string result = tree.problem6() ? "1" : "0";

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

// TC4: root with only right child
void test3() {
    cout << "\n\ntest3 - Root with only right child\n";
    BinaryTree tree(1);
    tree.add({ 1 }, { 'R' });

    string expected = "0";
    string result = tree.problem6() ? "1" : "0";

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

// TC5: perfect tree height 1 (root + 2 children)
void test4() {
    cout << "\n\ntest4 - Perfect tree height 1 (3 nodes)\n";
    BinaryTree tree(1);
    tree.add({ 1 }, { 'L' });
    tree.add({ 1 }, { 'R' });

    string expected = "1";
    string result = tree.problem6() ? "1" : "0";

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

// TC6: perfect tree height 2 (7 nodes)
void test5() {
    cout << "\n\ntest5 - Perfect tree height 2 (7 nodes)\n";
    BinaryTree tree(1);
    tree.add({ 1 }, { 'L' });
    tree.add({ 1 }, { 'R' });
    tree.add({ 1, 1 }, { 'L', 'L' });
    tree.add({ 1, 1 }, { 'L', 'R' });
    tree.add({ 1, 1 }, { 'R', 'L' });
    tree.add({ 1, 1 }, { 'R', 'R' });

    string expected = "1";
    string result = tree.problem6() ? "1" : "0";

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

// TC7: root + 2 children, only left child has 2 children (right is leaf)
// Hint: condition 1 passes everywhere but leaves are at different depths
void test6() {
    cout << "\n\ntest6 - Left subtree deeper than right (leaves at different depths)\n";
    BinaryTree tree(1);
    tree.add({ 1 }, { 'L' });
    tree.add({ 1 }, { 'R' });
    tree.add({ 1, 1 }, { 'L', 'L' });
    tree.add({ 1, 1 }, { 'L', 'R' });

    string expected = "0";
    string result = tree.problem6() ? "1" : "0";

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

// TC8: left subtree perfect height 2, right subtree perfect height 1
void test7() {
    cout << "\n\ntest7 - Left perfect h2, right perfect h1 (unequal subtree heights)\n";
    BinaryTree tree(1);
    tree.add({ 1 }, { 'L' });
    tree.add({ 1 }, { 'R' });
    tree.add({ 1, 1 }, { 'L', 'L' });
    tree.add({ 1, 1 }, { 'L', 'R' });
    tree.add({ 1, 1 }, { 'R', 'L' });
    tree.add({ 1, 1 }, { 'R', 'R' });
    tree.add({ 1, 1, 1 }, { 'L', 'L', 'L' });
    tree.add({ 1, 1, 1 }, { 'L', 'L', 'R' });
    tree.add({ 1, 1, 1 }, { 'L', 'R', 'L' });
    tree.add({ 1, 1, 1 }, { 'L', 'R', 'R' });

    string expected = "0";
    string result = tree.problem6() ? "1" : "0";

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

// TC9: deep violation — one grandchild has only 1 child
void test8() {
    cout << "\n\ntest8 - Deep violation: grandchild has only 1 child\n";
    BinaryTree tree(1);
    tree.add({ 1 }, { 'L' });
    tree.add({ 1 }, { 'R' });
    tree.add({ 1, 1 }, { 'L', 'L' });
    tree.add({ 1, 1 }, { 'L', 'R' });
    tree.add({ 1, 1 }, { 'R', 'L' });
    tree.add({ 1, 1 }, { 'R', 'R' });
    // Only left child of left-left node — violation deep in tree
    tree.add({ 1, 1, 1 }, { 'L', 'L', 'L' });

    string expected = "0";
    string result = tree.problem6() ? "1" : "0";

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

// TC10: perfect tree height 3 (15 nodes)
void test9() {
    cout << "\n\ntest9 - Perfect tree height 3 (15 nodes)\n";
    BinaryTree tree(1);
    tree.add({ 1 }, { 'L' });
    tree.add({ 1 }, { 'R' });
    tree.add({ 1, 1 }, { 'L', 'L' });
    tree.add({ 1, 1 }, { 'L', 'R' });
    tree.add({ 1, 1 }, { 'R', 'L' });
    tree.add({ 1, 1 }, { 'R', 'R' });
    tree.add({ 1, 1, 1 }, { 'L', 'L', 'L' });
    tree.add({ 1, 1, 1 }, { 'L', 'L', 'R' });
    tree.add({ 1, 1, 1 }, { 'L', 'R', 'L' });
    tree.add({ 1, 1, 1 }, { 'L', 'R', 'R' });
    tree.add({ 1, 1, 1 }, { 'R', 'L', 'L' });
    tree.add({ 1, 1, 1 }, { 'R', 'L', 'R' });
    tree.add({ 1, 1, 1 }, { 'R', 'R', 'L' });
    tree.add({ 1, 1, 1 }, { 'R', 'R', 'R' });

    string expected = "1";
    string result = tree.problem6() ? "1" : "0";

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
