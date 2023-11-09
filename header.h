/* Phuc Nguyen
Nicolas Duong
Sean Gascon */

//header.h
#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <vector>

struct Product
{
    std::string productID;
    std::string productName;
    double productPrice;
    int availableItems;
};

bool isValidProductID(const std::string& productID, const std::vector<Product>& products);

void saveProductData(const std::vector<Product>& products);

#endif
