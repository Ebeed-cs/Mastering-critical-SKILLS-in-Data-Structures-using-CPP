#include <iostream>
#include <cassert>
#include <vector>

struct Node
{
    int data{};
    Node *next{};
    Node(int data) : data(data) {}
    ~Node()
    {
        std::cout << "Destroy value: " << data << " at address " << this << "\n";
    }
};

class LinkedList
{
private:
    Node *head{};
    Node *tail{};
    int length{};

public:
    LinkedList() = default;

    void insert(int val)
    {
        Node *node = new Node(val);
        length++;
        if (head == nullptr)
        {
            head = tail = node;
            return;
        }
        tail->next = node;
        tail = node;
    }

    void debug_verify_data_integrity()
    {
        if (length == 0)
        {
            assert(head == nullptr);
            assert(tail == nullptr);
        }
        else
        {
            assert(head != nullptr);
            assert(tail != nullptr);
            if (length == 1)
                assert(head == tail);
            else
                assert(head != tail);
            assert(!tail->next);
        }
        int len = 0;
        for (Node *cur = head; cur; cur = cur->next, len++)
            assert(len < 10000); // Consider infinite cycle?
        assert(length == len);
        // assert(length == (int)debug_data.size());
    }

    void print()
    {
        Node *temp_head = head;
        while (temp_head != nullptr)
        {
            std::cout << temp_head->data << " ";
            temp_head = temp_head->next;
        }
        std::cout << "\n";
        std::cout << "the current length is :" << length << "\n";
    }

    LinkedList(const LinkedList &) = delete;
    LinkedList &operator=(const LinkedList &) = delete;

    void insert_front(int val)
    {
        length++;
        Node *node = new Node(val);
        if (head == nullptr)
        {
            head = tail = node;
            return;
        }
        node->next = head;
        head = node;
    }

    void delete_next(Node *node)
    {
        if (!head || !node || !node->next)
            return;
        length--;
        Node *temp = node->next;
        node->next = node->next->next;
        delete temp;
        if (!node->next)
            tail = head;
    }

    void delete_even_position()
    {
        for (Node *temp = head; temp; temp = temp->next)
            delete_next(temp);
    }

    ~LinkedList()
    {
        while (head != nullptr)
        {
            Node *temp_head = head;
            head = head->next;
            delete temp_head;
        }
        tail = nullptr;
    }
};

int main()
{
    LinkedList list1;

    list1.insert(1);
    list1.insert(2);
    list1.insert(3);
    list1.insert(4);
    list1.insert(5);
    list1.insert(6);
    list1.delete_even_position();
    list1.print();

    // must see it, otherwise RTE
    std::cout << "\n\nNO RTE\n";
    return 0;
}