#include "SavingsAccount.h"

using namespace std;

SavingsAccount::SavingsAccount(Customer *customer)
: Account(customer, Bank::AccountType::Savings)
{
}

boost::json::object& SavingsAccount::setAccountType(
        boost::json::object &obj) const
{
    obj.emplace("accountType", "Savings");

    return obj;
}
//Poco::JSON::Object& SavingsAccount::setAccountType(
//        Poco::JSON::Object &obj) const
//{
//    obj.set("accountType", "Savings");
//
//    return obj;
//}
