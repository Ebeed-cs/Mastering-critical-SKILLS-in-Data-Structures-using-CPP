
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
    BinaryTree *left{};
    BinaryTree *right{};

public:
    int data{};
    BinaryTree(int data) : data(data) {}

    BinaryTree(std::deque<std::pair<int, bool>> &preorder_deque)
    {
        std::pair<int, bool> current = preorder_deque.front();
        preorder_deque.pop_front();

        data = current.first;
        if (current.second)
            return;

        left = new BinaryTree(preorder_deque);
        right = new BinaryTree(preorder_deque);
    }

    void build_deque_pair(std::deque<std::pair<int, bool>> &deq)
    {
        if (!left && !right)
        {
            deq.push_back(make_pair(data, true));
            return;
        }

        deq.push_back(make_pair(data, false));
        if (left)
            left->build_deque_pair(deq);
        if (right)
            right->build_deque_pair(deq);
    }

    void add(vector<int> values, vector<char> direction)
    {
        assert(values.size() == direction.size());
        BinaryTree *current = this;
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

void test_case1()
{
    BinaryTree tree(1);
    tree.add({2, 4}, {'L', 'L'});
    tree.add({2, 5}, {'L', 'R'});
    tree.add({3, 6}, {'R', 'L'});
    tree.add({3, 7}, {'R', 'R'});

    std::deque<std::pair<int, bool>> res;

    tree.build_deque_pair(res);

    // for (auto deq : res)
    //     std::cout << "( " << deq.first << " , " << deq.second << " )" << " , " << " ";
    BinaryTree create_tree(res);
    create_tree.print_inorder();
}

int main()
{
    test_case1();

    cout << "\n\nNO RTE\n";
    return 0;
}
