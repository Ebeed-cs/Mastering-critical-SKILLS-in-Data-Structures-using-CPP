#include <iostream>
#include <cassert>
#include <vector>
#include <queue>
#include <climits>
#include <stack>
#include <algorithm>
using namespace std;

class BinarySearchTree
{
private:
    int data{};

public:
    BinarySearchTree *left{};
    BinarySearchTree *right{};

    BinarySearchTree(int data, BinarySearchTree *left = nullptr, BinarySearchTree *right = nullptr) : data(data), left(left), right(right)
    {
    }

    void print_inorder()
    {
        if (left)
            left->print_inorder();
        cout << data << " ";
        if (right)
            right->print_inorder();
    }

    void insert(int target)
    {
        if (target < data)
        {
            if (!left)
                left = new BinarySearchTree(target);
            else
                left->insert(target);
        }
        else if (target > data)
        {
            if (!right)
                right = new BinarySearchTree(target);
            else
                right->insert(target);
        }
    }

    BinarySearchTree(deque<int> &preorder, int min = 0, int max = 1001)
    {
        data = preorder[0];
        preorder.pop_front();
        if (!preorder.empty() && preorder[0] > min &&
            preorder[0] < data)
            left = new BinarySearchTree(preorder, min, data);
        if (!preorder.empty() && preorder[0] < max &&
            preorder[0] > data)
            right = new BinarySearchTree(preorder, data, max);
    }
};

void test_case1()
{
    deque<int> preorder{50, 20, 15, 45, 35, 60, 70, 73};
    BinarySearchTree tree(preorder);
    tree.print_inorder(); // 15 , 20 , 35 , 45 , 50 , 60 , 70 , 73
    cout << "\n";
}

void test_case2()
{
    deque<int> preorder{15, 12, 9};
    BinarySearchTree tree(preorder);
    tree.print_inorder(); //  9 , 12 , 15
    cout << "\n";
}

void test_case3()
{
    deque<int> preorder{12, 19, 20};
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
