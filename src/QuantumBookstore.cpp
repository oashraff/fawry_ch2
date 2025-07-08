#include "../include/QuantumBookstore.h"
#include <stdexcept>
#include <algorithm>
#include <iostream>

void QuantumBookstore::addBook(std::unique_ptr<Book> book) {
    if (!book) {
        throw std::invalid_argument("Cannot add null book to inventory");
    }
    
    std::string isbn = book->getISBN();
    if (inventory.find(isbn) != inventory.end()) {
        throw std::invalid_argument("Book with ISBN " + isbn + " already exists in inventory");
    }
    
    inventory[isbn] = std::move(book);
    printMessage("Added book with ISBN: " + isbn);
}

std::vector<std::unique_ptr<Book>> QuantumBookstore::removeOutdated(int currentYear, int yearsThreshold) {
    std::vector<std::unique_ptr<Book>> outdatedBooks;
    
    auto it = inventory.begin();
    while (it != inventory.end()) {
        if (it->second->isOutdated(currentYear, yearsThreshold)) {
            printMessage("Removing outdated book: " + it->second->getTitle() + 
                        " (ISBN: " + it->first + ")");
            outdatedBooks.push_back(std::move(it->second));
            it = inventory.erase(it);
        } else {
            ++it;
        }
    }
    
    return outdatedBooks;
}

double QuantumBookstore::buyBook(const std::string& isbn, int quantity, 
                                const std::string& customerEmail, 
                                const std::string& shippingAddress) {
    if (quantity <= 0) {
        throw std::invalid_argument("Quantity must be positive");
    }
    
    auto it = inventory.find(isbn);
    if (it == inventory.end()) {
        throw std::runtime_error("Book with ISBN " + isbn + " not found in inventory");
    }
    
    Book* book = it->second.get();
    
    if (!book->canBeSold()) {
        throw std::runtime_error("Book with ISBN " + isbn + " is not for sale");
    }
    
    // Check if it's a paper book and verify stock
    PaperBook* paperBook = dynamic_cast<PaperBook*>(book);
    if (paperBook) {
        if (!paperBook->hasEnoughStock(quantity)) {
            throw std::runtime_error("Insufficient stock for book with ISBN " + isbn + 
                                   ". Available: " + std::to_string(paperBook->getStock()) + 
                                   ", Requested: " + std::to_string(quantity));
        }
        paperBook->reduceStock(quantity);
    }
    
    // Process the purchase (shipping for paper books, email for ebooks)
    book->processPurchase(customerEmail, shippingAddress);
    
    double totalAmount = book->getPrice() * quantity;
    
    printMessage("Successfully sold " + std::to_string(quantity) + 
                " copy(ies) of '" + book->getTitle() + "' for $" + 
                std::to_string(totalAmount));
    
    return totalAmount;
}

void QuantumBookstore::printInventory() const {
    printMessage("Current Inventory:");
    for (const auto& pair : inventory) {
        const Book* book = pair.second.get();
        std::cout << "  ISBN: " << book->getISBN() 
                  << ", Title: " << book->getTitle()
                  << ", Author: " << book->getAuthorName()
                  << ", Year: " << book->getYearPublished()
                  << ", Price: $" << book->getPrice()
                  << ", Type: " << book->getType();
        
        // Show stock for paper books
        const PaperBook* paperBook = dynamic_cast<const PaperBook*>(book);
        if (paperBook) {
            std::cout << ", Stock: " << paperBook->getStock();
        }
        
        // Show file type for ebooks
        const EBook* ebook = dynamic_cast<const EBook*>(book);
        if (ebook) {
            std::cout << ", File Type: " << ebook->getFileType();
        }
        
        std::cout << std::endl;
    }
}

size_t QuantumBookstore::getInventorySize() const { 
    return inventory.size(); 
}

Book* QuantumBookstore::findBook(const std::string& isbn) const {
    auto it = inventory.find(isbn);
    return (it != inventory.end()) ? it->second.get() : nullptr;
}

void QuantumBookstore::printMessage(const std::string& message) const {
    std::cout << PRINT_PREFIX << ": " << message << std::endl;
}
