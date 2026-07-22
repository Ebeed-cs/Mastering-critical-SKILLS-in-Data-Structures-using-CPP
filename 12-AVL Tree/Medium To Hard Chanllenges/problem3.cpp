#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
using namespace std;

class AVLTree {
private:
    struct BinaryNode {
        int data{ };
        int height{ };
        int count{ 1 };
        BinaryNode* left{ };
        BinaryNode* right{ };

        BinaryNode(int data) :
            data(data) {
        }

        int ch_height(BinaryNode* node) {	// child height
            if (!node)
                return -1;			// -1 for null
            return node->height;	// 0 for leaf
        }
        int ch_count(BinaryNode* node) {
            if (!node)
                return 0;
            return node->count;
        }
        int update_height() {	// call in end of insert function
            return height = 1 + max(ch_height(left), ch_height(right));
        }
        int update_count() {
            return count = 1 + max(ch_count(left), ch_count(right));
        }
        void update() {
            update_height();
            update_count();
        }
        int balance_factor() {
            return ch_height(left) - ch_height(right);
        }
    };

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

    BinaryNode* insert_node(int target, BinaryNode* node) {
        if (target < node->data) {
            if (!node->left)
                node->left = new BinaryNode(target);
            else
                // change left. update left as it might be balanced
                node->left = insert_node(target, node->left);
        }
        else if (target > node->data) {
            if (!node->right)
                node->right = new BinaryNode(target);
            else
                node->right = insert_node(target, node->right);
        }
        node->update();
        return balance(node);
    }

    int problem3(int target, BinaryNode* node) {
        if (!node) return 0;
        if (target < node->data) {
            int sum = 1;
            if (node->right)
                sum += node->right->count;
            return sum + problem3(target, node->left);
        }
        return problem3(target, node->right);
    }
public:
    void insert_value(int target) {
        if (!root)
            root = new BinaryNode(target);
        else
            root = insert_node(target, root);
    }

    int count_inversions(vector<int>& v) {
        for (int i = 0; i < v.size(); ++i) {
            insert_value(v[i]);
            problem3(v[i], root);
        }
    }

};

int main() {

    cout << "bye\n";

    return 0;
}

