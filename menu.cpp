#include "header.h"
#include "productManagement.cpp"
#include "customerService.cpp"
#include <iostream>
#include <vector>


//Another menu would could use (This was what I was using for my program
int main() {
    std::vector<Product> products;
    std::vector<Customer> customers;
    RewardSystem yourRewardSystemObject;
    while (true) {
        std::cout << "Product Management Menu:\n";
        std::cout << "1. Customer Registration\n";
        std::cout << "2. Customer Removal\n";
        std::cout << "3. Product Additon\n";
        std::cout << "4. Product Removal\n";
        std::cout << "5. Shopping\n";
        std::cout << "6. View Customer Using Customer ID\n";
        std::cout << "7. Redeem Rewards\n";
        std::cout << "8. Quit\n";
        std::cout << "Enter your choice (1-8): ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                registerCustomer(customers);
                break;

            case 2:
                return 0;
                break;

            case 3: 
            {
                addProduct(products);
                saveProductData(products);
                break;
            }

            case 4:
            {
                std::string productID;
                std::cout << "Enter product ID to remove: ";
                std::cin >> productID;
                removeProduct(products, productID);
                break;
            }

            case 5:
                return 0;
                break;

            case 6:
                return 0;

            case 7:
                redeemRewards(customers, yourRewardSystemObject);
                saveCustomerData(customers);
                break;

            case 8:
                return 0;

            default:
                std::cout << "Invalid choice. Please enter a valid option (1-8)." << std::endl;
        }
    }

    return 0;
}
