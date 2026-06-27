#include <iostream>
#include <cassert>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

class BinarySearchTree {
private:
    struct BinaryNode {
        int data{};
        BinaryNode* left{};
        BinaryNode* right{};
        BinaryNode(int data) :
            data(data) {
        }
    }

    BinaryNode* root{};


    void special_delete(BinarySearchTree* child) {
        data = child->data;
        left = child->left;
        right = child->right;
        delete child;
    }
public:
    BinarySearchTree() {}

    void get_inorder(vector<int>& values) {
        if (left)
            left->get_inorder(values);
        values.push_back(data);
        if (right)
            right->get_inorder(values);
    }
    ////////////////////////////////////////////

    void insert_value(int target) {
        if (!root) {
            root = new BinaryNode(target);
            return;
        }
        BinaryNode* cur = root;
        while (true) {
            if (target > cur->data) {
                if (cur->right)
                    cur = cur->right;
                else {
                    cur->right = new BinaryNode(target);
                    return;
                }
            }
            else if (target < cur->data) {
                if (cur->left)
                    cur = cur->left;
                else {
                    cur->left = new BinaryNode(target);
                    return;
                }
            }
            else
                return; // already found
        }
    }
    void print_inorder(BinaryNode* cur = root) {
        if (!cur) return;
        cur->print_inorder(cur->left);
        cout << cur->data << " ";
        cur->print_inorder(cur->right);
    }

    bool search(int target) {
        if (!root) return false;
        if (target < root->data)
            return root->left && root->left->search(target);
        else if (target > root->data)
            return root->right && root->right->search(target);
        return true;
    }

    void level_order_traverse() {
        if (!root) return;
        vector<BinaryNode*> nodes = root;
        while (!nodes.empty())
        {
            int sz = (int)nodes.size();
            while (sz-- > 0) {
                BinaryNode* cur = nodes.front();
                nodes.pop_front();
                if (cur->left) nodes.push_back(cur->left);
                if (cur->right) nodes.push_back(cur->right);
                cout << cur->data << " ";
            }
            cout << "\n";
        }
    }

    void delete_value(int target) {}

    int main() {

        cout << "bye\n";

        return 0;
    }

