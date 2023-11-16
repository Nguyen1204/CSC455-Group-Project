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
    for (const Customer& customer : customer)
    {
        if (customer.creditCardNumber == creditCardNumber)
        {
            return false;
        }
    }
    return true;
}

bool isValidCreditCardFormat(const std::string& creditCardNumber)
{
    // Using a regular expression to check the format
    std::regex formatRegex(R"(\d{4}-\d{4}-\d{4})");
    return std::regex_match(creditCardNumber, formatRegex);
}

bool isValidCreditCard(const std::string& creditCardNumber, const std::vector<Customer>& customers) {
    // Check uniqueness
    if (!isUniqueCreditCard(creditCardNumber, customers))
    {
        std::cout << "Credit card number is not unique." << std::endl;
        return false;
    }

    // Check format
    if (!isValidCreditCardFormat(creditCardNumber))
    {
        std::cout << "Invalid credit card format." << std::endl;
        return false;
    }

    // Check for no leading 0
    if (creditCardNumber[0] == '0')
    {
        std::cout << "Credit card number cannot start with 0." << std::endl;
        return false;
    }

    // Check if each character after '-' is a digit
    for (size_t i = 5; i < creditCardNumber.length(); i += 5) {
        if (!isdigit(creditCardNumber[i]) || !isdigit(creditCardNumber[i + 1]) || !isdigit(creditCardNumber[i + 2]) || !isdigit(creditCardNumber[i + 3])) {
            std::cout << "Invalid character in credit card number." << std::endl;
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
        !std::regex_match(customer.lastName, std::regex("^[A-Za-z]+$")))
    {
        std::cout << "Invalid first name or last name. They must not exceed 12 characters and contain only letters." << std::endl;
        return false;
    }

    // Check age
    if (customer.age < 18 || customer.age > 100)
    {
        std::cout << "Invalid age. It must be between 18 and 100." << std::endl;
        return false;
    }

    // Check credit card
    if (!isValidCreditCard(customer.creditCardNumber, existingCustomers))
    {
        std::cout << "Invalid credit card number" << std::endl;
        return false;
    }

    // Check reward points
    if (customer.rewardPoints < 0)
    {
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
void registerCustomer(std::vector<Customer>& customers)
{
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
    if (validateCustomer(newCustomer, customers))
    {
        customers.push_back(newCustomer);

        // Append user information to the file
        std::ofstream customersFile("customers.txt", std::ios::app);
        if (customersFile.is_open())
        {
            customersFile << newCustomer.username << "\n"
                          << newCustomer.firstName << "\n"
                          << newCustomer.lastName << "\n"
                          << newCustomer.age << "\n"
                          << newCustomer.creditCardNumber << "\n"
                          << newCustomer.rewardPoints << "\n"
                          << newCustomer.userID << "\n\n";
            customersFile.close();
            std::cout << "Account created."<< std::endl;
        }
            
        else
        {
            std::cerr << "Failed to create account." << std::endl;
        }
    }
}

//Customer Removal Section

void removeCustomer(std::vector<Customer>& customers, const std::string& customerID)
{
    auto it = std::remove_if(customers.begin(), customers.end(), [customerID](const Customer& customer) {return customer.userID == customerID;});

    if (it != customers.end())
    {
        customers.erase(it, customers.end());
        std::cout << "Customer with ID " << customerID << " removed successfully." << std::endl;
    }

    else
    {
        std::cout << "Customer with ID " << customerID << " not found." << std::endl;
    }
}

void displayAllCustomers(const std::vector<Customer>& customers)
{
    std::cout << "List of all customers:" << std::endl;
    for (const Customer& customer : customers)
    {
        displayAllCustomers(customers);
    }
}

// Function to view customer details based on user ID
void viewCustomerByID(const std::vector<Customer>& customers, const std::string& userID) {
    auto it = std::find_if(customers.begin(), customers.end(),
                           [userID](const Customer& customer) { return customer.userID == userID; });

    if (it != customers.end()) {
        // Display customer details
        std::cout << "Customer Details for User ID: " << userID << "\n";
        std::cout << "Username: " << it->username << "\n";
        std::cout << "First Name: " << it->firstName << "\n";
        std::cout << "Last Name: " << it->lastName << "\n";
        std::cout << "Age: " << it->age << "\n";
        std::cout << "Credit Card Number: " << it->creditCardNumber << "\n";
        std::cout << "Reward Points: " << it->rewardPoints << "\n";

        // Add more details if needed

        std::cout << "--------------------------\n";
    } else {
        std::cout << "Customer with user ID " << userID << " not found." << std::endl;
    }
}
