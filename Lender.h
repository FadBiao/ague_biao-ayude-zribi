// Fichier Lender.h
#ifndef LENDER_H
#define LENDER_H

#include <string>

class Lender {
public:
    Lender(std::string name);

    std::string getName();
    bool operator==(const Lender& other) const;

private:
    std::string name;
};

#endif
