
#include "Facility.h"
#include <cmath> // pour utiliser la fonction pow
#include <ctime>
#include <sstream>
#include <iomanip>

std::tm parseDate(const std::string &date) {
    std::tm tm = {};
    std::stringstream ss(date);
     std::get_time(&tm, "%Y-%m-%d");
    return tm;
}

Facility::Facility(std::string startDate, std::string endDate, double facilityAmount, std::string currency,
                   std::vector<Lender> lenders, double annualInterestRate) {
    this->startDate = startDate;
    this->endDate = endDate;
    this->facilityAmount = facilityAmount;
    this->currency = currency;
    this->lenders = lenders;
    this->parts = std::vector<Part>();
    this->annualInterestRate = annualInterestRate;
}

void Facility::addPart(Part part) {
    this->parts.push_back(part);
}

void Facility::payPart(double facilityAmount, std::string date) {
    Part newPart(facilityAmount, date);
    addPart(newPart);
    std::cout << " rest to pay = " << this->getRemainingFacilityAmount() ;
    std::cout << " interst =  " << this->calculateInterest(newPart);
}

double Facility::getRemainingFacilityAmount() {
    double totalPaid = 0;
    for (Part &part: this->parts) {
        totalPaid += part.getPartAmount();
    }
    return this->facilityAmount - totalPaid;
}

double Facility::getFacilityAmount() const{
    return this->facilityAmount;
}

void Facility::display() {

    std::cout << "Start Date: " << startDate << std::endl;
    std::cout << " End Date" << endDate << std::endl;
    std::cout << "Facility Amount : " << facilityAmount<< std::endl;
    std::cout << "currency : " << currency << std::endl;
    std::cout << "lenders: ";
    for(Lender lender : lenders ) {
        std::cout << lender.getName() << " ";
    }
    std::cout << std::endl;

    std::cout << "Parts : ";
    for(Part part : parts ) {
        std::cout << "{  \n \t "<< part.getDate() << " \n \t ";
        std::cout << part.getPartAmount() << " \n \t ";
        std::cout << calculateInterest(part) << " } ";
    }
    std::cout << std::endl;

    std::cout << "Annual interest rate : " << annualInterestRate << std::endl;

}

double Facility::calculateInterest(Part p) {
    // Convertir les dates en une mesure de temps (par exemple, le nombre de jours)
    std::tm start = parseDate(this->startDate);
    std::tm end = parseDate(p.getDate());

    std::time_t x = std::mktime(&start);
    std::time_t y = std::mktime(&end);

    double time = 0;
    if (x != (std::time_t) (-1) && y != (std::time_t) (-1)) {
        time = std::difftime(y, x) / (60 * 60 * 24 * 365); // ici le temps est en an
    }

    // Calculer les intérêts en utilisant la formule des intérêts composés.
    double interest = this->getRemainingFacilityAmount() * pow(this->annualInterestRate, time);

    return interest;
}
