// Part.h
#ifndef PART_H
#define PART_H

#include "Facility.h"
#include <string>
#include <vector>

class Part {

private:
    double partAmount;
    std::string date;

public:
    Part(double amount, std::string date);
    double getPartAmount();
    std::string getDate();

};

#endif  // PART_H