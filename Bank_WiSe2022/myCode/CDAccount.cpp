#include "CDAccount.h"

using namespace std;

CDAccount::CDAccount(Customer *customer)
: Account(customer, Bank::AccountType::CD)
{
}

boost::json::object& CDAccount::setAccountType(boost::json::object &obj) const
{
    obj.emplace("accountType", "CD");

    return obj;
}

//Poco::JSON::Object& CDAccount::setAccountType(Poco::JSON::Object &obj) const
//{
//    obj.set("accountType", "CD");
//
//    return obj;
//}
