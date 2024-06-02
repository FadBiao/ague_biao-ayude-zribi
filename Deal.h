#ifndef DEAL_H
#define DEAL_H

#include <string>
#include <vector>

#include "Lender.h"
#include "Borrower.h"

using std::vector;


class Deal {
private:
    std::string agent;
    Borrower borrower;
    double project_amount;
    std::string currency;
    std::string contract_sign_date;
    std::string contract_end_date;
    std::string status;


public:
    Deal(std::string contract_num,
         std::string agent,
         std::vector<Lender> pool,
         Borrower borrower,
         double project_amount,
         std::string currency,
         std::string contract_sign_date,
         std::string contract_end_date,
         std::string status);

    // Destructeur
    ~Deal();


    void addFacility(Facility facility);

    void displayDetails();

    std::string getContractSignDate() const;

    std::string getContractEndDate() const;

    std::string getCurrency() const;

    double getProjectAmount() const;

    std::vector<Facility> facilities;

    std::vector<Lender> pool;
    std::string contract_num;

    void setStatus();
};

#endif