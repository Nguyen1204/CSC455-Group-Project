#include <iostream>
#include "header.h"
void showMenu() {
    std::cout << "Menu Options:" << std::endl;
    std::cout << "1. Customer registration" << std::endl;
    std::cout << "2. Customer Removal" << std::endl;
    std::cout << "3. Product addition" << std::endl;
    std::cout << "4. Product removal" << std::endl;
    std::cout << "5. Shopping" << std::endl;
    std::cout << "6. View customer using customer ID" << std::endl;
    std::cout << "7. Redeem rewards" << std::endl;
    std::cout << "8. Quit" << std::endl;
    std::cout << "Enter your choice: ";
}

int main() {
    int choice;
    do {
        showMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Customer registration selected." << std::endl;
                break;
            case 2:
                std::cout << "Customer Removal selected." << std::endl;
                break;
            case 3:
                std::cout << "Product addition selected." << std::endl;
                break;
            case 4:
                std::cout << "Product removal selected." << std::endl;
                break;
            case 5:
                std::cout << "Shopping selected." << std::endl;
                break;
            case 6:
                std::cout << "View customer using customer ID selected." << std::endl;
                break;
            case 7:
                std::cout << "Redeem rewards selected." << std::endl;
                break;
            case 8:
                std::cout << "Exiting..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }

    } while (choice != 8);

    std::vector<Product> products;

    while (true) {
        std::cout << "Product Management Menu:\n";
        std::cout << "1. Add Product\n";
        std::cout << "2. Remove Product\n";
        std::cout << "3. List Products\n";
        std::cout << "4. Save Products\n";
        std::cout << "5. Quit\n";
        std::cout << "Enter your choice (1-5): ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                addProduct(products);
                break;

            case 2: {
                std::string productID;
                std::cout << "Enter product ID to remove: ";
                std::cin >> productID;
                removeProduct(products, productID);
                break;
            }

            case 3:
                listProducts(products);
                break;

            case 4:
                saveProductData(products);
                break;

            case 5:
                return 0;

            default:
                std::cout << "Invalid choice. Please enter a valid option (1-4)." << std::endl;
        }
    }

    return 0;
}
