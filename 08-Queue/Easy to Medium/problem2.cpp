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

    bool isEmpty() {
        return added_elements == 0;
    }

    bool isFull() {
        return added_elements == size;
    }
};

class Stack {
private:
    int added_elements{};
    Queue<int> q;

    void insert_front(int val) {
        q.enqueue(val);
        int count = added_elements;
        while (count--)
            q.enqueue(q.dequeue());
        ++added_elements;
    }
public:
    Stack(int s) : q(s) {};

    int peek() {
        int val = q.dequeue();
        --added_elements;
        insert_front(val);
        return val;
    }

    int pop() {
        --added_elements;
        return q.dequeue();
    }

    void push(int val) {
        insert_front(val);
    }

    bool isEmpty() {
        return q.isEmpty();
    }

    bool isFull() {
        return q.isFull();
    }
};

int main() {
    Stack stk(5);
    stk.push(10);
    stk.push(20);
    stk.push(30);
    stk.push(40);
    stk.push(50);

    while (!stk.isEmpty()) {
        std::cout << stk.peek() << " ";
        stk.pop();
    }

    return 0;
}
