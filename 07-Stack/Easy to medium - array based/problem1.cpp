#include <iostream>
#include <cassert>
using namespace std;

class Stack {
private:
    int size{ };
    int added_elements{ };
    int* array{ };
public:
    Stack(int size) :
        size(size), added_elements(0) {
        array = new int[size];
    }

    ~Stack() {
        delete[] array;
    }

    bool push(int elem) { // o(n) time
        if (isFull())
            return false;
        for (int i = 0; i < added_elements; ++i)
            array[added_elements - i] = array[added_elements - i - 1];
        array[0] = elem;
        ++added_elements;
        return true;
    }

    bool pop(int elem) { // o(n) time
        if (isEmpty())
            return false;
        elem = array[0];
        for (int i = 0; i < added_elements - 1; ++i)
            array[i] = array[i + 1];
        --added_elements;
        return true;
    }

    bool peak(int& elem) { // o(1) time
        if (isEmpty())
            return false;
        elem = array[0];
        return true;
    }

    int isFull() {
        return added_elements == size;
    }

    int isEmpty() {
        return added_elements == 0;
    }

    void display() {
        for (int i = 0; i < added_elements; ++i)
            std::cout << array[i] << " ";
        std::cout << "\n";
    }
};

// the pop() , push() -> becomes consume o(n) time to do them functionalities "how even minor design choices affect our data structure"

int main() {


    Stack stk(3);
    stk.push(10);
    stk.push(20);
    stk.push(30);

    stk.display(); // 30 20 10

    int top_element = 0;
    stk.peak(top_element);
    std::cout << top_element << " "; // 30 

    return 0;
}
