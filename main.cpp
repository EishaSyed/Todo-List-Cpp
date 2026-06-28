#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// One task in the linked list
struct Node {
    string taskName;
    string priority;      // High, Medium, Low
    bool isDone;
    Node* next;
};

Node* head = NULL;

// Add a task
void addTask() {
    Node* newNode = new Node;

    cout << endl << "Enter task name: ";
    cin.ignore();
    getline(cin, newNode->taskName);

    cout << "Enter priority (High/Medium/Low): ";
    getline(cin, newNode->priority);

    newNode->isDone = false;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
    }
    else {
        Node* temp = head;

        while (temp->next != NULL) {
            temp = temp->next;
        }

        temp->next = newNode;
    }

    cout << "Task added successfully!" << endl;
}

// Display all tasks
void displayTasks() {
    if (head == NULL) {
        cout << endl << "No tasks available." << endl;
        return;
    }

    Node* temp = head;
    int num = 1;

    cout << endl << "----- TO-DO LIST -----" << endl;

    while (temp != NULL) {
        cout << num << ". "
             << temp->taskName
             << " | Priority: " << temp->priority
             << " | Status: ";

        if (temp->isDone)
            cout << "Done";
        else
            cout << "Pending";

        cout << endl;

        temp = temp->next;
        num++;
    }
}

// Mark task as done
void markAsDone() {
    if (head == NULL) {
        cout << endl << "No tasks available." << endl;
        return;
    }

    int taskNo;

    displayTasks();

    cout << endl << "Enter task number to mark as done: ";
    cin >> taskNo;

    Node* temp = head;
    int count = 1;

    while (temp != NULL && count < taskNo) {
        temp = temp->next;
        count++;
    }

    if (temp == NULL) {
        cout << "Invalid task number." << endl;
        return;
    }

    temp->isDone = true;

    cout << "Task marked as done." << endl;
}

// Delete a task
void deleteTask() {
    if (head == NULL) {
        cout << endl << "No tasks available." << endl;
        return;
    }

    int taskNo;

    displayTasks();

    cout << endl << "Enter task number to delete: ";
    cin >> taskNo;

    if (taskNo == 1) {
        Node* temp = head;
        head = head->next;
        delete temp;

        cout << "Task deleted." << endl;
        return;
    }

    Node* current = head;
    Node* previous = NULL;
    int count = 1;

    while (current != NULL && count < taskNo) {
        previous = current;
        current = current->next;
        count++;
    }

    if (current == NULL) {
        cout << "Invalid task number." << endl;
        return;
    }

    previous->next = current->next;
    delete current;

    cout << "Task deleted." << endl;
}

// Save tasks to file
void saveToFile() {
    ofstream file("tasks.txt");

    Node* temp = head;

    while (temp != NULL) {
        file << temp->taskName << endl;
        file << temp->priority << endl;
        file << temp->isDone << endl;

        temp = temp->next;
    }

    file.close();

    cout << "Tasks saved successfully!" << endl;
}

// Load tasks from file
void loadFromFile() {
    ifstream file("tasks.txt");

    if (!file) {
        return;
    }

    while (!file.eof()) {
        Node* newNode = new Node;

        getline(file, newNode->taskName);

        if (newNode->taskName == "") {
            delete newNode;
            break;
        }

        getline(file, newNode->priority);
        file >> newNode->isDone;
        file.ignore();

        newNode->next = NULL;

        if (head == NULL) {
            head = newNode;
        }
        else {
            Node* temp = head;

            while (temp->next != NULL) {
                temp = temp->next;
            }

            temp->next = newNode;
        }
    }

    file.close();

    cout << "Tasks loaded successfully!" << endl;
}


// Main function
int main() {

    loadFromFile();   // Load saved tasks when program starts

    int choice;

    do {
        cout << endl;
        cout << "===== TO-DO LIST =====" << endl;
        cout << "1. Add Task" << endl;
        cout << "2. Display Tasks" << endl;
        cout << "3. Mark as Done" << endl;
        cout << "4. Delete Task" << endl;
        cout << "5. Save Tasks" << endl;
        cout << "6. Exit" << endl;

        cout << endl << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addTask();
                break;

            case 2:
                displayTasks();
                break;

            case 3:
                markAsDone();
                break;

            case 4:
                deleteTask();
                break;

            case 5:
                saveToFile();
                break;

            case 6:
                cout << "Program ended." << endl;
                break;

            default:
                cout << "Invalid choice." << endl;
        }

    } while (choice != 6);

    return 0;
}
