// Implementation of a dynamic array in C++

#include <iostream>
#include <stdexcept>
#include <iterator>
#include <sstream>

template <typename T>
class DynamicArray {
private:
    T* arr;           // Pointer to the array
    int len;          // Current number of elements in the array
    int capacity;     // Actual size of the allocated array

    // Helper function to resize the array when needed
    void resize(int newCapacity) {
        T* newArr = new T[newCapacity];
        for (int i = 0; i < len; ++i) {
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
        capacity = newCapacity;
    }

public:
    // Default constructor
    DynamicArray() : len(0), capacity(16) {
        arr = new T[capacity];
    }

    // Constructor with initial capacity
    DynamicArray(int initialCapacity) : len(0), capacity(initialCapacity) {
        if (initialCapacity < 0) {
            throw std::invalid_argument("Illegal Capacity: " + std::to_string(initialCapacity));
        }
        arr = new T[capacity];
    }

    // Destructor to clean up allocated memory
    ~DynamicArray() {
        delete[] arr;
    }

    // Returns the current size of the array
    int size() const {
        return len;
    }

    // Checks if the array is empty
    bool isEmpty() const {
        return len == 0;
    }

    // Returns the element at a given index
    T get(int index) const {
        if (index < 0 || index >= len) {
            throw std::out_of_range("Index out of bounds");
        }
        return arr[index];
    }

    // Sets the element at a given index
    void set(int index, T elem) {
        if (index < 0 || index >= len) {
            throw std::out_of_range("Index out of bounds");
        }
        arr[index] = elem;
    }

    // Clears the array
    void clear() {
        for (int i = 0; i < len; ++i) {
            arr[i] = T();
        }
        len = 0;
    }

    // Adds an element to the end of the array
    void add(T elem) {
        if (len + 1 > capacity) {
            resize(capacity == 0 ? 1 : capacity * 2);
        }
        arr[len++] = elem;
    }

    // Removes an element at a specified index
    T removeAt(int rmIndex) {
        if (rmIndex < 0 || rmIndex >= len) {
            throw std::out_of_range("Index out of bounds");
        }
        T removedElement = arr[rmIndex];
        for (int i = rmIndex; i < len - 1; ++i) {
            arr[i] = arr[i + 1];
        }
        --len;
        return removedElement;
    }

    // Removes the first occurrence of an element
    bool remove(T elem) {
        int index = indexOf(elem);
        if (index == -1) return false;
        removeAt(index);
        return true;
    }

    // Finds the index of an element
    int indexOf(T elem) const {
        for (int i = 0; i < len; ++i) {
            if (arr[i] == elem) {
                return i;
            }
        }
        return -1;
    }

    // Checks if the array contains a specific element
    bool contains(T elem) const {
        return indexOf(elem) != -1;
    }

    // Iterator class for the dynamic array
    class Iterator {
    private:
        T* ptr;
    public:
        explicit Iterator(T* p) : ptr(p) {}
        Iterator& operator++() {
            ++ptr;
            return *this;
        }
        bool operator!=(const Iterator& other) const {
            return ptr != other.ptr;
        }
        const T& operator*() const {
            return *ptr;
        }
    };

    // Returns an iterator to the beginning of the array
    Iterator begin() const {
        return Iterator(arr);
    }

    // Returns an iterator to the end of the array
    Iterator end() const {
        return Iterator(arr + len);
    }

    // Converts the array to a string for printing
    std::string toString() const {
        if (len == 0) return "[]";
        std::ostringstream oss;
        oss << "[";
        for (int i = 0; i < len - 1; ++i) {
            oss << arr[i] << ", ";
        }
        oss << arr[len - 1] << "]";
        return oss.str();
    }
};

// Example usage
int main() {
    DynamicArray<int> arr;

    arr.add(10);
    arr.add(20);
    arr.add(30);

    std::cout << "Array: " << arr.toString() << std::endl;
    std::cout << "Size: " << arr.size() << std::endl;

    arr.removeAt(1);
    std::cout << "After removing index 1: " << arr.toString() << std::endl;

    arr.add(40);
    std::cout << "After adding 40: " << arr.toString() << std::endl;

    return 0;
}
