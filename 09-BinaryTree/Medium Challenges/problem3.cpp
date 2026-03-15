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

    void clear() {
        if (left) {
            left->clear();
            delete left;
            left = nullptr;
        }
        if (right) {
            right->clear();
            delete right;
            right = nullptr;
        }
    }

    void problem3() {
        std::cout << this->data << " ";
        if (left)
            left->problem3();
        else if (right)
            right->problem3();
    }

    // Helper: captures problem3 output as string
    string boundary_to_string() {
        ostringstream oss;
        capture_boundary(oss);
        string s = oss.str();
        if (!s.empty() && s.back() == ' ')
            s.pop_back();
        return s;
    }

    void capture_boundary(ostringstream& oss) {
        oss << this->data << " ";
        if (left)
            left->capture_boundary(oss);
        else if (right)
            right->capture_boundary(oss);
    }

    ~BinaryTree() {
        clear();
    }
};

// ===== Test Cases =====

// TC1: PDF example — prefer-left, fallback-to-right across multiple levels
void test1() {
    cout << "\n\ntest1 - PDF example tree\n";
    //         2
    //        / \
    //       3   13
    //      / \  / \
    //     5   8 8   7
    //      \
    //       8
    //        \
    //         6
    //        /
    //       7
    //        \
    //        15
    BinaryTree tree(2);
    tree.add({ 3 }, { 'L' });
    tree.add({ 13 }, { 'R' });
    tree.add({ 3, 5 }, { 'L', 'L' });
    tree.add({ 3, 8 }, { 'L', 'R' });
    tree.add({ 13, 8 }, { 'R', 'L' });
    tree.add({ 13, 7 }, { 'R', 'R' });
    tree.add({ 3, 5, 8 }, { 'L', 'L', 'R' });
    tree.add({ 3, 5, 8, 6 }, { 'L', 'L', 'R', 'R' });
    tree.add({ 3, 5, 8, 6, 7 }, { 'L', 'L', 'R', 'R', 'L' });
    tree.add({ 3, 5, 8, 6, 7, 15 }, { 'L', 'L', 'R', 'R', 'L', 'R' });

    string expected = "2 3 5 8 6 7 15";
    string result = tree.boundary_to_string();

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

// TC2: Single node — root is both start and left-most node
void test2() {
    cout << "\n\ntest2 - single node\n";
    //   1
    BinaryTree tree(1);

    string expected = "1";
    string result = tree.boundary_to_string();

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

// TC3: Pure left-skewed tree — always go left
void test3() {
    cout << "\n\ntest3 - pure left-skewed\n";
    //   1
    //  /
    // 2
   // /
   // 3
    BinaryTree tree(1);
    tree.add({ 2 }, { 'L' });
    tree.add({ 2, 3 }, { 'L', 'L' });

    string expected = "1 2 3";
    string result = tree.boundary_to_string();

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

// TC4: Pure right-skewed — no left children, entire right spine is boundary
void test4() {
    cout << "\n\ntest4 - pure right-skewed\n";
    //   1
    //    \
    //     2
    //      \
    //       3
    BinaryTree tree(1);
    tree.add({ 2 }, { 'R' });
    tree.add({ 2, 3 }, { 'R', 'R' });

    string expected = "1 2 3";
    string result = tree.boundary_to_string();

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

// TC5: Left child exists but always leads right — prefer-left then forced-right
void test5() {
    cout << "\n\ntest5 - left child always leads right\n";
    //       1
    //      / \
    //     2   3
    //      \
    //       4
    //        \
    //         5
    BinaryTree tree(1);
    tree.add({ 2 }, { 'L' });
    tree.add({ 3 }, { 'R' });
    tree.add({ 2, 4 }, { 'L', 'R' });
    tree.add({ 2, 4, 5 }, { 'L', 'R', 'R' });

    string expected = "1 2 4 5";
    string result = tree.boundary_to_string();

    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    cout << "PASS\n";
}

// TC6: Root with two children only — right subtree must be fully ignored
void test6() {
    cout << "\n\ntest6 - root with two children, no deeper nodes\n";
    //   1
    //  / \
    // 2   3
    BinaryTree tree(1);
    tree.add({ 2 }, { 'L' });
    tree.add({ 3 }, { 'R' });

    string expected = "1 2";
    string result = tree.boundary_to_string();

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

    cout << "\n\nNO RTE\n";
    return 0;
}
