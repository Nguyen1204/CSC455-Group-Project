//productManagement.cpp

#include "header.h"
#include <regex>
#include <fstream>
#include <iostream>

// Function to check if a string represents a valid product ID
bool isValidProductID(const std::string& productID, const std::vector<Product>& products)
{
    // Check if it starts with 'Prod' and is followed by a five-digit number
    if (productID.length() != 9 || productID.substr(0, 4) != "Prod" || !std::regex_match(productID.substr(4), std::regex("^[0-9]{5}$")))
    {
        return false;
    }

    // Check if it's unique
    for (const Product& product : products) 
    {
        if (product.productID == productID) 
        {
            return false;
        }
    }

    return true;
}

// Function to add a new product
void addProduct(std::vector<Product>& products)
{
    Product newProduct;
    std::cout << "Enter product ID (e.g., 'Prod00001'): ";
    std::cin >> newProduct.productID;

    if (!isValidProductID(newProduct.productID, products))
    {
        std::cout << "Invalid product ID. It must start with 'Prod' followed by a five-digit number, and it must be unique." << std::endl;
        return;
    }

    std::cout << "Enter product name: ";
    std::cin >> newProduct.productName;

    std::cout << "Enter product price: ";
    std::cin >> newProduct.productPrice;

    std::cout << "Enter the number of available items: ";
    std::cin >> newProduct.availableItems;

    if (newProduct.availableItems <= 0)
    {
        std::cout << "Invalid number of available items. It must be a positive number." << std::endl;
        return;
    }

    products.push_back(newProduct);

    std::cout << "Product added to inventory." << std::endl;
}

void removeProduct(std::vector<Product>& products, const std::string& productID) 
{
    for (auto it = products.begin(); it != products.end(); ++it) 
    {
        if (it->productID == productID)
        {
            products.erase(it);
            std::cout << "Product removed from inventory." << std::endl;
            return;
        }

        else
        {
            std::cout << "Product with ID " << productID << " not found." << std::endl;
        }
    }
}

void listProducts(const std::vector<Product>& products) 
{
    std::cout << "List of Products in Inventory:\n";
    for (const Product& product : products) 
    {
        std::cout << "Product ID: " << product.productID << std::endl;
        std::cout << "Product Name: " << product.productName << std::endl;
        std::cout << "Product Price: $" << product.productPrice << std::endl;
        std::cout << "Available Items: " << product.availableItems << std::endl;
        std::cout << "--------------------------\n";
    }
}

void saveProductData(const std::vector<Product>& products)
{
    std::ofstream productsFile("products.txt");
    if (productsFile.is_open())
    {
        for (const Product& product : products)
        {
            productsFile << product.productID << "\n"
                         << product.productName << "\n"
                         << product.productPrice << "\n"
                         << product.availableItems << "\n\n";
        }
        productsFile.close();
        std::cout << "Product data saved to 'products.txt'." << std::endl;
    } 

    else 
    {
        std::cerr << "Failed to open 'products.txt'" << std::endl;
    }
}

// Function to calculate the total reward points based on the total amount
int calculateRewardPoints(double totalAmount)
{
    //1 reward point for every $10 spent
    return static_cast<int>(totalAmount / 10);
}

// Function to record a transaction
void recordTransaction(const std::string& transactionID, const Customer& customer, const std::vector<Product>& purchasedProducts)
{
    std::ofstream transactionsFile("transactions.txt", std::ios::app);

    if (!transactionsFile.is_open())
    {
        std::cerr << "Error: Failed to open 'transactions.txt' for recording the transaction." << std::endl;
        return;
    }

    // Write the transaction data to the file
    transactionsFile << "Transaction ID: " << transactionID << "\n"
                     << "User ID: " << customer.userID << "\n";

    // Write product IDs
    transactionsFile << "Product IDs: ";
    for (const Product& product : purchasedProducts)
    {
        transactionsFile << product.productID << ", ";
    }
    transactionsFile << "\n";

    // Calculate and write the total amount
    double totalAmount = 0.0;
    for (const Product& product : purchasedProducts)
    {
        totalAmount += product.productPrice;
    }
    transactionsFile << "Total amount: $" << totalAmount << "\n";

    // Calculate and write the total reward points
    int totalRewardPoints = calculateRewardPoints(totalAmount);
    transactionsFile << "Total reward points: " << totalRewardPoints << "\n";

    transactionsFile << "--------------------------\n";

    transactionsFile.close();
    std::cout << "Transaction recorded." << std::endl;
}

//Shopping Functionallity

void shoppingTransaction(std::vector<Product>& products)
{
    // Load product data
    loadProductData(products);

    // Display available products
    std::cout << "Available Products:" << std::endl;
    for (const Product& product : products) {
        std::cout << "ID: " << product.productID << ", Name: " << product.productName
                  << ", Price: $" << product.productPrice << ", Available: " << product.availableItems << std::endl;
    }

    // Get user input for the product ID and quantity
    std::string productID;
    int quantity;
    std::cout << "Enter the product ID you want to purchase: ";
    std::cin >> productID;
    std::cout << "Enter the quantity you want to purchase: ";
    std::cin >> quantity;

    // Find the product with the specified ID
    auto it = std::find_if(products.begin(), products.end(),
                           [productID](const Product& product) { return product.productID == productID; });

    if (it != products.end()) {
        // Check if there is enough supply
        if (it->availableItems >= quantity) {
            // Record the transaction
            std::ofstream transactionsFile("transactions.txt", std::ios::app);
            if (transactionsFile.is_open()) {
                transactionsFile << "Product ID: " << it->productID << "\n";
                transactionsFile << "Product Name: " << it->productName << "\n";
                transactionsFile << "Quantity Purchased: " << quantity << "\n";
                transactionsFile << "Total Price: $" << (it->productPrice * quantity) << "\n";
                transactionsFile << "--------------------------\n";
                transactionsFile.close();

                // Update product availability
                it->availableItems -= quantity;

                // Save the updated product data
                saveProductData(products);

                std::cout << "Transaction recorded successfully." << std::endl;
            } else {
                std::cerr << "Failed to open 'transactions.txt' for writing." << std::endl;
            }
        } else {
            std::cout << "Insufficient supply for the specified quantity." << std::endl;
        }
    } else {
        std::cout << "Product with ID " << productID << " not found." << std::endl;
    }
}

void loadProductData(std::vector<Product>& products)
{
    std::ifstream productsFile("products.txt");
    if (productsFile.is_open())
    {
        while (!productsFile.eof())
        {
            Product product;
            std::getline(productsFile, product.productID);
            std::getline(productsFile, product.productName);
            productsFile >> product.productPrice;
            productsFile >> product.availableItems;
            productsFile.ignore(); // Ignore the newline character

            products.push_back(product);
        }
        productsFile.close();
    }
    
    else
    {
        std::cerr << "Failed to open 'products.txt' for reading." << std::endl;
    }
}
