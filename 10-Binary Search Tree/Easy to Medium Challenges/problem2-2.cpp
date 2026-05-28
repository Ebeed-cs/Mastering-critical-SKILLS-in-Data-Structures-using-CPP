
#include <iostream>
#include <cassert>
#include <vector>
#include <queue>
#include <map>
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

    bool problem2() {
        std::vector<int> vec;
        inorder_array(vec);
        int min_num = vec[0];
        int max_num = vec[vec.size() - 1];
        for (auto v : vec)
            if (!(v >= min_num && v <= max_num))
                return false;
        return true;
    }

    void print_inorder()
    {
        if (left)
            left->print_inorder();
        cout << data << " ";
        if (right)
            right->print_inorder();
    }

    void inorder_array(std::vector<int>& vec)
    {
        if (left)
            left->inorder_array(vec);
        vec.push_back(data);
        if (right)
            right->inorder_array(vec);
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
    BinaryTree tree1(50);
    tree1.add({ 40, 21 }, { 'L' , 'L' });
    tree1.add({ 40, 45 }, { 'L' , 'R' });
    tree1.add({ 60, 61 }, { 'R', 'R' });
    std::cout << tree1.problem2() << "\n"; // 1
}

void test_case2()
{
    BinaryTree tree1(50);

    std::cout << tree1.problem2() << "\n"; // 1
}

void test_case3()
{
    BinaryTree tree1(50);
    tree1.add({ 40, 70 }, { 'L' , 'L' });
    tree1.add({ 40, 45 }, { 'L' , 'R' });
    tree1.add({ 60, 61 }, { 'R', 'R' });
    std::cout << tree1.problem2() << "\n"; // 0
}

void test_case4()
{
    BinaryTree tree1(5);
    tree1.add({ 4 }, { 'L' });
    tree1.add({ 6 , 3 }, { 'R' , 'L' });
    tree1.add({ 6, 7 }, { 'R', 'R' });
    std::cout << tree1.problem2() << "\n"; // 0 
}

int main()
{
    test_case1();
    test_case2();
    test_case3();
    test_case4();

    cout << "\n\nNO RTE\n";
    return 0;
}
