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

    void insert_end(int value) {
        length++;
        Node* item = new Node(value);

        if (!head)
            head = tail = item;
        else
            tail->next = item, tail = item;
    }

    bool is_same(const LinkedList& other) {
        if (length != other.length) return false;
        for (Node* temp1 = head, *temp2 = other.head; (temp1 != nullptr); temp1 = temp1->next, temp2 = temp2->next)
            if (temp1->data != temp2->data) return false;
        return true;
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

    Node* get_nth_back(int n) {
        if (head == nullptr) return nullptr;
        int index = length - n;
        Node* temp = head;
        for (; index > 0; temp = temp->next, --index);
        return temp;
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
    LinkedList list2;

    std::cout << list1.is_same(list2) << "\n";
    list1.insert_end(6);
    list1.insert_end(10);
    list2.insert_end(6);


    std::cout << list1.is_same(list2) << "\n";
    list2.insert_end(10);
    std::cout << list1.is_same(list2) << "\n";
    list1.insert_end(8);
    list1.insert_end(15);
    list2.insert_end(8);
    list2.insert_end(77);

    std::cout << list1.is_same(list2) << "\n";

    // must see it, otherwise RTE
    std::cout << "\n\nNO RTE\n";
    return 0;
}
