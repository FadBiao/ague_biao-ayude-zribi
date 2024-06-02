// Fichier Part.cpp
#include <string>
#include "Part.h"


Part::Part(double amount, std::string date) {
    this->partAmount = amount;
    this->date = date;
}

double Part::getPartAmount()  {
    return this->partAmount;
}

std::string Part::getDate() {
    return this->date;
}

