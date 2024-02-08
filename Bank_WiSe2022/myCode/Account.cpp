#include "Account.h"
#include "Customer.h"

#include <boost/json/src.hpp>

using namespace std;

Account::~Account()
{
}

Account::Account(Customer *customer, Bank::AccountType type)
{
    int lsb = 0;

    if(type == Bank::CD)
    {
        lsb = 1;
    }
    else if(type == Bank::Current)
    {
        lsb = 2;
    }
    else if(type == Bank::Savings)
    {
        lsb = 3;
    }
    else
    {
        lsb = 0;
    }

    int sequenceNumber = 1;

    for(const auto& acc : customer->allAccounts())
    {
//        int accountTypeFromId = std::stoi(acc->getId().substr(0,1));

//        cout << lsb << " " << accountTypeFromId << endl;

        if(static_cast<int>(acc->accountType(acc->getId()))+1 == lsb)
        {
            int currSeqNumber = stoi(acc->getId().substr(1,2));
//            cout << currSeqNumber << endl;

            if(currSeqNumber >= sequenceNumber)
            {
                sequenceNumber = currSeqNumber + 1;
            }
        }
    }

    // generate the account id
    ostringstream oss;

    oss << lsb << setw(2) << setfill('0') << sequenceNumber
            << setw(7) << setfill('0') << customer->getNumber();

    this->id = oss.str();
    this->balance = 0;

//    cout << this->id << endl;
}

float Account::getBalance() const
{
    return this->balance;
}

std::string Account::getId() const
{
    return this->id;
}

Bank::AccountType Account::accountType(std::string accountId)
{
    int accountType = stoi(accountId.substr(0,1));

    if(accountType == 1)
    {
        return Bank::AccountType::CD;
    }
    else if(accountType == 2)
    {
        return Bank::AccountType::Current;
    }
    else if(accountType == 3)
    {
        return Bank::AccountType::Savings;
    }
    else
    {
        throw invalid_argument("Invalid Argument: Account Id cannot be found\n");
    }
}

void Account::transact(float amount)
{
    if(balance + amount < 0)
    {
        cerr << "Insufficient funds to withdraw" << endl;
    }

    balance += amount;
}

boost::json::object Account::toJson() const
{
    boost::json::object obj;

    setAccountType(obj);

    obj.emplace("balance", this->balance);

    return obj;
}

//Poco::JSON::Object::Ptr Account::toJson() const
//{
//    Poco::JSON::Object::Ptr obj = new Poco::JSON::Object;
//
//    setAccountType(*obj);
//
//    obj->set("balance", this->balance);
//
//    return obj;
//}
