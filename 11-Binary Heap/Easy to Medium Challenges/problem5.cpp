#include<vector>
#include<iostream>
#include<cassert>
#include<deque>
#include <algorithm>
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

    void problem5(int* p, int n) {
        int* old_array = array;
        int old_size = size;
        array = p;
        size = n;
        assert((int)size <= capacity);
        heapify();

        while (size > 1) {
            swap(array[0], array[size - 1]);
            --size;
            heapify_down(0);
        }
        reverse(p, p + n);
        array = old_array;
        size = old_size;
    }

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
};


void test_case1() {
    const int SZ = 14;
    int arr[SZ]{ 2, 17, 22, 10, 8, 37, 14, 19, 7, 6, 5, 12, 25, 30 };
    MinHeap heap;

    heap.problem5(arr, SZ);

    for (int i = 0; i < SZ; ++i)
        cout << arr[i] << " ";
    cout << "\n";
}

int main() {
    test_case1();
    return 0;
}
