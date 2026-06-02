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

    bool search(int target) {
        if (data == target)   return true;
        if (target < data)    return left && left->search(target);
        return right && right->search(target);
    }

    int problem5(int x, int y) {
        int res = -1234;
        if (left && ((res = left->problem5(x, y)) != -1234))
            return res;
        if (right && ((res = right->problem5(x, y)) != -1234))
            return res;
        if (left && right)
            if (search(x) && search(y))
                return data;
        return res;
    }
};



void test_cases()
{
    BinarySearchTree* tree = new BinarySearchTree(50);
    tree->insert(20);
    tree->insert(15);
    tree->insert(16);
    tree->insert(45);
    tree->insert(35);
    tree->insert(36);

    tree->insert(60);
    tree->insert(58);
    tree->insert(70);
    tree->insert(73);
    tree->insert(75);

    cout << tree->problem5(15, 45) << "\n"; // 20
    cout << tree->problem5(45, 15) << "\n"; // 20
    cout << tree->problem5(58, 70) << "\n"; // 60
    cout << tree->problem5(15, 70) << "\n"; // 50
    cout << tree->problem5(20, 45) << "\n"; // 20
    cout << tree->problem5(45, 20) << "\n"; // 20
    cout << tree->problem5(20, 50) << "\n"; // 50
    cout << tree->problem5(15, 60) << "\n"; // 50
    cout << tree->problem5(15, 70) << "\n"; // 50

    //2 failing cases
    cout << tree->problem5(45, 36) << "\n"; // 45  (returns 20)
    cout << tree->problem5(70, 75) << "\n"; // 70  (returns 60)
}

int main()
{
    test_cases(); // HAS 2 BUGS
    cout << "\n\nNO RTE\n";
    return 0;
}
