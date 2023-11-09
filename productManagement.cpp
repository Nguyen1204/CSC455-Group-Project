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
    }

    std::cout << "Product with ID " << productID << " not found." << std::endl;
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
