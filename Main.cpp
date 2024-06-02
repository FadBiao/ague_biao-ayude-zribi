#include <iostream>
#include "Facility.h"
#include "Facility.cpp"
#include "Lender.h"
#include "Lender.cpp"
#include "Part.h"
#include "Part.cpp"
#include "Borrower.h"
#include "Borrower.cpp"
#include "Deal.h"
#include "Deal.cpp"
#include "Portfolio.h"
#include "Portfolio.cpp"
#include <algorithm>

std::vector<Lender> pool;

std::vector<Lender> lenders;

std::vector<Borrower> borrowers;

std::vector<Facility> facilites;

std::vector<Deal> deals;

void createDeal();

Borrower createBorrower();

Lender createLender();

void addLenderToPool();

Facility createFacility(Deal& deal);

void pay();

int main() {

    Borrower borrower1("TOTAL ENERGIES");
    Borrower borrower2("TESLA");
    borrowers.push_back(borrower1);
    borrowers.push_back(borrower2);


    Lender lender1("BPCE");
    Lender lender2("SG");
    lenders.push_back(lender1);
    lenders.push_back(lender2);

    Deal deal("S1234", "BPCE", lenders, borrower1, 100520900, "EUR", "2023-06-26", "2033-06-27", "ACTIVE");
    deals.push_back(deal);

    Facility facility1(deals[0].getContractSignDate(), deals[0].getContractEndDate(), deals[0].getProjectAmount(), deals[0].getCurrency(),
                       {lender1, lender2}, 0.05);

    facilites.push_back(facility1);

    Part p1(1000000, "2026-07-25");
    Part p2(2000000, "2027-07-25");
    Part p3(1000000, "2032-07-25");
    facility1.addPart(p1);
    facility1.addPart(p2);
    facility1.addPart(p3);


    Portfolio portfolio(facility1);

    while (true) {
        std::cout << "\n-----------********************----------\n";
        std::cout << "----------> Structured Financing <---------\n";
        std::cout << "-------------********************----------\n";
        std::cout << "Press 1 :  Create a new deal\n";
        std::cout << "Press 2 :  Create a new borrower\n";
        std::cout << "Press 3 :  Create a new lender\n";
        std::cout << "Press 4 : Add a lender to the pool\n";
        std::cout << "Press 5 :  Create a new facility\n";
        std::cout << "Press 6 : Pay a part of a facility\n";
        std::cout << "Press 7 : Calculate interest\n";
        std::cout << "Press 8 : Manage portfolio\n";
        std::cout << "Press 9 : Terminate a deal\n";
        std::cout << "Press 10 : Display details of a deal\n";
        std::cout << "Press 11 : Display list of borrowers and lenders\n";
        std::cout << "Press 12 : Display the facilities\n";

        std::cout << "Press 0 : Exit\n";
        std::cout << "---------------------------------------\n";
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:

                createDeal();
                break;
            case 2:

                borrowers.push_back(createBorrower());
                break;
            case 3:

                lenders.push_back(createLender());
                break;
            case 4:

                addLenderToPool();
                break;
            case 5:

                createFacility(deals[0]);
                break;
            case 6:

                pay();
                break;
            case 7:

                std::cout << "Calculate the interest of part 1" << std::endl;
                std::cout << "The interest is : " << facility1.calculateInterest(p1);
                break;
            case 8:
               
                std::cout << "The total interest accumulated is: " << portfolio.getTotalInterest() << std::endl;
                std::cout << "The total amount is: " << portfolio.getTotalAmount() << std::endl;;
                std::cout << "Amount should be repaid: " << portfolio.getTotalRemboursement() << std::endl;
                break;
            case 9:

                for (Deal deal : deals){
                    for (int i=0;i<deal.facilities.size();i++){
                        if (deals[0].facilities[i].getRemainingFacilityAmount() > 0){
                            std::cout << "The deal does not finish !" << std::endl;
                        } else{
                            deals[0].setStatus();
                            std::cout << "All the deal is finished " << std::endl;
                        }
                    }
                }

                break;
            case 10:

                for(int i = 0; i < deals.size(); i++){
                    deals[i].displayDetails();

                }

                break;
            case 11:

                std::cout << "List of lenders :" << std::endl;
                for(int i = 0; i < lenders.size(); i++){
                    std::cout << lenders[i].getName() << std::endl;
                }

                std::cout << "List of borrowers :" << std::endl;
                for(int i = 0; i < borrowers.size(); i++){
                    std::cout << borrowers[i].getName() << std::endl;
                }
                break;
            case 12:

                std::cout << "List of facilities :" << std::endl;
                for(int i = 0; i < facilites.size(); i++){
                    facilites[i].display();
                }
                break;
            case 0:
                return 0;
            default:
                std::cout << "Invalid choice. Please enter a number between 0 and 12.\n";
        }
    }
    return 0;
}

void pay() {
    double amount;
    std::string date;
    std::cout << "Enter the amount to pay: ";
    std::cin >> amount;
    std::cout << "Enter the date of payment: ";
    std::cin >> date;
    if (facilites[0].getRemainingFacilityAmount() < amount){
        std::cout << "amount too much" << std::endl;
    }else {
        facilites[0].payPart(amount, date);
    }
}

Deal* findDealByNumber(const std::string& dealNum) {

    for (auto& deal : deals) {
        if (deal.contract_num == dealNum) {
            return &deal;
        }
    }
    return nullptr;
}

Facility createFacility(Deal& deal) {
    std::string currency;
    double amount;
    double annualInterestRate;
    std::vector<Lender> selectedLenders;

    std::cout << "Enter the amount: ";
    std::cin >> amount;
    std::cout << "Enter the currency: ";
    std::cin >> currency;
    std::cout << "Enter the annual interest rate (e.g., 0.05 for 5%): ";
    std::cin >> annualInterestRate;


    int lenderCount;
    std::cout << "How many lenders would you like to add to this facility? ";
    std::cin >> lenderCount;

    for (int i = 0; i < lenderCount; i++) {
        std::string lenderName;
        std::cout << "Enter the name of lender " << (i+1) << ": ";
        std::cin >> lenderName;

        auto it = std::find_if(deal.pool.begin(), deal.pool.end(), [&lenderName](Lender lender) {
            return lender.getName() == lenderName;
        });

        if (it != deal.pool.end()) {
            selectedLenders.push_back(*it);
        } else {
            std::cout << "Lender " << lenderName << " not found in the pool.\n";
        }
    }

    Facility facility(deal.getContractSignDate(), deal.getContractEndDate(), amount, currency, selectedLenders, annualInterestRate);
    deal.facilities.push_back(facility); // Add the created facility to the deal's facilities
    return facility;
}

void createDeal() {
    std::string contract_num;
    std::string agent;
    Borrower borrower;
    double project_amount;
    std::string currency;
    std::string contract_sign_date;
    std::string contract_end_date;
    std::string status;

    std::cout << "\nEnter contract number: ";
    std::cin >> contract_num;
    std::cout << "\nEnter agent: ";
    std::cin >> agent;
    std::cout << "\nEnter project amount: ";
    std::cin >> project_amount;
    std::cout << "\nEnter currency: ";
    std::cin >> currency;
    std::cout << "\nEnter contract sign date: ";
    std::cin >> contract_sign_date;
    std::cout << "\nEnter contract end date: ";
    std::cin >> contract_end_date;
    std::cout << "\nEnter deal status: ";
    std::cin >> status;

    Deal deal(contract_num, agent, std::vector<Lender>(), borrower, project_amount, currency, contract_sign_date, contract_end_date, status);
    deals.push_back(deal);
}

Borrower createBorrower() {
    std::string name;
    std::cout << "Borrower's name: ";
    std::cin >> name;

    return Borrower(name);
}

Lender createLender() {
    std::string name;
    std::cout << "Lender's name: ";
    std::cin >> name;

    return Lender(name);
}

void addLenderToPool() {
    std::string lenderName;
    std::cout << "Give the lender's name: ";
    std::cin >> lenderName;

    auto it = std::find_if(lenders.begin(), lenders.end(), [&lenderName](Lender lender) {
        return lender.getName() == lenderName;
    });


    if (it != lenders.end()) {

        pool.push_back(*it);
        std::cout << "Lender " << lenderName << " added to the pool.\n";
    } else {

        std::cout << "Error: Lender " << lenderName << " does not exist.\n";
    }
}
