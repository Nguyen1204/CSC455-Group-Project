//customerService.cpp

#include "header.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <regex>
#include <ctime>
#include <set>
#include <cctype>
#include <string>
using namespace std;

int numDigits = 0;

bool isUniqueCreditCard(const std::string& creditCardNumber, const std::vector<Customer>& customer)
{
    for (const Customer& customer : customer) {
        if (customer.creditCardNumber == creditCardNumber) {
            return false;
        }
    }
    return true;
}

// Function to validate a user's information
bool validateCustomer(const Customer& customer, const std::vector<Customer>& existingCustomers) {
    // Check username
    if (customer.username.length() < 10) 
    {
        std::cout << "Invalid username. It must be at least 10 characters" << std::endl;
        return false;
    }

    else
    {
        for(char c : customer.username) 
        {
            if(std::isdigit(c))
            {
                numDigits++;
            }
        }

        if (numDigits > 3)
        {
            std::cout << ("Username cannot contain more than 3 numbers.") << std::endl;
            return false;
        }
    }

    // Check names
    if (customer.firstName.length() > 12 || customer.lastName.length() > 12 ||
        !std::regex_match(customer.firstName, std::regex("^[A-Za-z]+$")) ||
        !std::regex_match(customer.lastName, std::regex("^[A-Za-z]+$"))) {
        std::cout << "Invalid first name or last name. They must not exceed 12 characters and contain only letters." << std::endl;
        return false;
    }

    // Check age
    if (customer.age < 18 || customer.age > 100) {
        std::cout << "Invalid age. It must be between 18 and 100." << std::endl;
        return false;
    }

    // Check credit card
    if (!std::regex_match(customer.creditCardNumber, std::regex("^[1-9][0-9]{2}-[0-9]{4}-[0-9]{4}$"))) {
        std::cout << "Invalid credit card number. It should not start with 0 and have the format xxxx-xxxx-xxxx." << std::endl;
        return false;
    }

    else
    {
        if(customer.creditCardNumber[0]=='0')
        {
            std::cout << "Credit card number cannot start with 0" << std::endl;
            return false;
        }

        if(!isUniqueCreditCard(customer.creditCardNumber, customer))
        {
            std::cout << "Credit card number is not unique" << std::endl;
            return false;
        }
    }

    // Check reward points
    if (customer.rewardPoints < 0) {
        std::cout << "Invalid reward points. They should be positive." << std::endl;
        return false;
    }

    // Check for existing user IDs
    for (const Customer& existingCustomer : existingCustomers) {
        if (customer.userID == existingCustomer.userID) {
            std::cout << "User ID collision. Please try again." << std::endl;
            return false;
        }
    }

    return true;
}

// Function to create an account and append user information to the file
void registerCustomer(std::vector<Customer>& customers) {
    Customer newCustomer;

    // Collect user information
    std::cout << "Enter your unique username (Must be 10 characters long followed by no more than 3 digits): ";
    std::cin >> newCustomer.username;

    std::cout << "Enter first name (No special characters): ";
    std::cin >> newCustomer.firstName;

    std::cout << "Enter last name (No special characters): ";
    std::cin >> newCustomer.lastName;

    std::cout << "Enter age (Between 18 and 100): ";
    std::cin >> newCustomer.age;

    std::cout << "Enter credit card number (xxxx-xxxx-xxxx): ";
    std::cin >> newCustomer.creditCardNumber;

    std::cout << "Enter reward points: ";
    std::cin >> newCustomer.rewardPoints;

    // Generate a unique user ID (based on current time)
    time_t currentTime;
    time(&currentTime);
    newCustomer.userID = std::to_string(currentTime);

    // Validate the customer's information
    if (validateCustomer(newCustomer, customers)) {
        customers.push_back(newCustomer);

        // Append user information to the file
        std::ofstream customersFile("customers.txt", std::ios::app);
        if (customersFile.is_open()) {
            customersFile << newCustomer.username << "\n"
                          << newCustomer.firstName << "\n"
                          << newCustomer.lastName << "\n"
                          << newCustomer.age << "\n"
                          << newCustomer.creditCardNumber << "\n"
                          << newCustomer.rewardPoints << "\n"
                          << newCustomer.userID << "\n\n";
            customersFile.close();
            std::cout << "Account created."<< std::endl;
        } else {
            std::cerr << "Failed to create account." << std::endl;
        }
    }
}
