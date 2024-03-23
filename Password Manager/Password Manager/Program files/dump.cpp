/*
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std;

size_t hashPassword(const string& password) {
    hash<string> hasher; // Create a hash function object for strings
    return hasher(password); // Compute the hash value of the password
}


// User class to represent user credentials
class User {
private:
    string username;
    size_t passwordHash; // Store hashed password

public:
    // Constructor
    User(const string& uname, const string& pwd) : username(uname), passwordHash(hashPassword(pwd)) {}

    // Getters
    string getUsername() const { return username; }
    size_t getPasswordHash() const { return passwordHash; }
    
};



// Function to write user information to a file
void writeUserToFile(const string& filename, const User& user) {
    ofstream file(filename, ios::app); // Open file in append mode
    if (file.is_open()) {
        file << user.getUsername() << "," << user.getPasswordHash() << endl; // Write user info to file
        file.close(); // Close the file
        cout << "User signed up successfully." << endl;
    } else {
        cout << "Error: Unable to open file for writing." << endl;
    }
}

// Function to check if a username already exists
bool usernameExists(const string& filename, const string& username) {
    ifstream file(filename); // Open file for reading
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            size_t pos = line.find(',');
            if (pos != string::npos) {
                string existingUsername = line.substr(0, pos);
                if (existingUsername == username) {
                    return true; // Username already exists
                }
            }
        }
        file.close(); // Close the file
    }
    return false; // Username does not exist
}

// Function to authenticate user
bool authenticateUser(const string& filename, const string& username, const string& password) {
    ifstream file(filename); // Open user credentials file for reading
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            size_t pos = line.find(',');
            if (pos != string::npos) {
                string existingUsername = line.substr(0, pos);
                size_t hashedPassword = stoul(line.substr(pos + 1)); // Convert hashed password string to size_t
                if (existingUsername == username && hashPassword(password) == hashedPassword) {
                    return true;// Compare hashed passwords
                }
            }
        }
        file.close(); // Close the file
    }
    return false; // User not found or incorrect password
}



// Function to write data to a file
void writeToFile(const string& filename, const string& username, const string& password, const string& website) {
    ofstream file(filename, ios::app); // Open file in append mode
    if (file.is_open()) {
        file << "Username: " << username << ", Password: " << password << ", Website: " << website << endl;
        file.close(); // Close the file
        cout << "Data written to file successfully." << endl;
    } else {
        cout << "Error: Unable to open file for writing." << endl;
    }
}

// Function to read data from a file
void readFromFile(const string& filename) {
    ifstream file(filename); // Open file for reading
    if (file.is_open()) {
        string line;
        cout << "Contents of file:" << endl;
        while (getline(file, line)) {
            cout << line << endl; // Print each line of the file
        }
        file.close(); // Close the file
    } else {
        cout << "Error: Unable to open file for reading." << endl;
    }
}

// Function to delete a file
void deleteFile(const string& filename) {
    if (remove(filename.c_str()) == 0) { // Remove file
        cout << "File deleted successfully." << endl;
    } else {
        cout << "Error: Unable to delete file." << endl;
    }
}


// Function to generate a random and strong password
string generateRandomPassword(int length = 18) { // Default length is 18
    // Define character sets for different types of characters
    string lowercaseChars = "abcdefghijklmnopqrstuvwxyz";
    string uppercaseChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string digitChars = "0123456789";
    string specialChars = "!@#$%^&*()-_+=<>?";

    string allChars = lowercaseChars + uppercaseChars + digitChars + specialChars;

    // Seed the random number generator
    srand(time(nullptr));

    string password;
    for (int i = 0; i < length; ++i) {
        // Generate a random index within the range of the combined character set
        int index = rand() % allChars.length();
        // Append the character at the random index to the password
        password += allChars[index];
    }

    return password;
}

int main() {
    string filename = "data.txt";
    string username = "users.txt";
    
    cout<< "welcome to your Passwrd Manager";
    char choice;
    
    while (true) {
        // Ask user for operation
        cout << "Choose operation:" << endl;
        cout << "1. Sign up" << endl;
        cout << "2. Log in" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        
        
        switch (choice) {
            case '1':
            {
                string username, password;
                cout << "Enter username: ";
                cin >> username;
                if (usernameExists(username, username)) {
                    cout << "Username already exists. Please choose a different username." << endl;
                    break;
                }
                cout << "Enter password: ";
                cin >> password;
                User newUser(username, password);
                writeUserToFile(username, newUser); // Write user info to file
                break;
            }
                
            case '2':
            {
                string username, password;
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;
                if (authenticateUser(username, username, password)) {
                    cout << "Login successful." << endl;
                    // Present password manager functionality
                    char managerChoice;
                    while (true) {
                        // Ask user for password manager operation
                        cout << "Choose password manager operation:" << endl;
                        cout << "1. Insert Password" << endl;
                        cout << "2. Read Password" << endl;
                        cout << "3. Delete Password" << endl;
                        cout << "4. Generate Password" << endl;
                        cout << "5. Log out" << endl;
                        cout << "Enter choice: ";
                        cin >> managerChoice;
                        
                        switch (managerChoice) {
                            case '1':
                            {   string username, password, website;
                                cout << "Enter username: ";
                                cin >> username;
                                cout << "Enter password: ";
                                cin >> password;
                                cout << "Enter website: ";
                                cin >> website;
                                writeToFile(filename, username, password, website); // Write data to file
                                break;
                            }
                            case '2':
                                readFromFile(filename);
                                break;
                                
                            case '3':
                                deleteFile(filename);
                                break;
                                
                            case '4':
                            {    string password = generateRandomPassword();
                                cout << "This is your Generated Password: " << password << endl;
                                break;
                            }
                            case '5':
                                cout << "Logged out successfully." << endl;
                                break;
                            default:
                                cout << "Invalid choice. Please try again." << endl;
                        }
                        
                        if (managerChoice == '5') {
                            break; // Break out of password manager loop if user logs out
                        }
                    }
                } else {
                    cout << "Invalid username or password. Please try again." << endl;
                }
                break;
            }
                
            case '3':
                return 0; // Exit program
            default:
                cout << "Invalid choice. Please try again." << endl;
                
        }
    }
    return 0;
}

        
 */
                
                
                
                
                


