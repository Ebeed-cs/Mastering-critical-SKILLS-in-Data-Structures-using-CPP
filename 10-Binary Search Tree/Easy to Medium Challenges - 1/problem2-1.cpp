
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

    int min_tree() {
        if (left)
            return left->min_tree();
        return data;
    }

    int max_tree() {
        if (right)
            return right->max_tree();
        return data;
    }

    bool problem2(int min_num = -1, int max_num = -1, bool updated = false) {
        if (!updated) {
            min_num = min_tree();
            max_num = max_tree();
            updated = true;
        }
        if (!left && !right)
            return true;
        if (left && !left->problem2(min_num, max_num, updated))
            return false;
        if (left && !(min_num <= left->data && max_num >= left->data))
            return false;
        if (right && !right->problem2(min_num, max_num, updated))
            return false;
        if (right && !(min_num <= right->data && max_num >= right->data))
            return false;
        return true;
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
