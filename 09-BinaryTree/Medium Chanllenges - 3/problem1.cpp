
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

    string parenthesize_normal() {
        string repr = "(" + to_string(data);

        if (left)
            repr += left->parenthesize_normal();
        else
            repr += "()";	// null: no child

        if (right)
            repr += right->parenthesize_normal();
        else
            repr += "()";	// null: no child
        repr += ")";

        return repr;
    }

    string parenthesize_reversed() {
        string repr = "(" + to_string(data);

        vector<string> v;

        if (left)
            v.push_back(left->parenthesize_reversed());
        else
            v.push_back("()");

        if (right)
            v.push_back(right->parenthesize_reversed());
        else
            v.push_back("()");

        reverse(v.begin(), v.end());

        for (auto value : v)
            repr += value;

        repr += ")";

        return repr;
    }

    bool is_symmatric_paranthesize() {
        if (!left && !right)  return true;
        if (!left || !right) return false;
        return (left->parenthesize_normal() == right->parenthesize_reversed());
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

    bool is_mirror(BinaryTree* first, BinaryTree* second) {
        if (!left && !right)  return true;

        if ((!first && second) ||
            (!second && first) ||
            (first->data != second->data))
            return false;

        if (first->left || second->right)
            if (!is_mirror(first->left, second->right))
                return false;
        if (first->right || second->left)
            if (!is_mirror(first->right, second->left))
                return false;
        return true;
    }

    bool is_symmatric() {
        return is_mirror(left, right);
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
    tree.add({ 2 }, { 'L' });

    std::cout << tree.is_symmatric() << "\n";
    std::cout << tree.is_symmatric_paranthesize() << "\n";
}

void test_case2()
{
    BinaryTree tree(1);
    tree.add({ 2 }, { 'R' });

    std::cout << tree.is_symmatric() << "\n";
    std::cout << tree.is_symmatric_paranthesize() << "\n";
}

void test_case3()
{
    BinaryTree tree(1);
    tree.add({ 2 }, { 'L' });
    tree.add({ 3 }, { 'R' });

    std::cout << tree.is_symmatric() << "\n";
    std::cout << tree.is_symmatric_paranthesize() << "\n";
}

void test_case4()
{
    BinaryTree tree(1);
    tree.add({ 2 , 3 , 5 }, { 'L' , 'L', 'L' });
    tree.add({ 2 , 3 , 6 }, { 'L' , 'L', 'R' });
    tree.add({ 2 , 4 , 7 }, { 'L' , 'R', 'L' });
    tree.add({ 2 , 4 , 8 }, { 'L' , 'R', 'R' });

    tree.add({ 2 , 4 , 8 }, { 'R' , 'L', 'L' });
    tree.add({ 2 , 4 , 7 }, { 'R' , 'L', 'R' });
    tree.add({ 2 , 3 , 6 }, { 'R' , 'R', 'L' });
    tree.add({ 2 , 3 , 5 }, { 'R' , 'R', 'R' });

    std::cout << tree.is_symmatric() << "\n";
    std::cout << tree.is_symmatric_paranthesize() << "\n";
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

