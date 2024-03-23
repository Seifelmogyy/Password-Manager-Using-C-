//
//  Testing.cpp
//  m
//
//  Created by Seif elmougy on 23/03/2024.
//

#include <iostream>
#include "main.cpp"

void testHashPassword() {
    // Test cases: password -> expected hash value
    std::vector<std::pair<std::string, size_t>> testCases = {
        {"password123", 123456789}, // Replace with expected hash value
        // Add more test cases as needed
    };

    // Perform tests
    for (const auto& testCase : testCases) {
        const std::string& password = testCase.first;
        size_t expectedHash = testCase.second;

        // Call the function under test
        size_t actualHash = hashPassword(password);

        // Check if the actual hash matches the expected hash
        if (actualHash == expectedHash) {
            std::cout << "Test passed for password: " << password << std::endl;
        } else {
            std::cerr << "Test failed for password: " << password << std::endl;
            std::cerr << "Expected hash: " << expectedHash << ", Actual hash: " << actualHash << std::endl;
        }
    }
}

// Add more test functions for other functions to be tested

int Main() {
    // Run the tests
    testHashPassword();

    // Call other test functions here

    return 0;
}
