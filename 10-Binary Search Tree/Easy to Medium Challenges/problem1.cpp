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
    BinarySearchTree* left{ };
    BinarySearchTree* right{ };

public:

    BinarySearchTree(int data, BinarySearchTree* left = nullptr, BinarySearchTree* right = nullptr) :
        data(data), left(left), right(right) {
    }

    void get_inorder(vector<int>& values) {
        if (left)
            left->get_inorder(values);
        values.push_back(data);
        if (right)
            right->get_inorder(values);
    }

    void level_order_traversal2() {
        queue<BinarySearchTree*> nodes_queue;
        nodes_queue.push(this);

        int level = 0;
        while (!nodes_queue.empty()) {
            int sz = nodes_queue.size();

            cout << "Level " << level << ": ";
            while (sz--) {
                BinarySearchTree* cur = nodes_queue.front();
                nodes_queue.pop();

                cout << cur->data << " ";
                if (cur->left)
                    nodes_queue.push(cur->left);
                if (cur->right)
                    nodes_queue.push(cur->right);
            }
            level++;
            cout << "\n";
        }
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
    bool problem1(int target) {
        BinarySearchTree* cur = this;
        while (cur && cur->data != target)
            cur = (cur->data > target) ? cur->left : cur->right;
        return (cur != nullptr);
    }
};

void test_case1() {
    BinarySearchTree binary_tree(50);
    binary_tree.insert(40);
    binary_tree.insert(60);

    binary_tree.insert(21);
    binary_tree.insert(45);
    binary_tree.insert(61);

    std::cout << binary_tree.problem1(50) << "\n"; // 1
}

void test_case2() {
    BinarySearchTree binary_tree(50);
    binary_tree.insert(40);
    binary_tree.insert(60);

    binary_tree.insert(21);
    binary_tree.insert(45);
    binary_tree.insert(61);

    std::cout << binary_tree.problem1(45) << "\n"; // 1
}

void test_case3() {
    BinarySearchTree binary_tree(50);
    binary_tree.insert(40);
    binary_tree.insert(60);

    binary_tree.insert(21);
    binary_tree.insert(45);
    binary_tree.insert(61);

    std::cout << binary_tree.problem1(30) << "\n"; // 0
}

int main() {
    test_case1();
    test_case2();
    test_case3();
    return 0;
}
