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

    bool problem4(int* p, int n, int st = 0) {
        int l = 2 * st + 1, r = 2 * st + 2;
        if (l >= n) return true;
        if (p[st] > p[l]) return false;
        if (r >= n) return true;
        if (p[st] > p[r]) return false;
        return problem4(p, n, st + 1);
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

    void print_array() {
        for (int i = 0; i < size; ++i)
            cout << array[i] << " ";
    }

};


void test_case1() {
    vector<int> v = { 2, 6, 14, 7, 8, 37, 22, 19, 10, 17 };
    vector<int> v2 = {};
    vector<int> v3 = { 2 };
    vector<int> v4 = { 2, 6 };

    MinHeap heap;

    cout << heap.problem4(v.data(), v.size()) << "\n"; // 1
    cout << heap.problem4(v2.data(), v2.size()) << "\n"; // 1
    cout << heap.problem4(v3.data(), v3.size()) << "\n"; // 1
    cout << heap.problem4(v4.data(), v4.size()) << "\n"; // 1
    cout << "\n";
}

int main() {
    test_case1();
    return 0;
}
