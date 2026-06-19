#include <iostream>
#include <cassert>
#include <vector>
#include <queue>
#include <climits>
#include <tuple>
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
            if (!left)
                left = new BinarySearchTree(target);
            else
                left->insert(target);
        }
        else if (target > data) {
            if (!right)
                right = new BinarySearchTree(target);
            else
                right->insert(target);
        }
    }

    BinarySearchTree(deque<int> level_order, int min = 0, int max = 1001) {
        data = level_order.front();
        level_order.pop_front();

        // queue of nodes still waiting to be checked for children, each with its own bounds
        queue<tuple<BinarySearchTree*, int, int>> pending;
        pending.push({ this, min, max });

        while (!level_order.empty() && !pending.empty()) {
            auto [node, node_min, node_max] = pending.front();
            pending.pop();

            if (!level_order.empty() && level_order.front() > node_min && level_order.front() < node->data) {
                node->left = new BinarySearchTree(level_order.front());
                level_order.pop_front();
                pending.push({ node->left, node_min, node->data });
            }

            if (!level_order.empty() && level_order.front() > node->data && level_order.front() < node_max) {
                node->right = new BinarySearchTree(level_order.front());
                level_order.pop_front();
                pending.push({ node->right, node->data, node_max });
            }
        }
    }
};

void test_case1()
{
    deque<int> level_order{ 50, 20, 60, 15, 45, 70, 35, 73 };
    BinarySearchTree tree(level_order);
    tree.print_inorder(); // 15 20 35 45 50 60 70 73
    cout << "\n";
}

void test_case2()
{
    deque<int> level_order{ 15, 12, 9 };
    BinarySearchTree tree(level_order);
    tree.print_inorder(); // 9 12 15
    cout << "\n";
}

void test_case3()
{
    deque<int> level_order{ 12, 19, 20 };
    BinarySearchTree tree(level_order);
    tree.print_inorder(); // 12 19 20
    cout << "\n";
}

int main()
{
    test_case1();
    test_case2();
    test_case3();
    cout << "\n\nNO RTE\n";
    return 0;
}
