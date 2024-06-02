
#ifndef FACILITY_H
#define FACILITY_H

#include <vector>
#include "Lender.h"
#include "Part.h"

class Facility {
public:
    Facility(std::string startDate, std::string endDate, double facilityAmount, std::string currency,
             std::vector<Lender> lenders, double annualInterestRate);
    void addPart(Part part);
    double getRemainingFacilityAmount();
    double calculateInterest(Part p);
    void payPart(double amount, std::string date);

    double getFacilityAmount() const;

    void display();

    std::vector<Part> parts;
private:
    std::string startDate;
    std::string endDate;
    std::string currency;
    std::vector<Lender> lenders;
    double annualInterestRate;
    double facilityAmount;


};

#endif