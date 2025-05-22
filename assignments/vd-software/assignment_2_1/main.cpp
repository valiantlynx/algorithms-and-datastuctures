#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include "rapidcsv.h" // Include the RapidCSV header

struct Customer {
    int id;
    std::string name;
    std::string address;
};

struct Product {
    int id;
    std::string name;
    double price;
};

struct Order {
    int id;
    int customerId;
    int productId;
    int amount;
};

std::string trimQuotes(const std::string& str) {
    std::string result = str;
    if (!result.empty() && result.front() == '"')
        result.erase(0, 1);
    if (!result.empty() && result.back() == '"')
        result.pop_back();
    return result;
}

int main() {
    try {
        // Read customers.csv 
        rapidcsv::Document customersDoc("customers.csv", rapidcsv::LabelParams(0, -1));
        std::vector<Customer> customers;
        
        for (size_t i = 0; i < customersDoc.GetRowCount(); ++i) {
            Customer customer;
            customer.id = customersDoc.GetCell<int>(0, i);
            customer.name = customersDoc.GetCell<std::string>(1, i);
            customer.address = customersDoc.GetCell<std::string>(2, i);
            customers.push_back(customer);
            
            std::cout << "Customer: " << customer.name << ", " << customer.address << std::endl;
        }
        
        // Read products.csv 
        rapidcsv::Document productsDoc("products.csv", rapidcsv::LabelParams(0, -1));
        std::vector<Product> products;
        std::map<int, Product> productMap;
        
        for (size_t i = 0; i < productsDoc.GetRowCount(); ++i) {
            Product product;
            product.id = productsDoc.GetCell<int>(0, i);
            product.name = productsDoc.GetCell<std::string>(1, i);
            product.price = productsDoc.GetCell<double>(2, i);
            products.push_back(product);
            productMap[product.id] = product;
            
            std::cout << "Product: " << product.name << ", " << product.price << std::endl;
        }
        
        // Read orders.csv
        rapidcsv::Document ordersDoc("orders.csv", rapidcsv::LabelParams(0, -1));
        std::vector<Order> orders;
        
        for (size_t i = 0; i < ordersDoc.GetRowCount(); ++i) {
            Order order;
            order.id = ordersDoc.GetCell<int>(0, i);
            order.customerId = ordersDoc.GetCell<int>(1, i);
            order.productId = ordersDoc.GetCell<int>(2, i);
            order.amount = ordersDoc.GetCell<int>(3, i);
            orders.push_back(order);
        }
        
        // total_s
        std::map<int, int> productAmounts;
        std::map<int, double> productIncome;
        std::map<int, double> customerSpending;
        
        for (const auto& order : orders) {
            const Product& product = productMap[order.productId];
            productAmounts[order.productId] += order.amount;
            productIncome[order.productId] += order.amount * product.price;
            customerSpending[order.customerId] += order.amount * product.price;
        }
        
        // total amount ordered per product
        for (const auto& product : products) {
            std::cout << product.name << " amount: " << productAmounts[product.id] << std::endl;
        }
        
        // total money spent per product
        for (const auto& product : products) {
            std::cout << product.name << " gross income: " << productIncome[product.id] << std::endl;
        }
        
        // total money spent per customer
        for (const auto& customer : customers) {
            std::cout << customer.name << " money spent: " << customerSpending[customer.id] << std::endl;
        }
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }
    
    return 0;
}
