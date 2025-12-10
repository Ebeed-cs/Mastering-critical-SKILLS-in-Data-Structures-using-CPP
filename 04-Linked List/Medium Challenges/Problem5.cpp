#include <iostream>
#include <cassert>
#include <vector>

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
    Node* tail{};
    int length{};
public:
    LinkedList() = default;

    void insert(int val) {
        Node* node = new Node(val);
        length++;
        if (head == nullptr) {
            head = tail = node;
            return;
        }
        tail->next = node;
        tail = node;
    }

    void debug_verify_data_integrity() {
        if (length == 0) {
            assert(head == nullptr);
            assert(tail == nullptr);
        }
        else {
            assert(head != nullptr);
            assert(tail != nullptr);
            if (length == 1)
                assert(head == tail);
            else
                assert(head != tail);
            assert(!tail->next);
        }
        int len = 0;
        for (Node* cur = head; cur; cur = cur->next, len++)
            assert(len < 10000);	// Consider infinite cycle?
        assert(length == len);
        // assert(length == (int)debug_data.size());
    }

    void print() {
        Node* temp_head = head;
        while (temp_head != nullptr) {
            std::cout << temp_head->data << " ";
            temp_head = temp_head->next;
        }
        std::cout << "\n";
        std::cout << "the current length is :" << length << "\n";
    }

    LinkedList(const LinkedList&) = delete;
    LinkedList& operator=(const LinkedList&) = delete;

    void insert_front(int val) {
        length++;
        Node* node = new Node(val);
        if (head == nullptr) {
            head = tail = node;
            return;
        }
        node->next = head;
        head = node;
    }

    void delete_node(Node* node) {
        --length;
        delete node;
    }

    void delete_next_node(Node* node) {
        // Delete the next of the current node
        // Handle if next is tail case
        assert(node);

        Node* to_delete = node->next;
        bool is_tail = to_delete == tail;

        // node->next in middle to delete
        node->next = node->next->next;

        delete_node(to_delete);
        if (is_tail)
            tail = node;
    }

    void back(int key) { // o(n) time - o(1) memory
        if (length <= 1) return;
        bool found = false;
        Node* first_appear = nullptr;
        for (Node* cur = head; cur->next && cur->next != first_appear && cur->next != tail; ) {
            if (cur->next->data == key) {
                tail->next = cur->next;
                cur->next = cur->next->next;
                tail = tail->next;
                tail->next = nullptr;
                if (!found) first_appear = tail;
                found = true;
            }
            else cur = cur->next;
        }
        if (head->data == key) {
            tail->next = head;
            tail = tail->next;
            head = head->next;
            tail->next = nullptr;
        }
    }

    ~LinkedList() {
        while (head != nullptr) {
            Node* temp_head = head;
            head = head->next;
            delete temp_head;
        }
        tail = nullptr;
    }
};

int main() {
    LinkedList list1;

    list1.insert(1);
    list1.insert(2);
    list1.insert(3);
    list1.insert(1);
    list1.insert(2);
    list1.insert(4);
    list1.insert(1);
    list1.insert(7);
    list1.insert(1);
    list1.insert(8);
    list1.insert(1);
    list1.insert(1);

    list1.back(1);

    list1.print();


    // must see it, otherwise RTE
    std::cout << "\n\nNO RTE\n";
    return 0;
}
