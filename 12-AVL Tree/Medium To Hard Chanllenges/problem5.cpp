#include <iostream>
#include <cassert>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct BinaryNode {
    queue<int> values;
    int key{};
    int height{ };
    BinaryNode* left{ };
    BinaryNode* right{ };

    BinaryNode(int val, int k) {
        key = k;
        values.push(val);
    }

    int ch_height(BinaryNode* node) {	// child height
        if (!node)
            return -1;			// -1 for null
        return node->height;	// 0 for leaf
    }
    int update_height() {	// call in end of insert function
        return height = 1 + max(ch_height(left), ch_height(right));
    }
    int balance_factor() {
        return ch_height(left) - ch_height(right);
    }

    void add_val(int val) {
        values.push(val);
    }

};

class AVLTree {
private:
    BinaryNode* root{ };

    ///////////////////////////
    BinaryNode* right_rotation(BinaryNode* Q) {
        BinaryNode* P = Q->left;
        Q->left = P->right;
        P->right = Q;
        Q->update_height();
        P->update_height();
        return P;
    }

    BinaryNode* left_rotation(BinaryNode* P) {
        BinaryNode* Q = P->right;
        P->right = Q->left;
        Q->left = P;
        P->update_height();
        Q->update_height();
        return Q;
    }

    BinaryNode* balance(BinaryNode* node) {
        if (node->balance_factor() == 2) { 			// Left
            if (node->left->balance_factor() == -1)	// Left Right?
                node->left = left_rotation(node->left);	// To Left Left

            node = right_rotation(node);	// Balance Left Left
        }
        else if (node->balance_factor() == -2) {
            if (node->right->balance_factor() == 1)
                node->right = right_rotation(node->right);

            node = left_rotation(node);
        }
        return node;
    }

    BinaryNode* insert_node(int val, int k, BinaryNode* node) {
        if (k < node->key) {
            if (!node->left)
                node->left = new BinaryNode(val, k);
            else
                // change left. update left as it might be balanced
                node->left = insert_node(val, k, node->left);
        }
        else if (k > node->key) {
            if (!node->right)
                node->right = new BinaryNode(val, k);
            else
                node->right = insert_node(val, k, node->right);
        }
        else
            node->add_val(val);

        node->update_height();
        return balance(node);
    }

    BinaryNode* min_node(BinaryNode* cur) {
        while (cur && cur->left)
            cur = cur->left;
        return cur;
    }

    BinaryNode* delete_node(int k, BinaryNode* node) {
        if (!node)
            return nullptr;

        if (k < node->key)
            node->left = delete_node(k, node->left);
        else if (k > node->key)
            node->right = delete_node(k, node->right);
        else {
            BinaryNode* tmp = node;

            if (!node->left && !node->right)	// case 1: no child
                node = nullptr;
            else if (!node->right) 	// case 2: has left only
                node = node->left;		// connect with child
            else if (!node->left)	// case 2: has right only
                node = node->right;
            else {	// 2 children: Use successor
                BinaryNode* mn = min_node(node->right);
                node->key = mn->key;
                node->values = mn->values;
                node->right = delete_node(node->key, node->right);
                tmp = nullptr;	// Don't delete me. Successor will be deleted
            }
            if (tmp)
                delete tmp;
        }
        if (node) {
            node->update_height();
            node = balance(node);
        }
        return node;
    }
public:
    void insert_value(int val, int k) {
        if (!root)
            root = new BinaryNode(val, k);
        else
            root = insert_node(val, k, root);
    }

    BinaryNode* max_tree()
    {
        BinaryNode* cur = root;

        while (cur && cur->right)
            cur = cur->right;

        return cur;
    }

    void delete_value(int k) {
        if (root) {
            root = delete_node(k, root);
        }
    }

    bool is_empty() {
        return root == nullptr;
    }

    int problem5(int height) {
        if (height == 0) return 1;
        if (height == 1) return 2;

        return problem5(height - 1) + problem5(height - 2) + 1;
    }

    int avl_nodes_iter(int height) {
        int first = 1;
        int second = 2;
        int temp = first;
        while (--height > 0) {
            first = second;
            second += temp + 1;
            temp = first;
        }
        return (height >= 0) ? second : first;
    }
};


int main() {
    AVLTree* tree = new AVLTree();
    for (int i = 0; i < 10; ++i)
        assert(tree->problem5(i) == tree->avl_nodes_iter(i));

    cout << "\n\nbye";
    return 0;
}

