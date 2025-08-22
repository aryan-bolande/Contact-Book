#include <bits/stdc++.h>
using namespace std;

struct Contact {
    string name;
    string phone;
    Contact* next;
};

Contact* head = nullptr;

// Function to insert contact in sorted order
void insertContact(string name, string phone) {
    Contact* newContact = new Contact{name, phone, nullptr};

    if (!head || head->name > name) {
        newContact->next = head;
        head = newContact;
        return;
    }

    Contact* current = head;
    while (current->next && current->next->name < name) {
        current = current->next;
    }
    newContact->next = current->next;
    current->next = newContact;
}

// Search contact by name
Contact* searchContact(string name) {
    Contact* current = head;
    while (current) {
        if (current->name == name)
            return current;
        current = current->next;
    }
    return nullptr;
}

// Update contact
bool updateContact(string name, string newPhone) {
    Contact* contact = searchContact(name);
    if (contact) {
        contact->phone = newPhone;
        return true;
    }
    return false;
}

// Delete contact
bool deleteContact(string name) {
    if (!head) return false;

    if (head->name == name) {
        Contact* temp = head;
        head = head->next;
        delete temp;
        return true;
    }

    Contact* current = head;
    while (current->next && current->next->name != name) {
        current = current->next;
    }

    if (current->next) {
        Contact* temp = current->next;
        current->next = current->next->next;
        delete temp;
        return true;
    }
    return false;
}

// Display all contacts
void displayContacts() {
    Contact* current = head;
    cout << "\n--- Contact List ---\n";
    while (current) {
        cout << current->name << " - " << current->phone << endl;
        current = current->next;
    }
}

// Save contacts to file
void saveToFile() {
    ofstream fout("contacts.txt");
    Contact* current = head;
    while (current) {
        fout << current->name << "," << current->phone << "\n";
        current = current->next;
    }
    fout.close();
}

// Load contacts from file
void loadFromFile() {
    ifstream fin("contacts.txt");
    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        string name, phone;
        getline(ss, name, ',');
        getline(ss, phone);
        insertContact(name, phone);
    }
    fin.close();
}

// Menu
void menu() {
    int choice;
    string name, phone;

    do {
        cout << "\n--- Contact Book Menu ---\n";
        cout << "1. Add Contact\n";
        cout << "2. Search Contact\n";
        cout << "3. Update Contact\n";
        cout << "4. Delete Contact\n";
        cout << "5. Display All Contacts\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            cout << "Enter name: ";
            getline(cin, name);
            cout << "Enter phone: ";
            getline(cin, phone);
            insertContact(name, phone);
            saveToFile();
            break;
        case 2:
            cout << "Enter name to search: ";
            getline(cin, name);
            {
                Contact* c = searchContact(name);
                if (c) cout << "Found: " << c->name << " - " << c->phone << endl;
                else cout << "Contact not found.\n";
            }
            break;
        case 3:
            cout << "Enter name to update: ";
            getline(cin, name);
            cout << "Enter new phone: ";
            getline(cin, phone);
            if (updateContact(name, phone)) {
                cout << "Contact updated.\n";
                saveToFile();
            } else {
                cout << "Contact not found.\n";
            }
            break;
        case 4:
            cout << "Enter name to delete: ";
            getline(cin, name);
            if (deleteContact(name)) {
                cout << "Contact deleted.\n";
                saveToFile();
            } else {
                cout << "Contact not found.\n";
            }
            break;
        case 5:
            displayContacts();
            break;
        case 6:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 6);
}

int main() {
    loadFromFile();
    menu();
    saveToFile();
    return 0;
}
