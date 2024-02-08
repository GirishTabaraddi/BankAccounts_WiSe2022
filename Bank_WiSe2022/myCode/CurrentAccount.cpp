#include "CurrentAccount.h"

using namespace std;

CurrentAccount::CurrentAccount(Customer *customer)
: Account(customer, Bank::AccountType::Current)
{
}

boost::json::object& CurrentAccount::setAccountType(boost::json::object &obj) const
{
    obj.emplace("accountType", "Current");

    return obj;
}

//Poco::JSON::Object& CurrentAccount::setAccountType(
//        Poco::JSON::Object &obj) const
//{
//    obj.set("accountType", "Current");
//
//    return obj;
//}
