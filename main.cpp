#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Hotel {
private:
    string name;
    string address;
    string phone;
    int roomNumber;
    int days;
    double costPerDay = 1000.0;

public:
    void bookRoom();
    void checkOut();
    void displayCustomer();
    void roomAvailability(int roomNum);
};

void Hotel::bookRoom() {
    ofstream file("records.txt", ios::app);

    cout << "\nEnter Customer Name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter Address: ";
    getline(cin, address);

    cout << "Enter Phone Number: ";
    cin >> phone;

    cout << "Enter Room Number to Book: ";
    cin >> roomNumber;

    roomAvailability(roomNumber);

    cout << "Enter Number of Days: ";
    cin >> days;

    file << name << "," << address << "," << phone << "," << roomNumber << "," << days << "\n";
    file.close();

    cout << "\nRoom successfully booked for " << days << " days.\n";
}

void Hotel::roomAvailability(int roomNum) {
    ifstream file("records.txt");
    string line;
    bool found = false;

    while (getline(file, line)) {
        size_t pos = line.find_last_of(',');
        int bookedRoom = stoi(line.substr(line.find_last_of(',', pos - 1) + 1, pos));
        if (bookedRoom == roomNum) {
            found = true;
            break;
        }
    }

    file.close();

    if (found) {
        cout << "❌ Room " << roomNum << " is already booked.\n";
        exit(0);
    } else {
        cout << "✅ Room " << roomNum << " is available.\n";
    }
}

void Hotel::checkOut() {
    ifstream inFile("records.txt");
    ofstream outFile("temp.txt");

    int roomToCheckout;
    bool found = false;
    string line;

    cout << "Enter Room Number to Check Out: ";
    cin >> roomToCheckout;

    while (getline(inFile, line)) {
        size_t lastComma = line.find_last_of(',');
        int room = stoi(line.substr(line.find_last_of(',', lastComma - 1) + 1, lastComma));

        if (room == roomToCheckout) {
            found = true;
            cout << "\nCustomer checked out. Billing details:\n";
            size_t firstComma = line.find(',');
            string customerName = line.substr(0, firstComma);
            int stayDays = stoi(line.substr(lastComma + 1));

            double bill = stayDays * costPerDay;
            cout << "Name: " << customerName << "\nTotal Bill: ₹" << bill << "\n";
        } else {
            outFile << line << "\n";
        }
    }

    inFile.close();
    outFile.close();

    remove("records.txt");
    rename("temp.txt", "records.txt");

    if (!found) {
        cout << "No booking found for Room " << roomToCheckout << "\n";
    }
}

void Hotel::displayCustomer() {
    ifstream file("records.txt");
    string line;

    cout << "\n📋 List of Customers:\n";
    while (getline(file, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        size_t pos3 = line.find(',', pos2 + 1);
        size_t pos4 = line.find(',', pos3 + 1);

        cout << "Name: " << line.substr(0, pos1)
             << ", Address: " << line.substr(pos1 + 1, pos2 - pos1 - 1)
             << ", Phone: " << line.substr(pos2 + 1, pos3 - pos2 - 1)
             << ", Room: " << line.substr(pos3 + 1, pos4 - pos3 - 1)
             << ", Days: " << line.substr(pos4 + 1)
             << "\n";
    }

    file.close();
}

int main() {
    Hotel h;
    int choice;

    do {
        cout << "\n==== Hotel Management System ====\n";
        cout << "1. Book a Room\n";
        cout << "2. Check-Out\n";
        cout << "3. Display All Customers\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                h.bookRoom();
                break;
            case 2:
                h.checkOut();
                break;
            case 3:
                h.displayCustomer();
                break;
            case 4:
                cout << "Exiting the system. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 4);

    return 0;
}
