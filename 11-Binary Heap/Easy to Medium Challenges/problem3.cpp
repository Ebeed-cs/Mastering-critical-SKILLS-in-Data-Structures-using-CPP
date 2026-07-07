#include<vector>
#include<iostream>
#include<cassert>
#include<deque>
using namespace std;

class MinHeap {
private:
    int* array{ };
    int size{ };
    int capacity{ 1000 };

    int left(int node) {
        int p = 2 * node + 1;
        if (p >= size)
            return -1;
        return p;
    }
    int right(int node) {
        int p = 2 * node + 2;
        return p >= size ? -1 : p;
    }
    int parent(int node) {
        return node == 0 ? -1 : (node - 1) / 2;
    }

    void heapify_up(int child_pos) {
        int par_pos = parent(child_pos);
        if (child_pos == 0 || array[par_pos] < array[child_pos])
            return;

        swap(array[child_pos], array[par_pos]);
        heapify_up(par_pos);
    }

    void heapify_down(int parent_pos) {    // O(logn)
        int child_pos = left(parent_pos);
        int right_child = right(parent_pos);

        if (child_pos == -1) // no children
            return;
        if (right_child != -1 && array[right_child] < array[child_pos])
            child_pos = right_child;

        if (array[parent_pos] > array[child_pos]) {
            swap(array[parent_pos], array[child_pos]);
            heapify_down(child_pos);
        }
    }

    void heapify() {    // O(n)
        for (int i = size / 2 - 1; i >= 0; --i)
            heapify_down(i);
    }

public:
    MinHeap() {
        array = new int[capacity] {};
        size = 0;
    }

    MinHeap(const vector<int>& v) {
        assert((int)v.size() <= capacity);
        array = new int[capacity] {};
        size = v.size();

        for (int i = 0; i < (int)v.size(); ++i)
            array[i] = v[i];

        heapify();
    }

    ~MinHeap() {
        delete[] array;
        array = nullptr;
    }

    void push(int key) {
        assert(size + 1 <= capacity);
        array[size++] = key;
        heapify_up(size - 1);
    }

    void pop() {
        assert(!isempty());
        array[0] = array[--size];
        heapify_down(0);
    }

    int top() {
        assert(!isempty());
        return array[0];
    }

    bool isempty() {
        return size == 0;
    }

    void problem3(int val, int parent_pos = 0) {
        if (isempty())
            return;

        if (parent_pos < 0 || parent_pos >= size)
            return;

        deque<int> dq;
        dq.push_back(parent_pos);

        while (!dq.empty()) {
            int cur = dq.front();
            dq.pop_front();

            if (array[cur] >= val)
                continue;

            cout << array[cur] << " ";

            int left_ind = left(cur);
            int right_ind = right(cur);

            if (left_ind != -1)
                dq.push_back(left_ind);
            if (right_ind != -1)
                dq.push_back(right_ind);
        }
    }
};


void test_case1() {
    vector<int> v{ 2, 17, 22, 10, 8, 37, 14, 19, 7, 6, 5, 12, 25, 30 };
    MinHeap heap(v);
    cout << "Test 1 (expected: 2 5 8 6 7): ";
    heap.problem3(10);
    cout << "\n";
}

void test_case2_empty_heap() {
    vector<int> v = {};
    MinHeap heap(v);
    cout << "Test 2 (empty heap, expected: nothing): ";
    heap.problem3(10);
    cout << "\n";
}

void test_case3_out_of_bounds_positive() {
    vector<int> v{ 2, 5, 8 };
    MinHeap heap(v);
    cout << "Test 3 (parent_pos=1000, expected: nothing): ";
    heap.problem3(10, 1000);
    cout << "\n";
}

void test_case4_negative_parent_pos() {
    vector<int> v{ 2, 5, 8 };
    MinHeap heap(v);
    cout << "Test 4 (parent_pos=-5, expected: nothing): ";
    heap.problem3(10, -5);
    cout << "\n";
}

void test_case5_val_smaller_than_root() {
    vector<int> v{ 2, 17, 22, 10, 8, 37, 14, 19, 7, 6, 5, 12, 25, 30 };
    MinHeap heap(v);
    cout << "Test 5 (val=2, expected: nothing): ";
    heap.problem3(2);
    cout << "\n";
}

void test_case6_single_element() {
    MinHeap heap;
    heap.push(3);
    cout << "Test 6 (single element=3, val=10, expected: 3): ";
    heap.problem3(10);
    cout << "\n";
}

void test_case7_all_elements_included() {
    vector<int> v{ 4, 6, 9, 8, 10 };
    MinHeap heap(v);
    cout << "Test 7 (val=100, expected: all 5 elements): ";
    heap.problem3(100);
    cout << "\n";
}

int main() {
    test_case1();
    test_case2_empty_heap();
    test_case3_out_of_bounds_positive();
    test_case4_negative_parent_pos();
    test_case5_val_smaller_than_root();
    test_case6_single_element();
    test_case7_all_elements_included();

    return 0;
}
