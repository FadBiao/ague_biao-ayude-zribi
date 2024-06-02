// Fichier Lender.cpp
#include "Lender.h"

Lender::Lender(std::string name) : name(name) {
}


std::string Lender::getName() {
    return this->name;
}

bool Lender::operator==(const Lender& other) const {
    return this->name == other.name;
}
