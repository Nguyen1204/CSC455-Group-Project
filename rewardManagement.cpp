//rewardManagement.cpp

#include "header.h"
#include <vector>
#include <fstream>
#include <iostream>

void RewardSystem::setPointsPerAmount(int points) {
    pointsPerAmount = points;
}

void RewardSystem::addGift(int pointsRequired, const std::string& giftName) {
    gifts.push_back(std::make_pair(pointsRequired, giftName));
}

void RewardSystem::displayGifts() const {
    std::cout << "Available gifts:" << std::endl;
    for (const auto& gift : gifts) {
        std::cout << "Points required: " << gift.first << ", Gift: " << gift.second << std::endl;
    }
}

std::string RewardSystem::redeemGift(int totalPoints) const {
    for (const auto& gift : gifts) {
        if (totalPoints >= gift.first) {
            return gift.second;
        } else {
            continue; // Continue the loop to check the next gift
        }
    }
    return "No gift available for the given points.";
}

// Function to record a transaction
void recordTransaction(const Customer& customer, const std::vector<Product>& purchasedProducts)
{
    std::ofstream transactionsFile("transactions.txt", std::ios::app);

    if (transactionsFile.is_open())
    {
        // Write the transaction data to the file
        transactionsFile << "Transaction ID: " << customer.userID << "\n"
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
    else
    {
        std::cerr << "Failed to open 'transactions.txt' for recording the transaction." << std::endl;
    }
}
