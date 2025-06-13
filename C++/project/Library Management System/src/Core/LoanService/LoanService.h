#ifndef LOAN_SERVICE_H
#define LOAN_SERVICE_H

#include <string>
#include <optional>
#include <vector> // For std::vector<OnlineBook>
#include "StringUtils.h"
#include "OnlineBookService.h" // To check online catalog
#include "LoanRequestDB.h"             // For saving loan requests

struct LoanResult {
    std::string borrowDate;
    std::string dueDate;
};

class LoanService {
public:
    // Constructor now takes an OnlineBookService instance by reference
    // and the path for the loan request database.
    LoanService(OnlineBookService& onlineSvc, const std::string& loanDbPath);

    // Try to borrow a book title; returns empty optional on failure
    std::optional<LoanResult> borrowBook(const std::string& title);

private:
    OnlineBookService& onlineBookService_; // Reference to the online book service
    // Make loanRequestDB_ mutable so we can call non-const methods from const LoanService methods
    mutable LoanRequestDB loanRequestDB_;  // <--- ADDED 'mutable' keyword

    // Now checks online availability instead of a local file
    bool existsInOnlineCatalog(const std::string& title) const;
    LoanResult calculateDates() const;
    // Saves to SQLite DB instead of a file
    void saveRequest(const std::string& title, const LoanResult& lr) const;
};

#endif // LOAN_SERVICE_H
