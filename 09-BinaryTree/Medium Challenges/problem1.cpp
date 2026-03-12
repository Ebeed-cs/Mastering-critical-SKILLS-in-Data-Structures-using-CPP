#include <iostream>
#include <cassert>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <algorithm>
#include <sstream>
using namespace std;

class BinaryTree {
private:
    int data{ };
    BinaryTree* left{ };
    BinaryTree* right{ };

public:
    BinaryTree(int data) :
        data(data) {
    }

    void add(vector<int> values, vector<char> direction) {
        assert(values.size() == direction.size());
        BinaryTree* current = this;
        for (int i = 0; i < (int)values.size(); ++i) {
            if (direction[i] == 'L') {
                if (!current->left)
                    current->left = new BinaryTree(values[i]);
                else
                    assert(current->left->data == values[i]);
                current = current->left;
            }
            else {
                if (!current->right)
                    current->right = new BinaryTree(values[i]);
                else
                    assert(current->right->data == values[i]);
                current = current->right;
            }
        }
    }

    void print_inorder() {
        if (left)
            left->print_inorder();
        cout << data << " ";
        if (right)
            right->print_inorder();
    }

    void problem1() { // we can't call on the childrens 
        if (left) {
            left->problem1();
            delete left;
            left = nullptr;
        }
        if (right) {
            right->problem1();
            delete right;
            right = nullptr;
        }
    }

    ~BinaryTree() {
        problem1();
    }
};


int main() {
    BinaryTree binaryTree(1);
    binaryTree.add({ 2 , 4 }, { 'L' , 'L' });
    binaryTree.add({ 2 , 5 }, { 'L' , 'R' });
    binaryTree.add({ 3 , 7 }, { 'R' , 'R' });
    binaryTree.add({ 3 , 6 }, { 'R' , 'L' });

    binaryTree.print_inorder();
    binaryTree.problem1();
    binaryTree.print_inorder();

    cout << "\n\nNO RTE\n";
    return 0;
}
