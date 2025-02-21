#include <iostream>

class IProductValidator {
public:
    virtual ~IProductValidator() = default;
    virtual bool IsValid(const int price) const = 0;
};


class Product {
public:
    int price;

    Product(int price) : price(price) {}

    bool IsValid(const IProductValidator& validator) const {
        return validator.IsValid(price);
    }
};


class BasicProductValidator : public IProductValidator {
public:
    bool IsValid(const int price) const override {
        return price > 0;
    }
};

class CustomerServiceProductValidator : public IProductValidator {
public:
    bool IsValid(const int price) const override {
        return price > 100000;
    }
};

int main() {
    Product product1(150000);
    Product product2(50000);

    BasicProductValidator basicValidator;
    CustomerServiceProductValidator customerServiceValidator;

    std::cout << "Product 1 is valid (basic): " << product1.IsValid(basicValidator) << std::endl;
    std::cout << "Product 1 is valid (customer service): " << product1.IsValid(customerServiceValidator) << std::endl;

    std::cout << "Product 2 is valid (basic): " << product2.IsValid(basicValidator) << std::endl;
    std::cout << "Product 2 is valid (customer service): " << product2.IsValid(customerServiceValidator) << std::endl;

    return 0;
}