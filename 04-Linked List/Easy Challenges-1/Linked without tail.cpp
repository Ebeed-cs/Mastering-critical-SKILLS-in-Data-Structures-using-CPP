#include <iostream>
#include <cassert>

struct Node {
    int data{ };
    Node* next{ };
    Node(int data) : data(data) {}
    ~Node() {
        std::cout << "Destroy value: " << data << " at address " << this << "\n";
    }
};

class LinkedList {
private:
    Node* head{};
public:
    LinkedList() = default;
    void print() {
        if (!head) std::cout << "Empty list " << "\n";
        for (Node* temp = head; temp; temp = temp->next)
            std::cout << temp->data << " ";
    }

    void add_element(int value) {
        Node* node = new Node(value);
        node->next = head;
        head = node;
    }

    Node* get_tail() {
        if (!head) {
            std::cout << "Empty list \n";
            return nullptr;
        }
        Node* temp = head;
        for (; temp->next; temp = temp->next);
        return temp;
    }

    ~LinkedList() {
        while (head != nullptr) {
            Node* temp_head = head;
            head = head->next;
            delete temp_head;
        }
    }
};

int main() {
    LinkedList list1;
    list1.print();
    list1.get_tail();

    list1.add_element(1);
    list1.add_element(2);
    list1.add_element(3);
    list1.print();
    std::cout << "\n";
    if (list1.get_tail()) std::cout << list1.get_tail()->data << " ";



    // must see it, otherwise RTE
    std::cout << "\n\nNO RTE\n";
    return 0;
}
