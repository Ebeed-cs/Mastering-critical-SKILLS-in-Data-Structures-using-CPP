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

    vector<int> next_greater_idx(deque<int> v) {
        stack<int> temp;
        vector<int> result(v.size());
        int i = 0;
        for (; i < (int)v.size(); ++i) {
            while (!temp.empty() && v[temp.top()] < v[i]) {
                result[temp.top()] = i;
                temp.pop();
            }
            temp.push(i);
        }
        while (!temp.empty()) {
            result[temp.top()] = i; // not found => vector length
            temp.pop();
        }
        return result;
    }

    BinarySearchTree(deque<int>& preorder, vector<int> greater_idx = {}, int start = 0, int end = -1) {
        if (end == -1) {
            end = (int)preorder.size() - 1;
            greater_idx = next_greater_idx(preorder);
        }
        data = preorder[start];
        int split = greater_idx[start];
        if (start + 1 <= split - 1)
            left = new BinarySearchTree(preorder, greater_idx, start + 1, split - 1);
        if (split <= end)
            right = new BinarySearchTree(preorder, greater_idx, split, end);
    }
};


void test_case1()
{
    deque<int> preorder{ 50, 20, 15, 45, 35, 60, 70, 73 };
    BinarySearchTree tree(preorder);
    tree.print_inorder(); // 15 , 20 , 35 , 45 , 50 , 60 , 70 , 73
    cout << "\n";
}

void test_case2()
{
    deque<int> preorder{ 15, 12, 9 };
    BinarySearchTree tree(preorder);
    tree.print_inorder(); //  9 , 12 , 15
    cout << "\n";
}

void test_case3()
{
    deque<int> preorder{ 12, 19, 20 };
    BinarySearchTree tree(preorder);
    tree.print_inorder(); //  12 , 19 , 20
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
