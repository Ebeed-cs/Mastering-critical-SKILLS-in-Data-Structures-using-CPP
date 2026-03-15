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

    void problem2() {
        std::stack <std::pair<BinaryTree*, bool>> nodes;
        nodes.push(make_pair(this, false));

        while (!nodes.empty()) {
            BinaryTree* cur = nodes.top().first;
            bool is_done = nodes.top().second;

            nodes.pop();

            if (is_done)
                std::cout << cur->data << " ";
            else {
                if (cur->right)
                    nodes.push(make_pair(cur->right, false));

                nodes.push(make_pair(cur, true));

                if (cur->left)
                    nodes.push(make_pair(cur->left, false));
            }
        }
    }

    void clear() { // we can't call on the childrens 
        if (left) {
            left->clear();
            delete left;
            left = nullptr;
        }
        if (right) {
            right->clear();
            delete right;
            right = nullptr;
        }
    }

    ~BinaryTree() {
        clear();
    }
};


int main() {
    BinaryTree binaryTree(1);
    binaryTree.add({ 2 , 4 }, { 'L' , 'L' });
    binaryTree.add({ 2 , 5 }, { 'L' , 'R' });
    binaryTree.add({ 3 , 7 }, { 'R' , 'R' });
    binaryTree.add({ 3 , 6 }, { 'R' , 'L' });

    binaryTree.problem2();
    binaryTree.clear();
    binaryTree.problem2();

    cout << "\n\nNO RTE\n";
    return 0;
}
