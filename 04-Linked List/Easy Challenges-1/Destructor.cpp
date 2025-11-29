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


    int search_move(int val) {
        if (head == nullptr) return -1;  // Empty list
        if (head->data == val) return 0;
        int ind = 0;
        for (Node* temp = head; temp->next != nullptr; temp = temp->next, ind++)
            if (temp->next->data == val) {
                std::swap(temp->data, temp->next->data);
                return ind;
            }
        return -1;
    }

    Node* nth(int n) {
        int count = 0;
        for (Node* temp = head; temp; temp = temp->next)
            if (++count == n) return temp;
        return nullptr;
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
    LinkedList link;

    link.insert(6);
    link.insert(10);
    link.insert(8);
    link.insert(15);

    link.print();

    // must see it, otherwise RTE
    std::cout << "\n\nNO RTE\n";
    return 0;
}
