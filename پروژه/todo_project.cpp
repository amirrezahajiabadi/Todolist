#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Task {
public:
    string title;
    string deadline;
    int priority;
    bool isDone;

    Task(string t, string dl, int p) {
        title = t;
        deadline = dl;
        priority = p;
        isDone = false;
    }

    virtual ~Task() {}

    virtual void show() {
        cout << "Name: " << title << " | Date: " << deadline << " | Priority: ";
        if (priority == 3) cout << "High";
        else if (priority == 2) cout << "Medium";
        else cout << "Low";

        cout << (isDone ? " [DONE]" : " [NOT DONE]") << endl;
    }
};

class Todo : public Task {
public:
    Todo(string t, string dl, int p) : Task(t, dl, p) {}
};

class TodoList {
private:
    vector<Task*> tasks;

public:
    void add(string t, string dl, int p) {
        tasks.push_back(new Todo(t, dl, p));
        cout << "Added successfully." << endl;
    }


    void displayAll() {
        if (tasks.empty()) cout << "List is empty!" << endl;
        for (Task* t : tasks) {
            t->show();
        }
    }

    void displayByStatus(bool status) {
        for (Task* t : tasks) {
            if (t->isDone == status) t->show();
        }
    }

    void finishTask(string name) {
        for (Task* t : tasks) {
            if (t->title == name) {
                t->isDone = true;
                cout << "Status updated." << endl;
                return;
            }
        }
        cout << "Task not found!" << endl;
    }

    void remove(string name) {
        for (int i = 0; i < tasks.size(); i++) {
            if (tasks[i]->title == name) {
                delete tasks[i];
                tasks.erase(tasks.begin() + i);
                cout << "Deleted." << endl;
                return;
            }
        }
    }
};

int main() {
    TodoList myTodo;
    int choice;
    string t, dl;
    int p;

    while (true) {
        cout << "\n--- TODO MENU (STL Version) ---\n";
        cout << "1. Add\n2. Show All\n3. Show Done\n4. Show Not Done\n5. Finish\n6. Delete\n7. Exit\nChoice: ";
        cin >> choice;

        if (choice == 7) break;

        if (choice == 1) {
            cout << "Name: "; cin >> t;
            cout << "Deadline: "; cin >> dl;
            cout << "Priority (1-3): "; cin >> p;
            myTodo.add(t, dl, p);
        }
        else if (choice == 2) myTodo.displayAll();
        else if (choice == 3) myTodo.displayByStatus(true);
        else if (choice == 4) myTodo.displayByStatus(false);
        else if (choice == 5) {
            cout << "Name: "; cin >> t;
            myTodo.finishTask(t);
        }
        else if (choice == 6) {
            cout << "Name to delete: "; cin >> t;
            myTodo.remove(t);
        }
    }
    return 0;
}
