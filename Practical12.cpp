/*
Name: Spandan P. Marathe
Class: SE-IV		Batch: H4		Roll No.: 21487
Practical No.: 12
 */

#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

const int MAX_RECORDS = 100;

class Student {
    int rollNumber;
    char name[50];
    char address[100];

public:
    void readData() {
        cout << "Enter Roll Number: ";
        cin >> rollNumber;
        cin.ignore(); // Ignore the newline charac1ter left by cin

        cout << "Enter Name: ";
        cin.getline(name, 50);

        cout << "Enter Address: ";
        cin.getline(address, 100);
    }

    void displayData() {
        cout << "Roll Number: " << rollNumber << endl;
        cout << "Name: " << name << endl;
        cout << "Address: " << address << endl;
        cout << "---------------------" << endl;
    }

    int getRollNumber() { return rollNumber; }
};

class StudentManagement {
    ofstream file;
    ifstream inputFile;

    int hashFunction(int rollNumber) { return rollNumber % MAX_RECORDS; }

public:
    void addStudent() {
        file.open("students.dat", ios::binary | ios::app);

        Student student;
        student.readData();

        int position = hashFunction(student.getRollNumber());
        // file.seekp(position * sizeof(Student), ios::beg);
        // file.write(reinterpret_cast<char*>(&student), sizeof(Student));

        // file.close();
        file.seekp(position *sizeof(Student), ios::beg);
        file.write(reinterpret_cast<char*>(&student), sizeof(Student));
        file.close()
        cout << "Student added successfully!" << endl;
    }

    void deleteStudent() {
        int rollNumber;
        cout << "Enter Roll Number of the student to delete: ";
        cin >> rollNumber;

        int position = hashFunction(rollNumber);

        inputFile.open("students.dat", ios::binary);
        if (!inputFile) {
            cout << "File not found!" << endl;
            return;
        }

        ofstream tempFile;
        tempFile.open("temp.dat", ios::binary);

        Student student;
        while (
            inputFile.read(reinterpret_cast<char*>(&student), sizeof(Student))) {
            if (student.getRollNumber() != rollNumber) {
                tempFile.write(reinterpret_cast<char*>(&student), sizeof(Student));
            }
        }

        inputFile.close();
        tempFile.close();

        remove("students.dat");
        rename("temp.dat", "students.dat");

        cout << "Student deleted successfully!" << endl;
    }

    void displayStudents() {
        inputFile.open("students.dat", ios::binary);
        if (!inputFile) {
            cout << "File not found!" << endl;
            return;
        }

        Student student;
        while (
            inputFile.read(reinterpret_cast<char*>(&student), sizeof(Student))) {
            student.displayData();
        }

        inputFile.close();
    }

    void run() {
        int choice;

        while (true) {
            cout << "Menu" << endl;
            cout << "1. Add Student" << endl;
            cout << "2. Delete Student" << endl;
            cout << "3. Display Students" << endl;
            cout << "4. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {   
            case 1:
                addStudent();
                break;
            case 2:
                deleteStudent();
                break;
            case 3:
                displayStudents();
                break;
            case 4:
                exit(0);
            default:
                cout << "Invalid choice!" << endl;
            }

            cout << endl;
        }
    }
};

int main() {
    StudentManagement management;
    management.run();

    return 0;
}

