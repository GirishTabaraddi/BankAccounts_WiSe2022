/*
 * SavingsAccount.h
 *
 *  Created on: 29.01.2023
 *      Author: mnl
 */

#ifndef SAVINGSACCOUNT_H_
#define SAVINGSACCOUNT_H_

#include "Account.h"

class Customer;

class SavingsAccount : public Account {

public:
    /**
     * Initializes a new account.
     *
     * @param customer the customer for which an account is to be created
     */
    SavingsAccount(Customer* customer);

    /**
     * Sets the accountType field of the object to "Savings".
     *
     * @param obj the object to modify
     * @return the object for method invocation chaining
     */
//    Poco::JSON::Object& setAccountType(Poco::JSON::Object& obj) const;
    boost::json::object& setAccountType(boost::json::object& obj) const;
};

#endif /* SAVINGSACCOUNT_H_ */
