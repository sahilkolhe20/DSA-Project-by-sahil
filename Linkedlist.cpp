#include <iostream>
#include <string>
#include <limits>
using namespace std;

// Node for each bus stop
struct BusStop {
    int stopNumber;
    string name;
    BusStop* next;

    BusStop(int number, const string& stopName)
        : stopNumber(number), name(stopName), next(NULL) {}
};

class BusStopManager {
private:
    BusStop* head;

public:
    // Constructor
    BusStopManager() {
        head = NULL;
    }

    // Check whether stop number already exists
    bool stopExists(int number) const {
        BusStop* current = head;

        while (current != NULL) {
            if (current->stopNumber == number) {
                return true;
            }
            current = current->next;
        }

        return false;
    }

    // Add a bus stop at the end
    void addStop(int number, const string& name) {

        if (stopExists(number)) {
            cout << "Error: Stop number already exists.\n";
            return;
        }

        BusStop* newStop = new BusStop(number, name);

        if (head == NULL) {
            head = newStop;
        }
        else {
            BusStop* current = head;

            while (current->next != NULL) {
                current = current->next;
            }

            current->next = newStop;
        }

        cout << "Bus stop added successfully.\n";
    }

    // Remove a bus stop by stop number
    void removeStop(int number) {

        if (head == NULL) {
            cout << "No bus stops available.\n";
            return;
        }

        // Remove first node
        if (head->stopNumber == number) {
            BusStop* temp = head;
            head = head->next;

            delete temp;

            cout << "Bus stop removed successfully.\n";
            return;
        }

        BusStop* current = head;

        while (current->next != NULL &&
               current->next->stopNumber != number) {
            current = current->next;
        }

        // Stop not found
        if (current->next == NULL) {
            cout << "Bus stop not found.\n";
            return;
        }

        BusStop* temp = current->next;
        current->next = temp->next;

        delete temp;

        cout << "Bus stop removed successfully.\n";
    }

    // Search bus stop by name
    void searchStop(const string& name) const {

        if (head == NULL) {
            cout << "No bus stops available.\n";
            return;
        }

        BusStop* current = head;

        while (current != NULL) {

            if (current->name == name) {
                cout << "\nBus stop found!\n";
                cout << "Stop Number : " << current->stopNumber << endl;
                cout << "Stop Name   : " << current->name << endl;

                return;
            }

            current = current->next;
        }

        cout << "Bus stop not found.\n";
    }

    // Display all bus stops
    void displayStops() const {

        if (head == NULL) {
            cout << "No bus stops available.\n";
            return;
        }

        BusStop* current = head;

        cout << "\n===== College Bus Route =====\n";

        while (current != NULL) {

            cout << "Stop " << current->stopNumber
                 << " -> " << current->name << endl;

            current = current->next;
        }

        cout << "=============================\n";
    }

    // Destructor
    ~BusStopManager() {

        while (head != NULL) {

            BusStop* temp = head;
            head = head->next;

            delete temp;
        }
    }
};

int main() {

    BusStopManager manager;

    int choice;
    int stopNumber;
    string stopName;

    do {

        cout << "\n===== College Bus Stop Manager =====\n";
        cout << "1. Add Bus Stop\n";
        cout << "2. Remove Bus Stop\n";
        cout << "3. Search Bus Stop\n";
        cout << "4. Display Route\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";

        cin >> choice;

        // Invalid menu input
        if (cin.fail()) {

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {

            // Add bus stop
            case 1:

                cout << "Enter stop number: ";
                cin >> stopNumber;

                if (cin.fail()) {

                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    cout << "Invalid stop number.\n";
                    break;
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Enter stop name: ";
                getline(cin, stopName);

                if (stopName.empty()) {

                    cout << "Stop name cannot be empty.\n";
                    break;
                }

                manager.addStop(stopNumber, stopName);

                break;

            // Remove bus stop
            case 2:

                cout << "Enter stop number to remove: ";
                cin >> stopNumber;

                if (cin.fail()) {

                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    cout << "Invalid stop number.\n";
                    break;
                }

                manager.removeStop(stopNumber);

                break;

            // Search bus stop
            case 3:

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Enter stop name to search: ";
                getline(cin, stopName);

                if (stopName.empty()) {

                    cout << "Stop name cannot be empty.\n";
                    break;
                }

                manager.searchStop(stopName);

                break;

            // Display route
            case 4:

                manager.displayStops();

                break;

            // Exit
            case 5:

                cout << "Thank you for using College Bus Stop Manager!\n";

                break;

            default:

                cout << "Invalid choice. Please select 1 to 5.\n";
        }

    } while (choice != 5);

    return 0;
}
