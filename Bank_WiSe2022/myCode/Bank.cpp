#include "Bank.h"
#include "Customer.h"
#include "Account.h"

using namespace std;

Customer* Bank::createCustomer()
{
    auto cus = std::unique_ptr<Customer>(new Customer(this->nextCustomerNumber));

//    auto cus = make_unique<Customer>(this->nextCustomerNumber);

    this->nextCustomerNumber++;

    Customer* cusPtr = cus.get();

    this->customers[cus->getId()] = move(cus);

    return cusPtr;
}

Customer* Bank::lookupCustomer(std::string id) const
{
    for(const auto& pair : this->customers)
    {
        if(pair.first == id)
        {
            return pair.second.get();
        }
    }

    return nullptr;
}

std::vector<Customer*> Bank::allCustomers() const
{
    vector<Customer*> vecCus;

    for(const auto& pair: this->customers)
    {
        vecCus.push_back(pair.second.get());
    }

    return vecCus;
}
