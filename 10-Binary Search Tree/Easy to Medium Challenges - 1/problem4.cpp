#include <iostream>
#include <cassert>
#include <vector>
#include <queue>
#include <climits>
#include <stack>
#include <algorithm>
using namespace std;

class BinarySearchTree {
private:
    int data{ };

public:
    BinarySearchTree* left{ };
    BinarySearchTree* right{ };

    BinarySearchTree(int data, BinarySearchTree* left = nullptr, BinarySearchTree* right = nullptr) :
        data(data), left(left), right(right) {
    }

    void print_inorder() {
        if (left)
            left->print_inorder();
        cout << data << " ";
        if (right)
            right->print_inorder();
    }

    void insert(int target) {
        if (target < data) {
            if (!left) {
                left = new BinarySearchTree(target);
            }
            else
                left->insert(target);
        }
        else if (target > data) {
            if (!right)
                right = new BinarySearchTree(target);
            else
                right->insert(target);
        } // else: exists already
    }

    int problem4(int& k) {
        if (k == 0)
            return -1234;

        if (left) {
            int res = left->problem4(k);
            if (k == 0)
                return res;
        }

        --k;	// for current node
        if (k == 0)
            return data;

        if (right)
            return right->problem4(k);

        return -1234;
    }
};



void test_case1()
{
    BinarySearchTree* tree = new BinarySearchTree(80);
    tree->insert(60);
    tree->insert(20);
    tree->insert(5);
    tree->insert(30);
    tree->insert(70);

    tree->insert(85);
    tree->insert(87);
    tree->insert(90);

    int k = 3;

    cout << tree->problem4(k) << "\n"; // 30
}

void test_case2()
{
    BinarySearchTree* tree = new BinarySearchTree(80);
    tree->insert(60);
    tree->insert(20);
    tree->insert(5);
    tree->insert(30);
    tree->insert(70);

    tree->insert(85);
    tree->insert(87);
    tree->insert(90);

    int k = 0;

    cout << tree->problem4(k) << "\n"; // -1234
}

void test_case3()
{
    BinarySearchTree* tree = new BinarySearchTree(80);
    tree->insert(60);
    tree->insert(20);
    tree->insert(5);
    tree->insert(30);
    tree->insert(70);

    tree->insert(85);
    tree->insert(87);
    tree->insert(90);

    int k = 15;

    cout << tree->problem4(k) << "\n"; // -1234
}

int main()
{
    test_case1();
    test_case2();
    test_case3();
    cout << "\n\nNO RTE\n";
    return 0;
}
