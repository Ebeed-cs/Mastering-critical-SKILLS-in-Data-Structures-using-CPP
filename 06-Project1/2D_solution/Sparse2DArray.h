#include <iostream>
struct RowNode {
    RowNode* prev{};
    RowNode* next{};
    int row{};
    ArrayLinkedList* list{};
    RowNode(int row, ArrayLinkedList* list) : list(list), row(row) {}
};

class SparseMatrix {
private:
    RowNode* head{};
    RowNode* tail{};
    int row{};
    int col{};
public:
    SparseMatrix(int row, int col) : row(row), col(col) {}
    void link(RowNode* first, RowNode* second) {
        if (first)
            first->next = second;
        if (second)
            second->prev = first;
    }

    RowNode* get_address(int row) {
        for (RowNode* cur = head;cur; cur = cur->next)
            if (cur->row == row) return cur;
        return nullptr;
    }

    void print_matrix_nonzero() {
        for (RowNode* cur = head; cur; cur = cur->next) {
            cur->list->print_array_nonzero();
            std::cout << "\n";
        }
    }

    RowNode* insert_front_row(int r, int list_length) {
        RowNode* item = new RowNode(r, new ArrayLinkedList(list_length));
        if (!head)
            head = tail = item;
        else {
            link(item, head);
            head = item;
        }
        return item;
    }

    int getRowLength() {
        return row;
    }

    void print_matrix() {
        int i = 0;
        for (RowNode* cur = head; i < row; ++i) {
            if (cur && cur->row == i) {
                cur->list->print_array();
                cur = cur->next;
            }
            else {
                for (int i = 0; i < row; ++i)
                    std::cout << 0 << " ";
            }
            std::cout << "\n";
        }
    }

    RowNode* insert_end_row(int row, int list_length) {
        RowNode* item = new RowNode(row, new ArrayLinkedList(list_length));
        // length++;

        if (!head)
            head = tail = item;
        else {
            link(tail, item);
            tail = item;
        }
        return item;
    }

    RowNode* embed_after_row(RowNode* node_before, int row, int list_length) {
        // Add a node with value between node and its next
        RowNode* middle = new RowNode(row, new ArrayLinkedList(list_length));
        // ++length;
        RowNode* node_after = node_before->next;
        link(node_before, middle);
        link(middle, node_after);

        return middle;
    }

    RowNode* set_value(int data, int r, int c) {
        if (r >= row || r < 0 || c >= col || c < 0) {
            std::cout << "invalid boundaries..." << "\n";
            return nullptr;
        }
        RowNode* RNode = nullptr;
        if (!(RNode = get_address(r))) {
            if (!head || r <= head->row) RNode = insert_front_row(r, col);
            else if (tail->row <= row)
                RNode = insert_end_row(r, col);
            else {
                for (RowNode* cur = head; cur; cur = cur->next) {
                    if (r <= cur->row) {
                        RNode = embed_after_row(cur->prev, r, col);
                        break;
                    }
                }
            }
        }
        RNode->list->set_value(data, c);
        return RNode;
    }

    void add(SparseMatrix& other) {
        if (getRowLength() != other.getRowLength()) {
            std::cout << "the two lengths not equal" << "\n";
            return;
        }

        RowNode* cur2 = other.head;

        // Iterate through all rows in the second matrix
        while (cur2) {
            int row_index = cur2->row;

            // Check if this row exists in the current matrix
            RowNode* cur1 = get_address(row_index);

            if (cur1) {
                // Row exists, add the lists
                cur1->list->add(*(cur2->list));
            }
            else {
                RowNode* new_row = set_value(0, row_index, cur2->list->get_head_index());
                if (new_row)
                    new_row->list->add(*(cur2->list));
            }

            cur2 = cur2->next;
        }
    }
};
