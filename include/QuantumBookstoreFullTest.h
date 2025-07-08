#pragma once
#include "QuantumBookstore.h"

class QuantumBookstoreFullTest {
public:
    static void runAllTests();

private:
    static void testAddBook();
    static void testBuyPaperBook();
    static void testBuyEBook();
    static void testShowcaseBookNotForSale();
    static void testInsufficientStock();
    static void testRemoveOutdated();
    static void testDuplicateISBN();
    static void testBookNotFound();
    static void testInvalidQuantity();
};
