#ifndef LOAN_UI_H
#define LOAN_UI_H

#include "LoanService.h"

class LoanUI {
public:
    LoanUI(LoanService& svc);
    void runMenu();

private:
    LoanService& svc_;
    void doBorrow();
};

#endif // LOAN_UI_H
