
#ifndef BORROWER_H
#define BORROWER_H

#include <string>

class Borrower {
public:
    Borrower(std::string name);
    Borrower();
    std::string getName();

    void setName(std::string basicString);

private:
    std::string name;


};

#endif
