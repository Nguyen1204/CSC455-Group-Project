//productManagement.cpp

#include "header.h"
#include <iostream>
#include <fstream>
#include <regex>

bool isValidProductID(const std::string& productID, const std::vector<Product>& products) {
    if (productID.length() != 8 || productID.substr(0, 4) != "Prod" || !std::regex_match(productID.substr(4), std::regex("^[0-9]{5}$")))
    {
        return false;
    }


    for (const Product& product : products) 
    {
        if (product.productID == productID) 
        {
            return false;
        }
    }

    return true;
}

void saveProductData(const std::vector<Product>& products)
{
    std::ofstream productsFile("products.txt");
    if (productsFile.is_open())
    {
        for (const Product& product : products)
        {
            productsFile << product.productID << ","
                         << product.productName << ","
                         << product.productPrice << ","
                         << product.availableItems << "\n";
        }
        productsFile.close();
        std::cout << "Product data saved to 'products.txt'." << std::endl;
    }

    else 
    {
        std::cerr << "Could not open 'products.txt'" << std::endl;
    }
}
