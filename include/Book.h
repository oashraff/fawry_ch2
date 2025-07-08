#pragma once
#include <string>
#include <memory>

// Abstract base class for all book types
class Book {
protected:
    std::string isbn;
    std::string title;
    int yearPublished;
    double price;
    std::string authorName;

public:
    Book(const std::string& isbn, const std::string& title, int year, 
         double price, const std::string& author);
    
    virtual ~Book() = default;
    
    // Pure virtual function to be implemented by derived classes
    virtual void processPurchase(const std::string& customerEmail, 
                               const std::string& shippingAddress) const = 0;
    
    virtual bool canBeSold() const = 0;
    virtual std::string getType() const = 0;
    
    // Getters
    const std::string& getISBN() const;
    const std::string& getTitle() const;
    int getYearPublished() const;
    double getPrice() const;
    const std::string& getAuthorName() const;
    
    bool isOutdated(int currentYear, int yearsThreshold) const;
};
