
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

    int tree_height() {
        int res = 0;
        if (left)
            res = std::max(res, 1 + left->tree_height());
        if (right)
            res = std::max(res, 1 + right->tree_height());
        return res;
    }

    void problem1(int level) {
        if (level == 0)
            std::cout << data << " ";
        else if (level) {
            if (left)
                left->problem1(level - 1);
            if (right)
                right->problem1(level - 1);
        }
    }

    void print_level_order() {
        int h = tree_height();

        for (int i = 0; i <= h; ++i)
            problem1(i);
    }
};

void test1_level_order_traversal_spiral() {
    BinaryTree tree(1);

    tree.add({ 2, 4, 8 }, { 'L', 'L', 'L' });
    tree.add({ 2, 4, 9 }, { 'L', 'L', 'R' });
    tree.add({ 2, 5, 10 }, { 'L', 'R', 'L' });
    tree.add({ 2, 5, 11 }, { 'L', 'R', 'R' });

    tree.add({ 3, 6, 12 }, { 'R', 'L', 'L' });
    tree.add({ 3, 6, 13 }, { 'R', 'L', 'R' });
    tree.add({ 3, 7, 14 }, { 'R', 'R', 'L' });

    //tree.level_order_traversal_recursive();

    tree.print_level_order();
    // Level 0: 1
    // Level 1: 3 2
    // Level 2: 4 5 6 7
    // Level 3: 15 14 13 12 11 10 9 8
}
int main()
{
    test1_level_order_traversal_spiral();
    cout << "\n\nNO RTE\n";
    return 0;
}
