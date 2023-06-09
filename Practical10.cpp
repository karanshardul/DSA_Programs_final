/*
Name: Spandan P. Marathe
Class: SE-IV		Batch: H4		Roll No.: 21487
Practical No.: 10
 */

#include <iostream>
using namespace std;

class Student {
public:
    string name;
    int rank;

    Student(const string& name, int rank) {
        this->name = name;
        this->rank = rank;
    }
};

class MaxHeap {
private:
    Student** heap;
    int capacity; // MAX number of data that can be stored
    int size;     // Current no. of data present

    int parent(int i) { return (i - 1/ 2); }

    int leftChild(int i) { return 2 * i + 1; }

    int rightChild(int i) { return 2 * i + 2; }

    void swap(Student*& a, Student*& b) {
        Student* temp = a;
        a = b;
        b = temp;
    }

    void maxHeapify(int i) {
        int left = leftChild(i);
        int right = rightChild(i);
        int largest = i;

        if (left < size && heap[left]->rank > heap[largest]->rank)
            largest = left;

        if (right < size && heap[right]->rank > heap[largest]->rank)
            largest = right;

        if (largest != i) {
            swap(heap[i], heap[largest]);       
            maxHeapify(largest);
        }
    }

public:
    MaxHeap(int capacity) {
        this->capacity = capacity;
        heap = new Student * [capacity];
        size = 0;
    }

    void insert(Student* student) {
        if (size == capacity)
            return;

        size++;
        int currentIndex = size - 1;
        heap[currentIndex] = student;

        // while (currentIndex > 0 &&heap[currentIndex]->rank > heap[parent(currentIndex)]->rank) {
        //     swap(heap[currentIndex], heap[parent(currentIndex)]);
        //     currentIndex = parent(currentIndex);
        // }
    }

    Student* extractMax() {
        if (size == 0)
            return nullptr;

        Student* maxStudent = heap[0];
        heap[0] = heap[size - 1]; // last element of heap array
        size--;
        maxHeapify(0);

        return maxStudent;
    }
};


// Getting the pointer of the student array
void heapSort(Student* arr[], int n) {
    MaxHeap MaxHeap(n);

    // Build max heap
    for (int i = 0; i < n; i++)
        MaxHeap.insert(arr[i]);

    // Extract max elements and place them at the end of the array
    // for (int i = n - 1; i >= 0; i--)
    //     arr[i] = MaxHeap.extractMax(); // It changes the sequence of student array as it is a pointer
}

int main() {
    const int numStudents = 7;

    // Student data (name, rank)
    Student* students[numStudents] = {
        new Student("Spandan", 3), new Student("Alok", 2), new Student("Diksha", 9),
        new Student("Ritesh", 1), new Student("Pranav", 6), new Student("Rutuja", 7), new Student("Kriti", 10) };

    heapSort(students, numStudents);

    cout << "\nPerforming HEAP SORT Algorithm\n\n";
    cout << "Sorted Students Data (Ascending Order of Ranks):\n" << endl;
    for (int i = 0; i < numStudents; i++)
        cout << students[i]->name << ": Rank " << students[i]->rank << endl;

    return 0;
}



/*

OUTPUT:

Performing HEAP SORT Algorithm

Sorted Students Data (Ascending Order of Ranks):

Nakul: Rank 1
Alok: Rank 2
Sameer: Rank 5
Pranav: Rank 6
Rutuja: Rank 8
Diksha: Rank 9
Kriti: Rank 10

*/