#include <iostream>
#include <stack>
#include <queue>
#include <string>
using namespace std;

stack<string> stops;
queue<string> route;

void addStop() {
    string name;

    cout << "Enter bus stop name: ";
    getline(cin >> ws, name);

    stops.push(name);
    route.push(name);

    cout << "Bus stop added successfully!\n";
}

void removeStop() {
    if (stops.empty()) {
        cout << "No bus stops available!\n";
        return;
    }

    string name = stops.top();
    stops.pop();

    // Rebuild the queue without the removed stop.
    queue<string> temp;

    while (!route.empty()) {
        string current = route.front();
        route.pop();

        if (current != name) {
            temp.push(current);
        }
    }

    route = temp;

    cout << "Removed bus stop: " << name << endl;
}

void searchStop() {
    if (route.empty()) {
        cout << "No bus stops available!\n";
        return;
    }

    string name;
    bool found = false;
    int position = 1;

    cout << "Enter bus stop to search: ";
    getline(cin >> ws, name);

    queue<string> temp = route;

    while (!temp.empty()) {
        if (temp.front() == name) {
            cout << "Bus stop found at position "
                 << position << ".\n";
            found = true;
            break;
        }

        temp.pop();
        position++;
    }

    if (!found) {
        cout << "Bus stop not found!\n";
    }
}

void displayStops() {
    if (route.empty()) {
        cout << "No bus stops available!\n";
        return;
    }

    queue<string> temp = route;

    cout << "\nCollege Bus Route:\n";

    int position = 1;

    while (!temp.empty()) {
        cout << position << ". "
             << temp.front() << endl;

        temp.pop();
        position++;
    }
}

int main() {
    int choice;

    do {
        cout << "\n===== College Bus Stop Manager =====\n";
        cout << "1. Add Bus Stop\n";
        cout << "2. Remove Last Added Stop\n";
        cout << "3. Search Bus Stop\n";
        cout << "4. Display Bus Stops\n";
        cout << "5. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStop();
                break;

            case 2:
                removeStop();
                break;

            case 3:
                searchStop();
                break;

            case 4:
                displayStops();
                break;

            case 5:
                cout << "Exiting the program.\n";
                break;

            default:
                cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 5);

    return 0;
}
