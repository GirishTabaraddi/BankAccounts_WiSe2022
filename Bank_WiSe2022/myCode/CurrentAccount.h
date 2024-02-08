/*
 * CurrentAccount.h
 *
 *  Created on: 29.01.2023
 *      Author: mnl
 */

#ifndef CURRENTACCOUNT_H_
#define CURRENTACCOUNT_H_

#include <string>
#include "Account.h"

class Customer;

class CurrentAccount : public Account {

public:
    /**
     * Initializes a new account.
     *
     * @param customer the customer for which an account is to be created
     */
    CurrentAccount(Customer* customer);

    /**
     * Sets the field "accountType" of the object to "Current".
     *
     * @return the object for method invocation chaining
     */
//    Poco::JSON::Object& setAccountType(Poco::JSON::Object& obj) const;
    boost::json::object& setAccountType(boost::json::object& obj) const;
};

#endif /* CURRENTACCOUNT_H_ */
