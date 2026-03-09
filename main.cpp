#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Global constants and arrays
const int SIZE = 100;
int rollNos[SIZE];
string names[SIZE];
float marks[SIZE];
int total = 0;
const string FILE_NAME = "students.txt";

// Load data from file
void loadData() {
    ifstream file(FILE_NAME);
    if (!file) return;
    while (file >> rollNos[total] && total < SIZE) {
        file.ignore(); 
        getline(file, names[total]);
        file >> marks[total];
        total++;
    }
    file.close();
}

// Save data to file
void saveData() {
    ofstream file(FILE_NAME);
    for (int i = 0; i < total; i++) {
        file << rollNos[i] << endl;
        file << names[i] << endl;
        file << marks[i] << endl;
    }
    file.close();
}

// Function to add students
void addStudent() {
    if (total >= SIZE) {
        cout << "Database Full!\n";
        return;
    }
    cout << "Enter Roll No: ";
    cin >> rollNos[total];
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, names[total]);
    while (true) {
        cout << "Enter Marks Out Of 1100: ";
        cin >> marks[total];
        if (marks[total] >= 0 && marks[total] <= 1100) break;
        cout << "Invalid marks! Please enter between 0 and 1100.\n";
    }
    total++;
    saveData();
    cout << "Student Added!\n";
}

// Function to show students
void showStudents() {
    if (total == 0) {
        cout << "No records!\n";
        return;
    }
    for (int i = 0; i < total; i++) {
        float percentage = (marks[i] / 1100) * 100;
        cout << "\nRoll No: " << rollNos[i] << "\nName: " << names[i] 
             << "\nTotal Marks: 1100\nMarks Obtained: " << marks[i] 
             << "\nPercentage: " << percentage << "%\n";
    }
}

// Function to edit students
void editStudent() {
    int r;
    cout << "Enter Roll No to Edit: ";
    cin >> r;
    for (int i = 0; i < total; i++) {
        if (rollNos[i] == r) {
            cout << "Enter New Roll No: ";
            cin >> rollNos[i];
            cout << "Enter New Name: ";
            cin.ignore();
            getline(cin, names[i]);
            while (true) {
                cout << "Enter New Marks: ";
                cin >> marks[i];
                if (marks[i] >= 0 && marks[i] <= 1100) break;
                cout << "Invalid marks!\n";
            }
            saveData();
            cout << "Record Updated!\n";
            return;
        }
    }
    cout << "Student Not Found!\n";
}

// Function to delete students
void deleteStudent() {
    int r;
    cout << "Enter Roll No to Delete: ";
    cin >> r;
    for (int i = 0; i < total; i++) {
        if (rollNos[i] == r) {
            for (int j = i; j < total - 1; j++) {
                rollNos[j] = rollNos[j + 1];
                names[j] = names[j + 1];
                marks[j] = marks[j + 1];
            }
            total--;
            saveData();
            cout << "Student Deleted!\n";
            return;
        }
    }
    cout << "Student Not Found!\n";
}

int main() {
    loadData(); // Load data on startup
    int choice;
    do {
        cout << "\n--- STUDENT REPORT CARD SYSTEM ---\n";
        cout << "1. Add\n2. Show\n3. Edit\n4. Delete\n5. Exit\nChoice: ";
        cin >> choice;
        if (choice == 1) addStudent();
        else if (choice == 2) showStudents();
        else if (choice == 3) editStudent();
        else if (choice == 4) deleteStudent();
        else if (choice == 5) cout << "Exit Program!\n";
        else cout << "Invalid choice!\n";
    } while (choice != 5);
    return 0;
}
