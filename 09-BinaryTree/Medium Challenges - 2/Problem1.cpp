
#include <iostream>
#include <cassert>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <algorithm>
#include <sstream>
using namespace std;

class BinaryTree
{
private:
    BinaryTree* left{};
    BinaryTree* right{};

public:
    int data{};
    BinaryTree(int data) : data(data) {}

    BinaryTree(std::deque<int>& preorder, std::deque<int>& inorder) {
        this->data = preorder.front();
        preorder.pop_front();
        std::deque<int> left_subtree;
        std::deque<int> right_subtree;

        while (this->data != inorder.front()) {
            left_subtree.push_back(inorder.front());
            inorder.pop_front();
        }

        if (left_subtree.size())
            left = new BinaryTree(preorder, left_subtree);

        while (this->data != inorder.back()) {
            right_subtree.push_front(inorder.back());
            inorder.pop_back();
        }
        if (right_subtree.size())
            right = new BinaryTree(preorder, right_subtree);
    }

    void add(vector<int> values, vector<char> direction)
    {
        assert(values.size() == direction.size());
        BinaryTree* current = this;
        for (int i = 0; i < (int)values.size(); ++i)
        {
            if (direction[i] == 'L')
            {
                if (!current->left)
                    current->left = new BinaryTree(values[i]);
                else
                    assert(current->left->data == values[i]);
                current = current->left;
            }
            else
            {
                if (!current->right)
                    current->right = new BinaryTree(values[i]);
                else
                    assert(current->right->data == values[i]);
                current = current->right;
            }
        }
    }

    void print_inorder()
    {
        if (left)
            left->print_inorder();
        cout << data << " ";
        if (right)
            right->print_inorder();
    }

    void print_preorder()
    {
        cout << data << " ";
        if (left)
            left->print_preorder();
        if (right)
            right->print_preorder();
    }

    void clear()
    {
        if (left)
        {
            left->clear();
            delete left;
            left = nullptr;
        }
        if (right)
        {
            right->clear();
            delete right;
            right = nullptr;
        }
    }

    ~BinaryTree()
    {
        clear();
    }
};

int main()
{
    std::deque<int> preorder = { 1 , 2, 4, 7 , 8 , 5 , 9 , 3, 6, 10 };
    std::deque<int> inorder = { 7 , 4, 8 , 2, 5 , 9 , 1, 3, 10 , 6 };
    BinaryTree tree(preorder, inorder);
    tree.print_preorder();

    cout << "\n\nNO RTE\n";
    return 0;
}

