#include "header.h"
#include <iostream>
using namespace std;

void showMenu() {
    cout << "Menu Options:" << endl;
    cout << "1. Customer registration" << endl;
    cout << "2. Customer Removal" << endl;
    cout << "3. Product addition" << endl;
    cout << "4. Product removal" << endl;
    cout << "5. Shopping" << endl;
    cout << "6. View customer using customer ID" << endl;
    cout << "7. Redeem rewards" << endl;
    cout << "8. Quit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    int choice;
    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Customer registration selected." << endl;
                break;
            case 2:
                cout << "Customer Removal selected." << endl;
                break;
            case 3:
                cout << "Product addition selected." << endl;
                break;
            case 4:
                cout << "Product removal selected." << endl;
                break;
            case 5:
                cout << "Shopping selected." << endl;
                break;
            case 6:
                cout << "View customer using customer ID selected." << endl;
                break;
            case 7:
                cout << "Redeem rewards selected." << endl;
                break;
            case 8:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != 8);

    return 0;
}