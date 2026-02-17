#include <iostream>
#include <cassert>


template <typename  T>
class Deque {
    int size{ };
    int front{ 0 };
    int rear{ 0 };
    int added_elements{ };
    T* array{ };

public:
    Deque(int size) :
        size(size) {
        array = new T[size];
    }

    ~Deque() {
        delete[] array;
    }

    int next(int pos) {
        ++pos;
        if (pos == size)
            pos = 0;
        return pos;
    }

    void enqueue_rear(T value) {
        assert(!isFull());
        array[rear] = value;
        rear = next(rear);
        added_elements++;
    }

    void enqueue_front(T value) {
        assert(!isFull());
        front = prev(front);
        array[front] = value;
        ++added_elements;
    }

    int prev(int pos) {
        --pos;
        if (pos < 0)
            pos = size - 1;
        return pos;
    }

    T dequeue_front() {
        assert(!isEmpty());
        T value = array[front];
        front = next(front);
        --added_elements;
        return value;
    }

    T dequeue_rear() {
        assert(!isEmpty());
        T value = array[rear];
        rear = prev(rear);
        --added_elements;
        return value;
    }

    void display() {
        std::cout << "Front " << front << " - rear " << rear << "\t";
        if (isFull())
            std::cout << "full";
        else if (isEmpty()) {
            std::cout << "empty\n\n";
            return;
        }
        std::cout << "\n";

        for (T cur = front, step = 0; step < added_elements; ++step, cur = next(cur))
            std::cout << array[cur] << " ";
        std::cout << "\n\n";
    }

    int isEmpty() {
        return added_elements == 0;
    }

    bool isFull() {
        return added_elements == size;
    }
};

int main() {

    Deque<int> dq(6);

    dq.enqueue_front(3);
    dq.display();
    dq.enqueue_front(2);
    dq.enqueue_rear(4);
    dq.enqueue_front(1);
    dq.enqueue_front(5);
    dq.enqueue_front(6);
    dq.display();	// 6 5 1 2 3 4
    std::cout << dq.dequeue_rear() << "\n";	// 4
    dq.display();	// 6 5 1 2 3
    std::cout << dq.dequeue_front() << "\n";	// 6
    dq.display();	//  5 1 2 3
    std::cout << dq.dequeue_rear() << "\n";	// 3
    std::cout << dq.dequeue_front() << "\n";	// 2

    while (!dq.isEmpty())
        dq.dequeue_rear();
    dq.display();	//
    for (int i = 0; i < 6; ++i)
        dq.enqueue_rear(i + 10);
    dq.display();	//
    return 0;
}
