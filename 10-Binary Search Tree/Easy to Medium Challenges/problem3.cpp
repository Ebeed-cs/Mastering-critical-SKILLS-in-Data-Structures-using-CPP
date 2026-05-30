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
};

BinarySearchTree *problem3(vector<int> &values)
{
    vector<int> right_sub;
    int md = values.size() / 2;
    md -= (values.size() % 2 == 0);
    for (int i = 0; i < md; ++i)
    {
        right_sub.push_back(values.back());
        values.pop_back();
    }
    reverse(right_sub.begin(), right_sub.end());
    int cur_data = values.back();
    values.pop_back();
    BinarySearchTree *cur = new BinarySearchTree(cur_data);

    if (values.size())
        cur->left = problem3(values);
    if (right_sub.size())
        cur->right = problem3(right_sub);
    return cur;
}

void test_case1()
{
    vector<int> values{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    BinarySearchTree *tree = problem3(values);
    tree->print_inorder();
    cout << "\n";
}

void test_case2()
{
    vector<int> values{0, 1, 2, 3, 4, 5, 6, 7, 8};
    BinarySearchTree *tree = problem3(values);
    tree->print_inorder();
    std::cout << "\n";
}

void test_case3()
{
    vector<int> values{-18, -5, -3, 0, 6, 18};
    BinarySearchTree *tree = problem3(values);
    tree->print_inorder();
}

int main()
{
    test_case1();
    test_case2();
    test_case3();
    cout << "\n\nNO RTE\n";
    return 0;
}
