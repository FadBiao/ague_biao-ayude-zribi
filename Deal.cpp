
#include "Deal.h"
#include "Borrower.h"
#include <vector>
#include <algorithm>



Deal::Deal(std::string contract_num,
           std::string agent,
           std::vector<Lender> pool,
           Borrower borrower,
           double project_amount,
           std::string currency,
           std::string contract_sign_date,
           std::string contract_end_date,
           std::string status)
{
    this->contract_num = contract_num;
    this->agent = agent;
    this->pool = pool;
    auto new_end = std::remove(this->pool.begin(), this->pool.end(), Lender(this->agent));
    this->pool.erase(new_end, this->pool.end()); this->borrower = borrower;
    this->project_amount = project_amount;
    this->currency = currency;
    this->contract_sign_date = contract_sign_date;
    this->contract_end_date = contract_end_date;
    this->status = status;
}

// Destructeur
Deal::~Deal(){}

std::string Deal::getContractSignDate() const {
    return contract_sign_date;
}

std::string Deal::getContractEndDate() const {
    return contract_end_date;
}

std::string Deal::getCurrency() const {
    return currency;
}

void Deal::addFacility(Facility facility) {
    this->facilities.push_back(facility);
}

double Deal::getProjectAmount() const{
    return project_amount;
}

void Deal::displayDetails() {
    std::cout << "Contract Number: " << contract_num << std::endl;
    std::cout << "Agent: " << agent << std::endl;

    std::cout << "Pool: ";
    for(Lender lender : pool) {
        std::cout << lender.getName() << " ";
    }
    std::cout << std::endl;

    std::cout << "Borrower: " << borrower.getName() << std::endl;
    std::cout << "Project Amount: " << project_amount << std::endl;
    std::cout << "Currency: " << currency << std::endl;
    std::cout << "Contract Sign Date: " << contract_sign_date << std::endl;
    std::cout << "Contract End Date: " << contract_end_date << std::endl;
    std::cout << "Status: " << status << std::endl;
}

void Deal::setStatus() {
    this->status = "Terminate";
}
