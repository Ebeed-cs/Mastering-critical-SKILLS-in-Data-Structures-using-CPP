#include <iostream>
#include <cassert>
using namespace std;

class Stack {
private:
    int size{ };
    int top{ };
    int* array{ };
public:
    Stack(int size) :
        size(size), top(-1) {
        array = new int[size];
    }

    ~Stack() {
        delete[] array;
    }

    void push(int x) {
        assert(!isFull());
        array[++top] = x;
    }

    int pop() {
        assert(!isEmpty());
        return array[top--];
    }

    int peek() {
        assert(!isEmpty());
        return array[top];
    }

    int isFull() {
        return top == size - 1;
    }

    int isEmpty() {
        return top == -1;
    }

    void display() {
        for (int i = top; i >= 0; i--)
            cout << array[i] << " ";
        cout << "\n";
    }
};


class Queue {
private:
    int size{ };
    int added_elements{};
    Stack s1; // the main stack
    Stack s2;   // helper stack

public:
    Queue(int s) :size(s), s1(s), s2(s) {}

    void enqueue(int val) {
        assert(!isFull());
        added_elements++;
        while (!s1.isEmpty())
            s2.push(s1.pop());
        s2.push(val);
        while (!s2.isEmpty())
            s1.push(s2.pop());
    }

    int dequeue() {
        assert(!isEmpty());
        --added_elements;
        return s1.pop();
    }


    bool isEmpty() {
        return added_elements == 0;
    }

    bool isFull() {
        return added_elements == size;
    }

    void display() {
        while (!isEmpty())
            std::cout << dequeue() << " ";
    }
};


int main() {
    Queue qu(6);

    for (int i = 1; i <= 3; ++i)
        qu.enqueue(i);

    std::cout << qu.dequeue() << "\n";

    for (int i = 4; i <= 5; ++i)
        qu.enqueue(i);

    qu.display();
    return 0;
}
