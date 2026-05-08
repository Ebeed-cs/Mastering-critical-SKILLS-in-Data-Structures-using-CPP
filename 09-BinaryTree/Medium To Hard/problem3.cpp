
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

    bool problem3() {
        queue<BinaryTree*> nodes_queue;
        nodes_queue.push(this);

        bool no_more_allowed = false;


        while (!nodes_queue.empty()) {
            int sz = nodes_queue.size();

            while (sz--) {
                BinaryTree* cur = nodes_queue.front();
                nodes_queue.pop();

                if (cur->left) {
                    if (no_more_allowed)
                        return false;
                    nodes_queue.push(cur->left);
                }
                else
                    no_more_allowed = true;

                if (cur->right) {
                    if (no_more_allowed)
                        return false;
                    nodes_queue.push(cur->right);
                }
                else
                    no_more_allowed = true;
            }
        }
        return true;
    }
};

int main()
{
    BinaryTree tree(1);

    tree.add({ 2, 4, 8 }, { 'L', 'L', 'L' });
    tree.add({ 2, 4, 9 }, { 'L', 'L', 'R' });
    tree.add({ 2, 5, 10 }, { 'L', 'R', 'L' });
    tree.add({ 2, 5, 11 }, { 'L', 'R', 'R' });

    tree.add({ 3, 6, 12 }, { 'R', 'L', 'L' });
    tree.add({ 3, 6, 13 }, { 'R', 'L', 'R' });
    tree.add({ 3, 7, 14 }, { 'R', 'R', 'L' });
    tree.add({ 3, 7, 15 }, { 'R', 'R', 'R' });

    std::cout << tree.problem3() << "\n";

    cout << "\n\nNO RTE\n";
    return 0;
}

