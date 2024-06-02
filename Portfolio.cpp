// Fichier Portfolio.cpp
#include "Portfolio.h"

Portfolio::Portfolio(Facility facility) : facility(facility) {
    totalInterest = 0.0;
}

double Portfolio::getTotalAmount() {
    return facility.getFacilityAmount();
}

double Portfolio::getTotalInterest() {
    double total = 0;
    for (Part &part: this->facility.parts) { // changed to reference
        total += facility.calculateInterest(part);
    }
    return total;
}

double Portfolio::getTotalRemboursement(){
    return this->getTotalAmount() + this->getTotalInterest();
}

void Portfolio::addInterest(double interest) {
    totalInterest += interest;
}

