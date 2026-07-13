#include<vector>
#include<queue>
#include<iostream>
#include<cassert>
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
        // iterate on the path, create all necessary nodes
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
    ////////////////////////////////////////////

    void level_order_traversal() {
        queue<BinaryTree*> nodes_queue;
        nodes_queue.push(this);

        while (!nodes_queue.empty()) {
            int sz = nodes_queue.size();

            while (sz--) {
                BinaryTree* cur = nodes_queue.front();
                nodes_queue.pop();

                cout << cur->data << " ";
                if (cur->left)
                    nodes_queue.push(cur->left);
                if (cur->right)
                    nodes_queue.push(cur->right);
            }
            cout << "\n";
        }
    }

    void problem3() {
        priority_queue<int> heap; // max heeap built in
        queue<BinaryTree*> nodes_queue;
        nodes_queue.push(this);
        while (!nodes_queue.empty()) {
            int sz = nodes_queue.size();
            while (sz--) {
                BinaryTree* cur = nodes_queue.front();
                nodes_queue.pop();
                heap.push(cur->data);
                if (cur->left)
                    nodes_queue.push(cur->left);
                if (cur->right)
                    nodes_queue.push(cur->right);
            }
            while (!heap.empty()) {
                cout << heap.top() << " ";
                heap.pop();
            }
            cout << "\n";
        }
    }
};

void test() {
    BinaryTree tree(1);

    tree.add({ 2, 4, 7 }, { 'L', 'L', 'L' });
    tree.add({ 2, 4, 8 }, { 'L', 'L', 'R' });
    tree.add({ 2, 5, 9 }, { 'L', 'R', 'R' });
    tree.add({ 3, 6, 15 }, { 'R', 'R', 'L' });

    tree.add({ 2, 5, 13 }, { 'L', 'R', 'L' });
    tree.add({ 3, 6, 12 }, { 'R', 'R', 'R' });
    tree.add({ 3, 14, 15 }, { 'R', 'L', 'L' });
    tree.add({ 3, 14, 16 }, { 'R', 'L', 'R' });

    tree.level_order_traversal();
    tree.problem3();
}

int main() {
    test();


    return 0;

}


