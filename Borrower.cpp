
#include <string>
#include "Borrower.h"


Borrower::Borrower(std::string name) {
    this->name = name;
}

Borrower::Borrower() {
    this->name = "Air France";
}

std::string Borrower::getName() {
    return this->name;
}

void Borrower::setName(std::string name) {
    this->name = name;
}
