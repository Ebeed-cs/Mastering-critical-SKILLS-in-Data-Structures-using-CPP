#include <iostream>


struct Node {
    int data{ };
    int index{ };
    Node* next{ };
    Node* prev{ };	 // Previous node!
    Node(int data, int index) : data(data), index(index) {}

    ~Node() {
        std::cout << "Destroy value: " << data << "with indexing numbers is: " << index << " at address " << this << "\n";
    }
};

class ArrayLinkedList {
private:
    Node* head{ };
    Node* tail{ };
    int length = 0;

public:

    ArrayLinkedList(int length) : length(length) {
    }
    // Below 2 deletes prevent copy and assign to avoid this mistake
    ArrayLinkedList(const ArrayLinkedList&) = delete;
    ArrayLinkedList& operator=(const ArrayLinkedList& another) = delete;

    void link(Node* first, Node* second) {
        if (first)
            first->next = second;
        if (second)
            second->prev = first;
    }
    int get_head_index() { return head->index; }
    void insert_end(int value, int index) {
        Node* item = new Node(value, index);
        // length++;

        if (!head)
            head = tail = item;
        else {
            link(tail, item);
            tail = item;
        }
    }

    void insert_front(int value, int index) {
        Node* item = new Node(value, index);
        // length++;
        if (!head)
            head = tail = item;
        else {
            link(item, head);
            head = item;
        }
    }

    void embed_after(Node* node_before, int value, int index) {
        // Add a node with value between node and its next
        Node* middle = new Node(value, index);
        // ++length;
        Node* node_after = node_before->next;
        link(node_before, middle);
        link(middle, node_after);
    }

    Node* found(int index) {
        for (Node* cur = head; cur; cur = cur->next)
            if (cur->index == index)
                return cur;
        return nullptr;
    }

    void set_value(int value, int index) {
        // 3 special cases for simplicity
        Node* found_node = nullptr;
        if (found_node = found(index)) {
            found_node->data = value;
            return;
        }
        if (!head || index <= head->index) insert_front(value, index);
        else if (tail->index <= index)
            insert_end(value, index);
        else {
            // Find the node I am less than. Then I am before it
            for (Node* cur = head; cur; cur = cur->next) {
                if (index <= cur->index) {
                    embed_after(cur->prev, value, index);
                    break;
                }
            }
        }
    }


    void print_array() {
        int i = 0;
        for (Node* cur = head; i < length;++i) {
            if (cur && i == cur->index) {
                std::cout << cur->data << " ";
                cur = cur->next;
            }
            else
                std::cout << 0 << " ";
        }
    }

    void print_array_nonzero() {
        for (Node* cur = head; cur; cur = cur->next)
            std::cout << cur->data << " ";
    }

    int get_value(int ind) {
        Node* cur = head;
        while (cur) {
            if (cur->index == ind) return cur->data;
            cur = cur->next;
        }
        return -1;
    }

    void add(ArrayLinkedList& other) {
        Node* cur1 = head;
        Node* cur2 = other.head;
        for (int i = 0; i < length && cur2; ++i) {
            if ((cur1 && cur1->index == i) || cur2->index == i) {
                int op2 = (cur2->index == i) ? cur2->data : 0;
                if (!cur1 || cur1->index != i) {
                    set_value(op2, i);

                }
                else {
                    cur1->data += op2;
                    cur1 = cur1->next;
                }
                if (cur2->index == i)
                    cur2 = cur2->next;
            }
        }
    }
};
