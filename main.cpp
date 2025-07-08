#include "include/QuantumBookstore.h"
#include "include/QuantumBookstoreFullTest.h"
#include <iostream>

int main() {
    try {
        // Run all tests first
        QuantumBookstoreFullTest::runAllTests();
        
        std::cout << "\n=== Quantum Bookstore Demo ===" << std::endl;
        
        // Create a bookstore instance
        QuantumBookstore store;
        
        // Add different types of books
        auto paperBook1 = std::make_unique<PaperBook>("978-0134685991", 
            "Effective Modern C++", 2014, 45.99, "Scott Meyers", 10);
        
        auto paperBook2 = std::make_unique<PaperBook>("978-0321714114", 
            "C++ Primer", 2012, 59.99, "Stanley Lippman", 5);
        
        auto ebook = std::make_unique<EBook>("978-1035024957", 
            "Think Faster, Talk Smarter", 2023, 14.99, "Matt Abrahams", "PDF");
        
        auto showcaseBook = std::make_unique<ShowcaseBook>("978-9999999999", 
            "Demo Book", 2023, 0.0, "Demo Author");
        
        // Add books to inventory
        store.addBook(std::move(paperBook1));
        store.addBook(std::move(paperBook2));
        store.addBook(std::move(ebook));
        store.addBook(std::move(showcaseBook));
        
        // Display inventory
        store.printInventory();
        
        std::cout << "\n--- Purchase Examples ---" << std::endl;
        
        // Buy a paper book
        double amount1 = store.buyBook("978-0134685991", 2, 
            "test@test.com", "Cairo, Egypt");
        std::cout << "Amount paid: $" << amount1 << std::endl;
        
        // Buy an ebook
        double amount2 = store.buyBook("978-0321714114", 1, 
            "test2@test.com", "New Cairo, Egypt");
        std::cout << "Amount paid: $" << amount2 << std::endl;
        
        std::cout << "\n--- After Purchases ---" << std::endl;
        store.printInventory();
        
        std::cout << "\n--- Removing Outdated Books (>10 years from 2025) ---" << std::endl;
        auto outdatedBooks = store.removeOutdated(2025, 10);
        std::cout << "Removed " << outdatedBooks.size() << " outdated book(s)" << std::endl;
        
        std::cout << "\n--- Final Inventory ---" << std::endl;
        store.printInventory();
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
