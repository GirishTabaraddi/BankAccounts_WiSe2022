/*
 * Customer.h
 *
 *  Created on: 29.01.2023
 *      Author: mnl
 */

#ifndef CUSTOMER_H_
#define CUSTOMER_H_

#include <string>
#include <ostream>
#include <map>
#include <memory>
#include <Poco/Data/Date.h>
#include "Bank.h"

#include <iomanip>
#include <sstream>

class Account;

/**
 * Represents a customer of the bank.
 */
class Customer {
private:
    const unsigned int number;
    std::string lastName;
    std::string firstName;
    Poco::Data::Date dateOfBirth;
    std::map<std::string,std::unique_ptr<Account>> accounts;

public:
    /**
     * Creates a new customer record with the given number.
     *
     * @param the customer record number
     */
    Customer(unsigned int number);

    /**
     * Returns the customer number.
     */
    unsigned int getNumber() const;

    /**
     * Returns the customer id. The id is the customer number
     * left padded with zeros until the length is 10. Example:
     * if the customer number is 1234, the id is "0000001234".
     */
    std::string getId() const;

    /**
     * Sets the personal data.
     *
     * @param lastName the last name
     * @param firstName the first name
     * @param dateOfBirth the customer's date of birth
     * @return the customer for method chaining
     */
    Customer* setPersonalData(std::string lastName,
            std::string firstName, Poco::Data::Date dateOfBirth);

    /**
     * Returns the date of birth.
     */
    const Poco::Data::Date& getDateOfBirth() const;

    /**
     * Returns the first name.
     */
    const std::string& getFirstName() const;

    /**
     * Returns the last name.
     */
    const std::string& getLastName() const;

    /**
     * Create a new account of the given type for the customer.
     *
     * @param type the account type
     */
    Account* createAccount(Bank::AccountType type);

    /**
     * Returns a list of all accounts of the user
     *
     * @return vector of pointers to all accounts
     */
    std::vector<Account*> allAccounts() const;

    /**
     * Return the account with the given id.
     *
     * @throws invalid_argument exception if an account with
     * the given id does not exist
     */
    Account* lookupAccount(std::string id) const;

    /**
     * Delete the account with the given id if its balance is 0.
     *
     * Implementation hint: in order to avoid searching through
     * the accounts twice, the implementation must use
     * an iterator for searching and erasing the account.
     *
     * @param id the account id
     * @throws invalid_argument if an account with the given id
     * does not exist
     * @throws logic_error if the balance of the account is not 0
     */
    void deleteAccount (std::string id);
};

/**
 * Writes a customer's personal data to the stream as
 *
 * <id>: <lastName>, <firstName> (<dateOfBirth>)
 *
 * <dateOfBirth> may have English or German format, no zero-padding required.
 *
 * Example:
 * 0000000001: Angel, Alice (1.1.1991)
 */
std::ostream& operator<< (std::ostream& out, const Customer& customer);

#endif /* CUSTOMER_H_ */
