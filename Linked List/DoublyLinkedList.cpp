#include <iostream>
#include <stdexcept>
#include <iterator>
#include <sstream>

// Template class for a Doubly Linked List

template <typename T>
class DoublyLinkedList {
private:
    // Node class representing an element in the linked list
    struct Node {
        T data;       // Data held by the node
        Node* prev;   // Pointer to the previous node
        Node* next;   // Pointer to the next node

        // Constructor to initialize a node with given data and pointers
        Node(T value, Node* prevNode, Node* nextNode)
            : data(value), prev(prevNode), next(nextNode) {}
    };

    Node* head; // Pointer to the first node in the list
    Node* tail; // Pointer to the last node in the list
    int size;   // Current size of the linked list

public:
    // Constructor to initialize an empty linked list
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    // Destructor to free all nodes
    ~DoublyLinkedList() {
        clear();
    }

    // Clear the linked list, O(n)
    void clear() {
        Node* trav = head;
        while (trav != nullptr) {
            Node* next = trav->next;
            delete trav; // Free memory for the current node
            trav = next; // Move to the next node
        }
        head = tail = nullptr;
        size = 0;
    }

    // Return the size of the linked list
    int getSize() const {
        return size;
    }

    // Check if the linked list is empty
    bool isEmpty() const {
        return size == 0;
    }

    // Add an element to the end of the list, O(1)
    void addLast(T elem) {
        if (isEmpty()) {
            head = tail = new Node(elem, nullptr, nullptr);
        } else {
            tail->next = new Node(elem, tail, nullptr);
            tail = tail->next;
        }
        ++size;
    }

    // Add an element to the beginning of the list, O(1)
    void addFirst(T elem) {
        if (isEmpty()) {
            head = tail = new Node(elem, nullptr, nullptr);
        } else {
            head = new Node(elem, nullptr, head);
            head->next->prev = head;
        }
        ++size;
    }

    // Peek the first element, O(1)
    T peekFirst() const {
        if (isEmpty()) throw std::runtime_error("Empty list");
        return head->data;
    }

    // Peek the last element, O(1)
    T peekLast() const {
        if (isEmpty()) throw std::runtime_error("Empty list");
        return tail->data;
    }

    // Remove the first element, O(1)
    T removeFirst() {
        if (isEmpty()) throw std::runtime_error("Empty list");

        T data = head->data;
        Node* temp = head;
        head = head->next;

        if (head == nullptr) {
            tail = nullptr; // List is now empty
        } else {
            head->prev = nullptr;
        }

        delete temp;
        --size;
        return data;
    }

    // Remove the last element, O(1)
    T removeLast() {
        if (isEmpty()) throw std::runtime_error("Empty list");

        T data = tail->data;
        Node* temp = tail;
        tail = tail->prev;

        if (tail == nullptr) {
            head = nullptr; // List is now empty
        } else {
            tail->next = nullptr;
        }

        delete temp;
        --size;
        return data;
    }

    // Remove a node at a specific index, O(n)
    T removeAt(int index) {
        if (index < 0 || index >= size) {
            throw std::invalid_argument("Index out of bounds");
        }

        Node* trav;

        if (index < size / 2) {
            // Start from the head if index is closer to the front
            trav = head;
            for (int i = 0; i < index; ++i) {
                trav = trav->next;
            }
        } else {
            // Start from the tail if index is closer to the end
            trav = tail;
            for (int i = size - 1; i > index; --i) {
                trav = trav->prev;
            }
        }

        return remove(trav);
    }

    // Remove a specific node, O(1)
    T remove(Node* node) {
        if (node->prev == nullptr) {
            return removeFirst();
        }
        if (node->next == nullptr) {
            return removeLast();
        }

        node->prev->next = node->next;
        node->next->prev = node->prev;

        T data = node->data;
        delete node;
        --size;
        return data;
    }

    // Check if the list contains a specific element, O(n)
    bool contains(T elem) const {
        return indexOf(elem) != -1;
    }

    // Get the index of a specific element, O(n)
    int indexOf(T elem) const {
        Node* trav = head;
        for (int index = 0; trav != nullptr; ++index) {
            if (trav->data == elem) {
                return index;
            }
            trav = trav->next;
        }
        return -1;
    }

    // Print the linked list as a string
    std::string toString() const {
        std::ostringstream oss;
        oss << "[ ";
        Node* trav = head;
        while (trav != nullptr) {
            oss << trav->data << (trav->next ? ", " : " ");
            trav = trav->next;
        }
        oss << "]";
        return oss.str();
    }
};

int main() {
    DoublyLinkedList<int> list;
    list.addLast(1);
    list.addLast(2);
    list.addFirst(0);

    std::cout << "List: " << list.toString() << std::endl;
    std::cout << "First: " << list.peekFirst() << std::endl;
    std::cout << "Last: " << list.peekLast() << std::endl;

    list.removeFirst();
    std::cout << "After removing first: " << list.toString() << std::endl;

    list.removeLast();
    std::cout << "After removing last: " << list.toString() << std::endl;

    return 0;
}
