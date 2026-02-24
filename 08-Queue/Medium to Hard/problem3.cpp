#include <iostream>
#include <cassert>

// your solution is correct but it takes o(n) time complexity while we can optimize it to o(1)

template <typename  T>
class Queue {
    int size{ };
    int front{ 0 };
    int rear{ 0 };
    int added_elements{ };
    T* array{ };

public:
    Queue(int size) :
        size(size) {
        array = new T[size];
    }

    ~Queue() {
        delete[] array;
    }

    int get_added_elements() {
        return added_elements;
    }

    int next(int pos) {
        ++pos;
        if (pos == size)
            pos = 0;
        return pos;
    }

    void enqueue(T value) {
        assert(!isFull());
        array[rear] = value;
        rear = next(rear);
        added_elements++;
    }

    T dequeue() {
        assert(!isEmpty());
        T value = array[front];
        front = next(front);
        --added_elements;
        return value;
    }


    void display() {
        int step = 0;
        for (int cur = front; step < added_elements; ++step, cur = next(cur))
            std::cout << array[cur] << " ";
        std::cout << "\n\n";
    }

    bool isEmpty() {
        return added_elements == 0;
    }

    bool isFull() {
        return added_elements == size;
    }
};

class problem3 {
private:
    Queue<int> qu;
public:
    problem3(int k) :qu(k) {}

    int next(int new_num) {
        if (qu.isFull())
            qu.dequeue();

        qu.enqueue(new_num);
        int sum = 0;
        for (int i = 0; i < qu.get_added_elements(); ++i) {
            int val = qu.dequeue();
            sum += val;
            qu.enqueue(val);
        }

        return sum;
    }
};

int main() {
    problem3 prcessor(3);

    int num;
    while (std::cin >> num)
        std::cout << "the result is: " << prcessor.next(num) << "\n";

    return 0;
}
