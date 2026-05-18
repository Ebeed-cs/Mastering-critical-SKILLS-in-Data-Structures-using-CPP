
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

    string parenthesize(vector<string>& all_repres)
    {
        // save the representation of every subtree
        string repr = "(" + to_string(data);

        if (left)
            repr += left->parenthesize(all_repres);
        else
            repr += "()";

        if (right)
            repr += right->parenthesize(all_repres);
        else
            repr += "()";

        repr += ")";

        if (left || right) // nodes > 1
            all_repres.push_back(repr);

        return repr;
    }

    void problem3()
    {
        std::map<std::string, int> freq;
        std::vector<std::string> repts;
        parenthesize(repts);
        for (auto r : repts)
            freq[r]++;
        for (auto p : freq) {
            if (p.second > 1)
                std::cout << p.first << " ";
        }
        std::cout << "\n";
    }

    ~BinaryTree()
    {
        clear();
    }

};

void test_case1()
{
    BinaryTree tree1(1);
    tree1.add({ 2, 3 }, { 'L' , 'L' });
    tree1.add({ 2, 4 }, { 'L' , 'R' });
    tree1.add({ 5, 9 , 2, 3 }, { 'R' , 'L' , 'L' , 'L' });
    tree1.add({ 5, 9 , 2, 4 }, { 'R' , 'L' , 'L' , 'R' });
    tree1.add({ 5,9 }, { 'R' , 'R' });

    tree1.problem3();

}

void test_case2()
{
    BinaryTree tree(1);
    tree.add({ 2 , 3 }, { 'L' , 'L' });
    tree.add({ 2 , 4 }, { 'L' , 'R' });
    tree.add({ 2 , 3 }, { 'R' , 'L' });
    tree.add({ 2 , 4 }, { 'R' , 'R' });

    tree.problem3();

}

void test_case3()
{
    BinaryTree tree(1);
    tree.add({ 2 , 4 }, { 'L' , 'L' });
    tree.add({ 3 , 4 }, { 'R' , 'L' });

    tree.problem3();
}

void test_case4()
{
    BinaryTree tree(1);
    tree.add({ 2 , 3 , 8 }, { 'L' , 'L', 'R' });
    tree.add({ 2 , 3 , 8 }, { 'R' , 'L', 'R' });

    tree.problem3();
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
