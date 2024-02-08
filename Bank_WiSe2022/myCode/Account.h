/*
 * Account.h
 *
 *  Created on: 29.01.2023
 *      Author: mnl
 */

#ifndef ACCOUNT_H_
#define ACCOUNT_H_

#include <string>
#include <Poco/JSON/Object.h>
#include "Bank.h"

#include <boost/json.hpp>

class Customer;

/**
 * Base class for all Accounts. Accounts have an id which is assigned
 * upon creation as follows:
 *
 *  * The first digit indicated the account type
 *    - 1: Current account
 *    - 2: Savings account
 *    - 3: Certificate of deposit account
 *
 *  * The second and third digit represent a counter (sequence number)
 *    for the number of accounts of a given type. Counting starts with 1.
 *
 *  * The remaining 8 digits are the same as the 8 rightmost digits
 *    of the customer id.
 */
class Account {
private:
    std::string id;
    float balance = 0;

protected:
    /**
     * Initializes a new account.
     *
     * To evaluate the account id, the method uses the type
     * passed as argument (becomes the leftmost digit). In
     * addition, it searches through the existing accounts
     * of the customer in order to find the next free sequence
     * number for creating an account of the desired type.
     *
     * Note that finding the next free sequence number isn't trivial.
     * Imagine that you have created accounts with id's
     * 3010000001, 3020000001, 3030000001. Then the second account
     * is deleted, leaving accounts 3010000001, 3030000001. If you
     * create a new account of type "3", you'll have to detect that
     * sequence number "02" is not used and create 3020000001 as
     * new id.
     *
     * @param customer the customer for which an account is to be created
     * @param type the account type
     */
    Account(Customer* customer, Bank::AccountType type);

    /**
     * Sets the field "accountType" of the JSON object.
     *
     * @return the object for method invocation chaining
     */
//    virtual Poco::JSON::Object&
//        setAccountType(Poco::JSON::Object& obj) const = 0;
    virtual boost::json::object&
        setAccountType(boost::json::object& obj) const = 0;

public:
    /**
     * Given an account id, extract and return the account type.
     *
     * @param accountId the account id
     * @return the account type
     * @throws invalid_argument exception if the type cannot
     * be derived from the id.
     */
    static Bank::AccountType accountType(std::string accountId);

    /**
     * Defined because this a a base class, does nothing.
     */
    virtual ~Account();

    /**
     * Returns the id of the account.
     */
    std::string getId() const;

    /**
     * Returns the current balance.
     *
     * @return the balance
     */
    float getBalance() const;

    /**
     * Combined method for deposit (positiv amount) and
     * withdraw (negative amount).
     *
     * @param amount the amount to add to or subtract from the balance
     */
    void transact(float amount);

    /**
     * Creates a JSON Object that represents the account data.
     * Fields are "accountType" and "balance", e.g.:
     * {"accountType":"Current","balance":100}
     */
//    Poco::JSON::Object::Ptr toJson() const;
    boost::json::object toJson() const;
};

#endif /* ACCOUNT_H_ */
