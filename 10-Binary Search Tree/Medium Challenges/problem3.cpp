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
};


bool problem3(vector<int>& preorder) {
    if (preorder.size() <= 2)
        return true;

    int mn = 1, mx = 1000;

    for (int i = 1; i < (int)preorder.size(); ++i)
    {
        if (preorder[i] < mn || preorder[i] > mx)
            return false;
        if (preorder[i] > preorder[i - 1])
            mn = preorder[i - 1] + 1;
        else
            mx = preorder[i - 1] - 1;
    }
    return true;
}

void test_case1()
{
    vector<int> preorder{ 25, 8, 11, 13, 12 };
    bool my_result = problem3(preorder);
    bool expected_result = true;
    assert(my_result == expected_result);
    cout << "passed \n";
}

void test_case2()
{
    vector<int> preorder{ 100, 70, 101 };
    bool my_result = problem3(preorder);
    bool expected_result = false;
    assert(my_result == expected_result);
    cout << "passed \n";
}

void test_case3()
{
    vector<int> preorder{ 100, 70, 60, 75 };
    bool my_result = problem3(preorder);
    bool expected_result = false;
    assert(my_result == expected_result);
    cout << "passed \n";
}

void test_case4()
{
    vector<int> preorder{ 100, 70, 60, 65 };
    bool my_result = problem3(preorder);
    bool expected_result = true;
    assert(my_result == expected_result);
    cout << "passed \n";
}

void test_case5()
{
    vector<int> preorder{ 9, 8, 7, 6, 5, 4, 3 };
    bool my_result = problem3(preorder);
    bool expected_result = true;
    assert(my_result == expected_result);
    cout << "passed \n";
}

void test_case6()
{
    vector<int> preorder{ 500, 400, 300, 200 , 250 , 275, 260 };
    bool my_result = problem3(preorder);
    bool expected_result = true;
    assert(my_result == expected_result);
    cout << "passed \n";
}

void test_case7()
{
    vector<int> preorder{ 500, 400, 300, 200 , 250 , 275, 260, 280 };
    bool my_result = problem3(preorder);
    bool expected_result = false;
    assert(my_result == expected_result);
    cout << "passed \n";
}

void test_case8()
{
    vector<int> preorder{ 10 , 5 , 3, 1 , 4, 2 };
    bool my_result = problem3(preorder);
    bool expected_result = false;
    assert(my_result == expected_result);
    cout << "passed \n";
}

void test_case9()
{
    vector<int> preorder{ 50 , 40 , 19 , 25 , 45 };
    bool my_result = problem3(preorder);
    bool expected_result = false;
    assert(my_result == expected_result);
    cout << "passed \n";
}

int main()
{
    test_case1();
    test_case2();
    test_case3();
    test_case4();
    test_case5();
    test_case6();
    test_case7();
    test_case8();
    test_case9();   // 1 BUG IN YOUR SOLUTION 
    cout << "\n\nNO RTE\n";
    return 0;
}
