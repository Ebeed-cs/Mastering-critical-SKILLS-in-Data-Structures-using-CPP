
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

public:
    BinaryTree* left{};
    BinaryTree* right{};

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

};

bool problem2(BinaryTree* a, BinaryTree* b) {
    if (!a && !b) return true;
    if (!a || !b) return false;
    if (a->data != b->data) return false;

    return (problem2(a->left, b->left) && problem2(a->right, b->right)) ||
        (problem2(a->left, b->right) && problem2(a->right, b->left));
}

void test_case1()
{
    BinaryTree tree1(1);
    tree1.add({ 3, 6 }, { 'R' , 'L' });
    tree1.add({ 2, 5 , 8 }, { 'L' , 'R' , 'R' });
    tree1.add({ 2, 4 }, { 'L' , 'L' });
    tree1.add({ 2, 5 , 8 }, { 'L' , 'R' , 'R' });
    tree1.add({ 2, 5 , 7 }, { 'L' , 'R' , 'L' });

    BinaryTree tree2(1);
    tree2.add({ 3, 6 }, { 'L' , 'R' });
    tree2.add({ 2, 4 }, { 'R' , 'L' });
    tree2.add({ 2, 5 , 8 }, { 'R' , 'R' , 'L' });
    tree2.add({ 2, 5 , 7 }, { 'R' , 'R' , 'R' });

    std::cout << problem2(&tree1, &tree2) << "\n";

}

int main()
{

    test_case1();

    cout << "\n\nNO RTE\n";
    return 0;
}

