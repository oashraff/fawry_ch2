#include "../include/QuantumBookstoreFullTest.h"
#include <cassert>
#include <iostream>
#include <vector>

void QuantumBookstoreFullTest::runAllTests() {
    std::cout << "=== Running Quantum Bookstore Full Tests ===" << std::endl;
    
    testAddBook();
    testBuyPaperBook();
    testBuyEBook();
    testShowcaseBookNotForSale();
    testInsufficientStock();
    testRemoveOutdated();
    testDuplicateISBN();
    testBookNotFound();
    testInvalidQuantity();
    
    std::cout << "=== All tests passed! ===" << std::endl;
}

void QuantumBookstoreFullTest::testAddBook() {
    std::cout << "Testing addBook functionality..." << std::endl;
    QuantumBookstore store;
    
    auto paperBook = std::make_unique<PaperBook>("978-0134685991", 
        "Effective Modern C++", 2014, 45.99, "Scott Meyers", 10);
    
    store.addBook(std::move(paperBook));
    assert(store.getInventorySize() == 1);
    
    Book* foundBook = store.findBook("978-0134685991");
    assert(foundBook != nullptr);
    assert(foundBook->getTitle() == "Effective Modern C++");
    
    std::cout << "✓ addBook test passed" << std::endl;
}

void QuantumBookstoreFullTest::testBuyPaperBook() {
    std::cout << "Testing buying paper book..." << std::endl;
    QuantumBookstore store;
    
    auto paperBook = std::make_unique<PaperBook>("978-0134685991", 
        "Effective Modern C++", 2014, 45.99, "Scott Meyers", 10);
    
    store.addBook(std::move(paperBook));
    
    double paidAmount = store.buyBook("978-0134685991", 2, 
        "oomaraashrafaabdou@gmail.com", "New Cairo, Cairo, Egypt");
    
    assert(std::abs(paidAmount - 91.98) < 0.01); // 45.99 * 2
    
    PaperBook* book = dynamic_cast<PaperBook*>(store.findBook("978-0134685991"));
    assert(book->getStock() == 8); // 10 - 2
    
    std::cout << "✓ buyPaperBook test passed" << std::endl;
}

void QuantumBookstoreFullTest::testBuyEBook() {
    std::cout << "Testing buying EBook..." << std::endl;
    QuantumBookstore store;
    
    auto ebook = std::make_unique<EBook>("978-1035024957", 
        "Think Faster, Talk Smarter", 2023, 14.99, "Matt Abrahams", "PDF");
    
    store.addBook(std::move(ebook));
    
    double paidAmount = store.buyBook("978-1035024957", 1, 
        "test@test.com", "Cairo, Egypt");
    
    assert(std::abs(paidAmount - 14.99) < 0.01);
    
    std::cout << "✓ buyEBook test passed" << std::endl;
}

void QuantumBookstoreFullTest::testShowcaseBookNotForSale() {
    std::cout << "Testing showcase book not for sale..." << std::endl;
    QuantumBookstore store;
    
    auto showcaseBook = std::make_unique<ShowcaseBook>("978-9999999999", 
        "Demo Book", 2023, 0.0, "Demo Author");
    
    store.addBook(std::move(showcaseBook));
    
    try {
        store.buyBook("978-9999999999", 1, "test@test.com", "Cairo, Egypt");
        assert(false); // Should not reach here
    } catch (const std::runtime_error& e) {
        // Expected exception
    }
    
    std::cout << "✓ showcaseBookNotForSale test passed" << std::endl;
}

void QuantumBookstoreFullTest::testInsufficientStock() {
    std::cout << "Testing insufficient stock error..." << std::endl;
    QuantumBookstore store;
    
    auto paperBook = std::make_unique<PaperBook>("978-0134685991", 
        "Effective Modern C++", 2014, 45.99, "Scott Meyers", 2);
    
    store.addBook(std::move(paperBook));
    
    try {
        store.buyBook("978-0134685991", 5, "test@test.com", "Cairo, Egypt");
        assert(false); // Should not reach here
    } catch (const std::runtime_error& e) {
        // Expected exception
    }
    
    std::cout << "✓ insufficientStock test passed" << std::endl;
}

void QuantumBookstoreFullTest::testRemoveOutdated() {
    std::cout << "Testing remove outdated books..." << std::endl;
    QuantumBookstore store;
    
    // Add books from different years
    auto oldBook = std::make_unique<PaperBook>("978-1111111111", 
        "Old Book", 2000, 25.99, "Old Author", 5);
    auto newBook = std::make_unique<PaperBook>("978-2222222222", 
        "New Book", 2020, 55.99, "New Author", 10);
    
    store.addBook(std::move(oldBook));
    store.addBook(std::move(newBook));
    
    assert(store.getInventorySize() == 2);
    
    // Remove books older than 20 years (from 2025)
    auto outdatedBooks = store.removeOutdated(2025, 20);
    
    assert(outdatedBooks.size() == 1);
    assert(store.getInventorySize() == 1);
    assert(outdatedBooks[0]->getTitle() == "Old Book");
    
    std::cout << "✓ removeOutdated test passed" << std::endl;
}

void QuantumBookstoreFullTest::testDuplicateISBN() {
    std::cout << "Testing duplicate ISBN error..." << std::endl;
    QuantumBookstore store;
    
    auto book1 = std::make_unique<PaperBook>("978-0134685991", 
        "Book 1", 2014, 45.99, "Author 1", 10);
    auto book2 = std::make_unique<PaperBook>("978-0134685991", 
        "Book 2", 2015, 35.99, "Author 2", 5);
    
    store.addBook(std::move(book1));
    
    try {
        store.addBook(std::move(book2));
        assert(false); // Should not reach here
    } catch (const std::invalid_argument& e) {
        // Expected exception
    }
    
    std::cout << "✓ duplicateISBN test passed" << std::endl;
}

void QuantumBookstoreFullTest::testBookNotFound() {
    std::cout << "Testing book not found error..." << std::endl;
    QuantumBookstore store;
    
    try {
        store.buyBook("978-9999999999", 1, "test@test.com", "Cairo, Egypt");
        assert(false); // Should not reach here
    } catch (const std::runtime_error& e) {
        // Expected exception
    }
    
    std::cout << "✓ bookNotFound test passed" << std::endl;
}

void QuantumBookstoreFullTest::testInvalidQuantity() {
    std::cout << "Testing invalid quantity error..." << std::endl;
    QuantumBookstore store;
    
    auto paperBook = std::make_unique<PaperBook>("978-0134685991", 
        "Effective Modern C++", 2014, 45.99, "Scott Meyers", 10);
    
    store.addBook(std::move(paperBook));
    
    try {
        store.buyBook("978-0134685991", 0, "test@test.com", "Cairo, Egypt");
        assert(false); // Should not reach here
    } catch (const std::invalid_argument& e) {
        // Expected exception
    }
    
    try {
        store.buyBook("978-0134685991", -1, "test@test.com", "Cairo, Egypt");
        assert(false); // Should not reach here
    } catch (const std::invalid_argument& e) {
        // Expected exception
    }
    
    std::cout << "✓ invalidQuantity test passed" << std::endl;
}
