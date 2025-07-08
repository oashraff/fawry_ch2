#include "../include/BookTypes.h"
#include "../include/Services.h"
#include <stdexcept>

// PaperBook implementation
PaperBook::PaperBook(const std::string& isbn, const std::string& title, int year,
                     double price, const std::string& author, int stock)
    : Book(isbn, title, year, price, author), stock(stock) {}

void PaperBook::processPurchase(const std::string& customerEmail, 
                               const std::string& shippingAddress) const {
    ShippingService::ship(shippingAddress);
}

bool PaperBook::canBeSold() const { 
    return true; 
}

std::string PaperBook::getType() const { 
    return "Paper Book"; 
}

int PaperBook::getStock() const { 
    return stock; 
}

void PaperBook::reduceStock(int quantity) { 
    stock -= quantity; 
}

bool PaperBook::hasEnoughStock(int quantity) const { 
    return stock >= quantity; 
}

// EBook implementation
EBook::EBook(const std::string& isbn, const std::string& title, int year,
             double price, const std::string& author, const std::string& fileType)
    : Book(isbn, title, year, price, author), fileType(fileType) {}

void EBook::processPurchase(const std::string& customerEmail, 
                           const std::string& shippingAddress) const {
    MailService::sendEmail(customerEmail);
}

bool EBook::canBeSold() const { 
    return true; 
}

std::string EBook::getType() const { 
    return "EBook"; 
}

const std::string& EBook::getFileType() const { 
    return fileType; 
}

// ShowcaseBook implementation
ShowcaseBook::ShowcaseBook(const std::string& isbn, const std::string& title, int year,
                           double price, const std::string& author)
    : Book(isbn, title, year, price, author) {}

void ShowcaseBook::processPurchase(const std::string& customerEmail, 
                                  const std::string& shippingAddress) const {
    throw std::runtime_error("Showcase/Demo books are not for sale");
}

bool ShowcaseBook::canBeSold() const { 
    return false; 
}

std::string ShowcaseBook::getType() const { 
    return "Showcase/Demo Book"; 
}
