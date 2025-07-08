#pragma once
#include "Book.h"

// Forward declarations for services
class ShippingService;
class MailService;

// Paper book implementation
class PaperBook : public Book {
private:
    int stock;

public:
    PaperBook(const std::string& isbn, const std::string& title, int year,
              double price, const std::string& author, int stock);
    
    void processPurchase(const std::string& customerEmail, 
                        const std::string& shippingAddress) const override;
    
    bool canBeSold() const override;
    std::string getType() const override;
    
    int getStock() const;
    void reduceStock(int quantity);
    bool hasEnoughStock(int quantity) const;
};

// EBook implementation
class EBook : public Book {
private:
    std::string fileType;

public:
    EBook(const std::string& isbn, const std::string& title, int year,
          double price, const std::string& author, const std::string& fileType);
    
    void processPurchase(const std::string& customerEmail, 
                        const std::string& shippingAddress) const override;
    
    bool canBeSold() const override;
    std::string getType() const override;
    
    const std::string& getFileType() const;
};

// Showcase/Demo book implementation
class ShowcaseBook : public Book {
public:
    ShowcaseBook(const std::string& isbn, const std::string& title, int year,
                 double price, const std::string& author);
    
    void processPurchase(const std::string& customerEmail, 
                        const std::string& shippingAddress) const override;
    
    bool canBeSold() const override;
    std::string getType() const override;
};
