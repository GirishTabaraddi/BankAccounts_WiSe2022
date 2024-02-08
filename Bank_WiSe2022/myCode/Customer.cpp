#include "Customer.h"
#include "CDAccount.h"
#include "CurrentAccount.h"
#include "SavingsAccount.h"

using namespace std;

Customer::Customer(unsigned int number) : number(number)
{
}

unsigned int Customer::getNumber() const
{
    return this->number;
}

std::string Customer::getId() const
{
    ostringstream oss;

    oss << setw(10) << setfill('0') << this->getNumber();

    return oss.str();
}

Customer* Customer::setPersonalData(std::string lastName, std::string firstName,
        Poco::Data::Date dateOfBirth)
{
    this->firstName = firstName;
    this->lastName = lastName;
    this->dateOfBirth = dateOfBirth;

    return this;
}

const Poco::Data::Date& Customer::getDateOfBirth() const
{
    return this->dateOfBirth;
}

const std::string& Customer::getFirstName() const
{
    return this->firstName;
}

const std::string& Customer::getLastName() const
{
    return this->lastName;
}

std::vector<Account*> Customer::allAccounts() const
{
    vector<Account*> vecAcc;

    for(const auto& pair: this->accounts)
    {
        vecAcc.push_back(pair.second.get());
    }

    return vecAcc;
}

Account* Customer::lookupAccount(std::string id) const
{
    Account* acc = nullptr;

    for(const auto& pair: this->accounts)
    {
        if(pair.first == id)
        {
            acc = pair.second.get();
            break;
        }
        else
        {
            acc = nullptr;
        }
    }

    return acc;
}

Account* Customer::createAccount(Bank::AccountType type)
{
    unique_ptr<Account> acc = nullptr;

    string accountId;

    if(type == Bank::CD)
    {
        acc = make_unique<CDAccount>(this);
        accountId = acc.get()->getId();
    }
    if(type == Bank::Current)
    {
        acc = make_unique<CurrentAccount>(this);
        accountId = acc.get()->getId();
    }
    if(type == Bank::Savings)
    {
        acc = make_unique<SavingsAccount>(this);
        accountId = acc.get()->getId();
    }

    this->accounts[accountId] = move(acc);

    return this->accounts[accountId].get();
}

void Customer::deleteAccount(std::string id)
{
    auto findId = this->accounts.find(id);

    if(findId != this->accounts.end())
    {
        auto currentAcc = findId->second.get();

//        cout << currentAcc->getBalance() << endl;

        if(currentAcc->getBalance() == 0)
        {
            this->accounts.erase(findId);
        }
        else
        {
            throw logic_error("Logic Error: Cannot delete account non 0 Balance\n");
        }
    }
    else
    {
        throw invalid_argument("Invalid Argument: Entered Id doesn't exist\n");
    }
}

std::ostream& operator <<(std::ostream &out, const Customer &customer)
{
    Poco::Data::Date dob = customer.getDateOfBirth();

    string dobStr = Poco::DateTimeFormatter::format
            (Poco::LocalDateTime(dob.year(), dob.month(), dob.day()), "%d.%m.%Y");

    out << customer.getId() << ": " << customer.getLastName() << ", "
            << customer.getFirstName() << " (" << dobStr << ")";
//    out << customer.getId() << ": " << customer.getLastName() << ", "
//            << customer.getFirstName() << " (" << dob.day() << "." <<
//            dob.month() << "." << dob.year() << ")";

    return out;
}
