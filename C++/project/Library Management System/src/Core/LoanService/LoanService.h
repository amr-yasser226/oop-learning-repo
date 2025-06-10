#ifndef LOAN_SERVICE_H
#define LOAN_SERVICE_H

#include <string>
#include <optional>
#include "StringUtils.h"

struct LoanResult {
    std::string borrowDate;
    std::string dueDate;
};

class LoanService {
public:
    LoanService(const std::string& booksFilePath,
                const std::string& requestFilePath);

    // Try to borrow a book title; returns empty optional on failure
    std::optional<LoanResult> borrowBook(const std::string& title);

private:
    std::string booksFile_;
    std::string requestFile_;

    bool existsInCatalog(const std::string& title) const;
    LoanResult calculateDates() const;
    void saveRequest(const std::string& title, const LoanResult& lr) const;
};

#endif // LOAN_SERVICE_H
