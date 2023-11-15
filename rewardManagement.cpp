//rewardManagement.cpp

#include "header.h"

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
        }
    }
    return "No gift available for the given points.";
}

