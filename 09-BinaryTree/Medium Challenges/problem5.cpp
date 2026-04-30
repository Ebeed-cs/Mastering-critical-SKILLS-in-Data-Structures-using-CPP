
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

    char last_one(string& str)
    {
        if (str.empty())
            return '%';
        char c = str[str.size() - 1];
        str = str.substr(0, str.size() - 1);
        return c;
    }

public:
    char data{};
    BinaryTree(char data) : data(data) {}

    BinaryTree(string postfix)
    {
        std::stack<BinaryTree*> tree;
        for (int i = 0; i < postfix.size(); ++i) {
            BinaryTree* cur = new BinaryTree(postfix[i]);

            if (!isdigit(postfix[i])) {
                cur->right = tree.top();
                tree.pop();
                cur->left = tree.top();
                tree.pop();
            }
            tree.push(cur);
        }
        BinaryTree* root = tree.top();
        this->data = root->data;
        this->right = root->right;
        this->left = root->left;
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

    void print_postorder()
    {
        if (left)
            left->print_postorder();
        if (right)
            right->print_postorder();
        cout << data << " ";
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

    int tree_height()
    {
        int res = 0;
        if (left)
            res = 1 + left->tree_height();
        if (right)
            res = std::max(1 + right->tree_height(), res);
        return res;
    }
};
int main()
{
    BinaryTree root("523*+");
    root.print_postorder();
    cout << "\n\nNO RTE\n";
    return 0;
}
