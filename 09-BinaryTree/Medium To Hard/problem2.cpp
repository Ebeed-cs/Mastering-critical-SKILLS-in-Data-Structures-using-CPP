
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

    void problem2() {

        deque<BinaryTree*> qu;
        qu.push_back(this);
        bool right_dir = false;
        int level = 0;

        while (!qu.empty()) {

            int size = qu.size();
            std::cout << level << " : ";
            while (size--) {
                if (right_dir) {

                    BinaryTree* cur = qu.back();
                    qu.pop_back();

                    cout << cur->data << " ";

                    if (cur->right)
                        qu.push_front(cur->right);

                    if (cur->left)
                        qu.push_front(cur->left);
                }
                else {

                    BinaryTree* cur = qu.front();
                    qu.pop_front();

                    cout << cur->data << " ";

                    if (cur->left)
                        qu.push_back(cur->left);

                    if (cur->right)
                        qu.push_back(cur->right);
                }
            }
            right_dir = !right_dir;
            level++;
            std::cout << "\n";
        }
    }
};

void test1_problem2() {
    BinaryTree tree(1);

    tree.add({ 2, 4, 8 }, { 'L', 'L', 'L' });
    tree.add({ 2, 4, 9 }, { 'L', 'L', 'R' });
    tree.add({ 2, 5, 10 }, { 'L', 'R', 'L' });
    tree.add({ 2, 5, 11 }, { 'L', 'R', 'R' });

    tree.add({ 3, 6, 12 }, { 'R', 'L', 'L' });
    tree.add({ 3, 6, 13 }, { 'R', 'L', 'R' });
    tree.add({ 3, 7, 14 }, { 'R', 'R', 'L' });

    //tree.level_order_traversal_recursive();

    tree.problem2();
    // Level 0: 1
    // Level 1: 3 2
    // Level 2: 4 5 6 7
    // Level 3: 14 13 12 11 10 9 8
}
int main()
{
    test1_problem2();
    cout << "\n\nNO RTE\n";
    return 0;
}
