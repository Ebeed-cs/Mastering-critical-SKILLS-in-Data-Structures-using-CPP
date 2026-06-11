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

    BinarySearchTree(int data, BinarySearchTree* left = nullptr, BinarySearchTree* right = nullptr) :
        data(data), left(left), right(right) {
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
                left = new BinarySearchTree(target);
            }
            else
                left->insert(target);
        }
        else if (target > data) {
            if (!right)
                right = new BinarySearchTree(target);
            else
                right->insert(target);
        } // else: exists already
    }

    ///////////////////////////////////
    int min_value() {
        BinarySearchTree* cur = this;
        while (cur && cur->left)
            cur = cur->left;
        return cur->data;
    }

    int problem2(int target, int* may_successor = nullptr) {
        if (target == data) {
            if (right)
                return right->min_value();
            return may_successor ? *may_successor : -1234; // if -1234 then it's the max and hasn't a successor
        }

        if (target < data) {
            if (!left)
                return -1234; // the target not found in the tree
            return left->problem2(target, &data);
        }
        else if (target > data) {
            if (!right)
                return -1234;
            return right->problem2(target, may_successor);
        }return -1234;
    }
};



void test_cases()
{
    BinarySearchTree* tree = new BinarySearchTree(50);
    tree->insert(20);
    tree->insert(15);
    tree->insert(45);
    tree->insert(16);
    tree->insert(35);
    tree->insert(36);

    tree->insert(60);
    tree->insert(58);
    tree->insert(70);
    tree->insert(73);
    tree->insert(75);

    cout << tree->problem2(15) << "\n"; // 16
    cout << tree->problem2(20) << "\n"; // 35
    cout << tree->problem2(58) << "\n"; // 60
    cout << tree->problem2(16) << "\n"; // 20
    cout << tree->problem2(75) << "\n"; // -1234
    cout << tree->problem2(90) << "\n"; // -1234
}

int main()
{
    test_cases();

    cout << "\n\nNO RTE\n";
    return 0;
}
