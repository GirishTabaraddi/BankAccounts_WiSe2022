/*
 * Bank.h
 *
 *  Created on: 29.01.2023
 *      Author: mnl
 */

#ifndef BANK_H_
#define BANK_H_

#include <memory>
#include <map>
#include <vector>

class Customer;

/**
 * Represents the Bank. In the scope of this exercise, the properties
 * of the bank are reduced to "a bank has customers".
 */
class Bank {
private:
    /** The number of the next customer that is created by an
     * invocation of #createCustomer() */
    unsigned int nextCustomerNumber = 1;

    /** The customer directory. Customers are stored by their id. */
    std::map<std::string, std::unique_ptr<Customer>> customers;

public:
    /**
     * The account types offered by the bank (in alphabetical order).
     */
    enum AccountType { CD, Current, Savings };

    /**
     * Creates a new customer, assigning it the next available id
     * (see #nextCustomerId). The customer is added to the customer
     * directory (see #customers).
     */
    Customer* createCustomer();

    /**
     * Looks up a customer in the customer directory by its id.
     *
     * @param id the customer id
     * @return a pointer to the customer or nullptr if no customer
     * with this id exists
     */
    Customer* lookupCustomer(std::string id) const;

    /**
     * Returns pointers to all customers of the bank.
     *
     * @return the customers
     */
    std::vector<Customer*> allCustomers() const;

};

#endif /* BANK_H_ */
