#pragma once
#include <string>

// Service interfaces for external dependencies
class ShippingService {
public:
    static void ship(const std::string& address);
};

class MailService {
public:
    static void sendEmail(const std::string& email);
};
