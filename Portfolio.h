// Fichier Portfolio.h
#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include <string>

#include <vector>
#include "Facility.h"

class Portfolio {
public:
    Portfolio(Facility facility);
    double getTotalAmount();
    double getTotalInterest();
    void addInterest(double interest);
    double getTotalRemboursement();
private:
    double totalInterest;
    Facility facility;
};

#endif