#include <iostream>
#include <cassert>
#include <vector>
#include <queue>
#include <climits>
#include <stack>
#include <algorithm>
using namespace std;

class BinarySearchTree {
private:
    int data{ };

public:
    BinarySearchTree* left{ };
    BinarySearchTree* right{ };
    BinarySearchTree* parent{ };

    BinarySearchTree(int data, BinarySearchTree* parent) :
        data(data), parent(parent) {
    }

    void print_inorder() {
        if (left)
            left->print_inorder();
        cout << data << " ";
        if (right)
            right->print_inorder();
    }

    void insert(int target) {
        if (target < data) {
            if (!left) {
                left = new BinarySearchTree(target, this);
            }
            else
                left->insert(target);
        }
        else if (target > data) {
            if (!right)
                right = new BinarySearchTree(target, this);
            else
                right->insert(target);
        } // else: exists already
    }

    int min_value() {
        BinarySearchTree* cur = this;
        while (cur && cur->left)
            cur = cur->left;
        return cur->data;
    }

    int max_value() {
        BinarySearchTree* cur = this;
        while (cur && cur->right)
            cur = cur->right;
        return cur->data;
    }

    BinarySearchTree* search(int target) {
        if (target == data)
            return this;
        if (target < data)
            if (left) return left->search(target);
        if (target > data)
            if (right) return right->search(target);
        return nullptr;
    }

    int problem1(int target) {
        BinarySearchTree* cur = search(target);
        if (!cur) return -1234; // the target not found 
        if (cur->right)
            return cur->right->min_value();
        if (max_value() == cur->data)
            return -1234;
        while (cur->parent->left != cur)
            cur = cur->parent;
        return cur->parent->data;
    }
};



void test_cases()
{
    BinarySearchTree* tree = new BinarySearchTree(15, nullptr);
    tree->insert(6);
    tree->insert(1);
    tree->insert(8);
    tree->insert(10);
    tree->insert(9);
    tree->insert(14);

    tree->insert(20);

    cout << tree->problem1(14) << "\n"; // 15
    cout << tree->problem1(9) << "\n"; // 10
    cout << tree->problem1(20) << "\n"; // -1234
    cout << tree->problem1(10) << "\n"; // 14
    cout << tree->problem1(8) << "\n"; // 9
}

int main()
{
    test_cases();
    cout << "\n\nNO RTE\n";
    return 0;
}
