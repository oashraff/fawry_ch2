#include "../include/Book.h"

Book::Book(const std::string& isbn, const std::string& title, int year, 
           double price, const std::string& author)
    : isbn(isbn), title(title), yearPublished(year), price(price), authorName(author) {}

const std::string& Book::getISBN() const { 
    return isbn; 
}

const std::string& Book::getTitle() const { 
    return title; 
}

int Book::getYearPublished() const { 
    return yearPublished; 
}

double Book::getPrice() const { 
    return price; 
}

const std::string& Book::getAuthorName() const { 
    return authorName; 
}

bool Book::isOutdated(int currentYear, int yearsThreshold) const {
    return (currentYear - yearPublished) > yearsThreshold;
}
