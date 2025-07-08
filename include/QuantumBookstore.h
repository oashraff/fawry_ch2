#pragma once
#include "BookTypes.h"
#include <vector>
#include <memory>
#include <unordered_map>

class QuantumBookstore {
private:
    std::unordered_map<std::string, std::unique_ptr<Book>> inventory;
    static constexpr const char* PRINT_PREFIX = "Quantum book store";

public:
    QuantumBookstore() = default;
    ~QuantumBookstore() = default;
    
    // Delete copy constructor and assignment operator to prevent copying
    QuantumBookstore(const QuantumBookstore&) = delete;
    QuantumBookstore& operator=(const QuantumBookstore&) = delete;
    
    // Add a book to the inventory
    void addBook(std::unique_ptr<Book> book);
    
    // Remove and return outdated books
    std::vector<std::unique_ptr<Book>> removeOutdated(int currentYear, int yearsThreshold);
    
    // Buy a single book
    double buyBook(const std::string& isbn, int quantity, 
                   const std::string& customerEmail, 
                   const std::string& shippingAddress);
    
    // Utility methods
    void printInventory() const;
    size_t getInventorySize() const;
    Book* findBook(const std::string& isbn) const;
    
private:
    void printMessage(const std::string& message) const;
};
