#include <iostream>
#include <cassert>
#include <climits>
#include <tuple>

#include <vector>		// for debug
#include <algorithm>
#include <sstream>
using namespace std;

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

    vector<Node*> debug_data;	// add/remove nodes you use
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

    // LinkedList(const LinkedList&) = delete;
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


    Node* add_next(Node* pos, int value) {
        length++;
        Node* node = new Node(value);
        if (pos == tail) {
            pos->next = node;
            tail = node;
            tail->next = nullptr;
            return nullptr;
        }
        Node* temp = pos->next;
        pos->next = node;
        node->next = temp;
        return temp;
    }

    Node* add_next2(Node* pos, Node* node) {
        length++;
        if (pos == tail) {
            pos->next = node;
            tail = node;
            tail->next = nullptr;
            return nullptr;
        }
        Node* temp = pos->next;
        pos->next = node;
        node->next = temp;
        return temp;
    }



    // that is the first version of my solution , here i was did "deep copy" but i can make it better in memory complexity
    // clarification: deep copy here i mean , i didn't use the old nodes for another i created a new ones to me 
    void add_alternate(LinkedList& another) { // o(n) time , o(n) memory  
        Node* cur1 = head, * cur2 = another.head;
        for (; cur1 && cur2; cur2 = cur2->next)
            cur1 = add_next(cur1, cur2->data);
        if (!cur1 && cur2)
            for (Node* cur = cur2; cur; cur = cur->next)
                insert(cur->data);
        debug_verify_data_integrity();
    }

    // the new version , i can use the old nodes for another which already created before and don't make new ones
    void add_alternate2(LinkedList& another) { // o(n) time , o(1) memory 
        Node* cur1 = head, * cur2 = another.head;
        for (; cur1 && cur2; cur2 = cur2->next)
            cur1 = add_next2(cur1, cur2), another.length--; // note in the first version we didn't care about the another length consistancy because we did "deep copy" and in the end will destroy which all it's info(head , tail , length)
        if (length == 0) {
            head = another.head;
            tail = another.tail;
            length = another.length;
        }
        else if (cur1 && cur2) {
            tail->next = cur2;
            tail = another.tail;
            length += another.length;
        }
        head = tail = nullptr;
        another.length = 0;


    }

    ~LinkedList() {
        while (head != nullptr) {
            Node* temp_head = head;
            head = head->next;
            delete temp_head;
        }
        tail = nullptr;
    }

    void debug_print_node(Node* node, bool is_seperate = false) {
        if (is_seperate)
            cout << "Sep: ";
        if (node == nullptr) {
            cout << "nullptr\n";
            return;
        }
        cout << node->data << " ";
        if (node->next == nullptr)
            cout << "X ";
        else
            cout << node->next->data << " ";

        if (node == head)
            cout << "head\n";
        else if (node == tail)
            cout << "tail\n";
        else
            cout << "\n";
    }
    // void debug_print_list(string msg = "") {
    //     if (msg != "")
    //         cout << msg << "\n";
    //     for (int i = 0; i < (int)debug_data.size(); ++i)
    //         debug_print_node(debug_data[i]);
    //     cout << "************\n" << flush;
    // }

    string debug_to_string() {
        if (length == 0)
            return "";
        ostringstream oss;
        for (Node* cur = head; cur; cur = cur->next) {
            oss << cur->data;
            if (cur->next)
                oss << " ";
        }
        return oss.str();
    }
};

void test1() {
    cout << "\n\ntest1\n";
    LinkedList list1;

    LinkedList list2;

    list2.insert(1);
    list2.insert(2);
    list2.insert(3);

    list1.add_alternate(list2);

    list1.print();

    string expected = "1 2 3";
    string result = list1.debug_to_string();
    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    // list1.debug_print_list("********");
}

void test2() {
    cout << "\n\ntest2\n";
    LinkedList list1;

    list1.insert(1);
    list1.insert(2);
    list1.insert(3);

    LinkedList list2;

    list1.add_alternate(list2);

    list1.print();

    string expected = "1 2 3";
    string result = list1.debug_to_string();
    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    // list1.debug_print_list("********");
}

void test3() {
    cout << "\n\ntest3\n";
    LinkedList list1;

    list1.insert(1);

    LinkedList list2;
    list2.insert(1);
    list2.insert(2);

    list1.add_alternate(list2);

    list1.print();

    string expected = "1 1 2";
    string result = list1.debug_to_string();
    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    // list1.debug_print_list("********");
}

void test4() {
    cout << "\n\ntest4\n";
    LinkedList list1;

    list1.insert(1);
    list1.insert(2);

    LinkedList list2;
    list2.insert(1);

    list1.add_alternate(list2);

    list1.print();

    string expected = "1 1 2";
    string result = list1.debug_to_string();
    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    // list1.debug_print_list("********");
}

void test5() {
    cout << "\n\ntest5\n";
    LinkedList list1;

    list1.insert(1);
    list1.insert(2);

    LinkedList list2;
    list2.insert(1);
    list2.insert(2);

    list1.add_alternate(list2);

    list1.print();

    string expected = "1 1 2 2";
    string result = list1.debug_to_string();
    if (expected != result) {
        cout << "no match:\nExpected: " << expected << "\nResult  : " << result << "\n";
        assert(false);
    }
    // list1.debug_print_list("********");
}

int main() {
    test1();
    test2();
    test3();
    test4();
    test5();

    // must see it, otherwise RTE
    std::cout << "\n\nNO RTE\n";
    return 0;
}
