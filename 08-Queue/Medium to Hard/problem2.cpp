#include <iostream>
#include <cassert>

// ok my idea is good , but what if the user entered an integer it's value is "-1" , your approach will failed 

template <typename  T>
class problem2 {
    int size{ };
    int front{ 0 };
    int rear{ 0 };
    T* array{ };

public:
    problem2(int size) :
        size(size) {
        array = new T[size];
        for (int i = 0; i < size; ++i)
            array[i] = -1;
    }

    ~problem2() {
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
    }

    T dequeue() {
        assert(!isEmpty());
        T value = array[front];
        array[front] = -1;
        front = next(front);
        return value;
    }


    void display() {
        int count = 0;
        for (T cur = front; array[cur] != -1 && count++ != size;cur = next(cur))
            std::cout << array[cur] << " ";
        std::cout << "\n\n";
    }

    bool isEmpty() {
        return array[front] == -1;
    }

    bool isFull() {
        return ((front == rear) && !isEmpty());
    }
};

int main() {
    problem2<int> qu(6);
    assert(qu.isEmpty());
    qu.display();

    for (int i = 1; i <= 6; ++i) {
        assert(!qu.isFull());
        qu.enqueue(i);
        qu.display();
    }
    assert(qu.isFull());

    for (int i = 1; i <= 6; ++i) {
        assert(!qu.isEmpty());
        qu.dequeue();
        qu.display();
    }

    for (int i = 1; i <= 6; ++i) {
        assert(!qu.isFull());
        qu.enqueue(i);
        qu.display();
    }

    qu.dequeue();
    assert(!qu.isFull());
    qu.enqueue(7);
    assert(qu.isFull());
    qu.display();

    qu.dequeue();
    qu.dequeue();
    assert(!qu.isFull());
    qu.enqueue(8);
    assert(!qu.isFull());
    qu.display();
    qu.enqueue(9);
    assert(qu.isFull());
    qu.display();

    for (int i = 1; i <= 6; ++i) {
        assert(!qu.isEmpty());
        qu.dequeue();
        qu.display();
    }

    return 0;
}
