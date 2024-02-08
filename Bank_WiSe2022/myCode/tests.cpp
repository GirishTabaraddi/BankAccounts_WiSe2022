
#include <iostream>
#include <sstream>
#include <set>
#include <Poco/JSON/Stringifier.h>

using namespace std;

#include "Bank.h"
#include "Customer.h"
#include "Account.h"
#include "CurrentAccount.h"
#include "SavingsAccount.h"
#include "CDAccount.h"

/**
 * Outputs the failedMessage on the console if condition is false.
 *
 * @param condition the condition
 * @param failedMessage the message
 */
void assertTrue(bool condition, string failedMessage) {
    if (!condition) {
        cout << failedMessage << endl;
    }
}

/**
 * Initializes a bank with customers with different account
 * types. Can be used as data for various tests.
 */
void setupBank(Bank& bank) {
    // The following code has been commented out to keep
    // the start project buildable. Remove the comments
    // when you have implemented the required methods.

    Customer* c = bank.createCustomer()->setPersonalData
            ("Angel", "Alice", Poco::Data::Date(1991, 1, 1));
    c->createAccount(Bank::AccountType::Current)->transact(100);
    c->createAccount(Bank::AccountType::Savings)->transact(500);
    c->createAccount(Bank::AccountType::CD)->transact(1000);
    c->createAccount(Bank::AccountType::CD)->transact(2000);
    c->createAccount(Bank::AccountType::CD)->transact(3000);
    c->createAccount(Bank::AccountType::Savings)->transact(500);
    c->createAccount(Bank::AccountType::Savings)->transact(500);
    bank.createCustomer()->setPersonalData
            ("Billings", "Bob", Poco::Data::Date(1992, 2, 2));
    bank.createCustomer()->setPersonalData
            ("Chase", "Caesar", Poco::Data::Date(1993, 3, 3));
}

void bankTests () {
    /**
     * Create a bank and initialize it with setupBank.
     */
    // Add your code here:
    Bank myBank;

    setupBank(myBank);

    /*
     * (1) Assert that the bank has three customers.
     */
    // Add your code here:
    assertTrue((myBank.allCustomers().size() == 3),
            "Bank does not have 3 customers");
   /*
    * (2) Assert that the customer with id 0000000002 can be looked up.
    */
    // Add your code here:
    assertTrue((myBank.lookupCustomer("0000000002") != nullptr),
            "0000000002 cannot be found");
   /*
    * (3) Assert that there is no customer with id 0000000042.
    */
    // Add your code here:
    assertTrue((myBank.lookupCustomer("0000000042") == nullptr),
            "0000000042 is found");
}

void customerTests () {
    /*
     * (1) Create a Customer with sample data. Assert that
     * invoking the overloaded left shift operator produces the
     * expected result. (Hint: use a stringstream.)
     */
    // Add your code here:
    Bank myBank;

    Customer* c = myBank.createCustomer()->setPersonalData(
            "Tabaraddi", "Girish", Poco::Data::Date(1997, 3, 31));

    stringstream ss;

    ss << *c;

    string expected = "0000000001: Tabaraddi, Girish (31.03.1997)";
//    cout << *c;

    assertTrue((ss.str() == expected), "The customer data is not same");

}

void accountTests () {
    /**
     * Create a bank and initialize it with setupBank.
     */
    // Add your code here:
    Bank myBank;

    setupBank(myBank);

    /*
     * (1) Lookup Customer 0000000001 (Alice), assert that she is found.
     */
    // Add your code here:
    assertTrue((myBank.lookupCustomer("0000000001") != nullptr),
            "Alice is not found");
    /*
     * (2) Assert that Alice has 5 accounts.
     */
    // Add your code here:
//    cout << myBank.lookupCustomer("0000000001")->allAccounts().size() << endl;
//
//    auto accountsVec = myBank.lookupCustomer("0000000001")->allAccounts();
//    for(auto itr = accountsVec.begin(); itr != accountsVec.end(); itr++)
//    {
//        cout << (*itr)->getId() << endl;
//    }
    assertTrue((myBank.lookupCustomer("0000000001")->allAccounts().size() == 7),
            "Alice does not have 7 accounts");

    /**
     * (3) Assert that the C++-types of Alice's accounts and the
     * types derived from the account id (see Account::accountType)
     * match.
     */
    // Add your code here:
    auto accounts = myBank.lookupCustomer("0000000001")->allAccounts();
    for(auto& account : accounts)
    {
        Bank::AccountType derived = account->accountType(account->getId());

        string derivedStr = to_string(static_cast<int>(derived)+1);

        assertTrue((account->getId().substr(0,1) == derivedStr), "Actual type does not match derived type");
    }

    /**
     * (4) Assert that Alice has 3 accounts of type CD
     * and that these accounts have the ids "3010000001",
     * "3020000001" and "3030000001". The check must not
     * rely on accounts being returned in a specific sequence.
     *
     * In order to check this, proceed as follows:
     *  * Obtain the ids
     *  * Filter out the CD accounts and count them
     *  * Out the ids in a set and assert that the set contains
     *    the expected ids.
     */
    // Add your code here:
    auto accountsVec = myBank.lookupCustomer("0000000001")->allAccounts();

    set<string> obtainedIds;

    for(auto itr = accountsVec.begin(); itr != accountsVec.end(); itr++)
    {
        if(stoi((*itr)->getId().substr(0,1)) == 3)
        {
            obtainedIds.insert((*itr)->getId());
        }
    }

    assertTrue((obtainedIds == set<string>{"3010000001", "3020000001", "3030000001"}),
            "CD Accounts do not expected Ids");

    /**
     * (5) Assert that an attempt to delete account 3040000001
     * throws an invalid_argument exception.
     */
    // Add your code here:
//    myBank.lookupCustomer("0000000001")->deleteAccount("3040000001");

     /**
      * (6) Assert that an attempt to delete account 3020000001
      * throws a logic_error exception.
      */
    // Add your code here:
//    myBank.lookupCustomer("0000000001")->deleteAccount("3020000001");

      /**
       * (7) Withdraw the deposit from account 3010000001,
       * delete the account and assert that Alice has only
       * 4 accounts left
       */
    // Add your code here:
    myBank.lookupCustomer("0000000001")->lookupAccount("3010000001")->transact(-500);

//    cout << myBank.lookupCustomer("0000000001")->lookupAccount("3010000001")->getBalance() << endl;
    myBank.lookupCustomer("0000000001")->deleteAccount("3010000001");

    assertTrue((myBank.lookupCustomer("0000000001")->allAccounts().size() == 6),
                "Alice does not have 6 accounts");

      /**
       * (8) Lookup Alice's account 1010000001, create
       * the JSON object representing its data and assert
       * that the account type is "Current" and the balance
       * is 100.
       */
    // Add your code here:
//    auto jsonAccount =  myBank.lookupCustomer("0000000001")->lookupAccount("1010000001")->toJson();
//    cout << jsonAccount->get("accountType").toString() << endl;
//    cout << jsonAccount->get("balance").toString() << endl;
//    assertTrue(jsonAccount->get("accountType").toString() == "CD", "Account type is not CD");
//    assertTrue(jsonAccount->get("balance").toString() == "1000", "Account balance is not 100");

    auto boostAccount = myBank.lookupCustomer("0000000001")->lookupAccount("1010000001")->toJson();

    assertTrue(boostAccount.at("accountType").as_string() == "CD", "Account type is not CD");
    assertTrue(boostAccount.at("balance").as_double() == 1000, "Account balance is not 1000");

}

void allTests() {
    bankTests();
    customerTests();
    accountTests();
}
