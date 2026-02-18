#include <iostream>
#include <cassert>


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
        for (T cur = front, step = 0; step < added_elements; ++step, cur = next(cur))
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

class problem1 {
    Queue<int> q_p3;
    Queue<int> q_p2;
    Queue<int> q_p1;

    int size;
    int added_elements{};

    Queue<int>& q_pr(int p) {
        switch (p)
        {
        case 3:
            return q_p3;
        case 2:
            return q_p2;
        case 1:
            return q_p1;
        default:
            assert(false);
            return q_p1;     // unreachable , only to shut up the compiler
        }
    }
public:
    problem1(int sz) : size(sz), q_p3(sz), q_p2(sz), q_p1(sz) {}

    void enqueue(int val, int p) {
        assert(!isFull());
        q_pr(p).enqueue(val);
        ++added_elements;
    }

    int dequeue() {
        assert(!isEmpty());
        --added_elements;
        if (!q_p3.isEmpty())
            return q_p3.dequeue();
        if (!q_p2.isEmpty())
            return q_p2.dequeue();
        if (!q_p1.isEmpty())
            return q_p1.dequeue();
        return -1; // unreachable 
    }

    bool isEmpty() {
        return added_elements == 0;
    }

    bool isFull() {
        return added_elements == size;
    }

    void display() {
        std::cout << "priority #3 tasks: ";
        q_p3.display();

        std::cout << "priority #2 tasks: ";
        q_p2.display();

        std::cout << "priority #1 tasks: ";
        q_p1.display();
    }

};

int main() {
    problem1 tasks(8);

    tasks.enqueue(1131, 1);
    tasks.enqueue(3111, 3);
    tasks.enqueue(2211, 2);
    tasks.enqueue(3161, 3);

    tasks.display();

    std::cout << tasks.dequeue() << "\n";
    std::cout << tasks.dequeue() << "\n";

    tasks.enqueue(1535, 1);
    tasks.enqueue(2815, 2);
    tasks.enqueue(3845, 3);
    tasks.enqueue(3145, 3);

    tasks.display();

    while (!tasks.isEmpty())
        std::cout << tasks.dequeue() << " ";

    return 0;
}
