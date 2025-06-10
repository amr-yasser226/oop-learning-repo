#include "LoanService.h"
#include "StringUtils.h"
#include <fstream>
#include <ctime>

using util::trim;

LoanService::LoanService(const std::string& booksFilePath,
                         const std::string& requestFilePath)
 : booksFile_(booksFilePath), requestFile_(requestFilePath)
{}

bool LoanService::existsInCatalog(const std::string& title) const {
    std::ifstream in(booksFile_);
    std::string line;
    while (std::getline(in, line)) {
        if (util::toLower(line).find(util::toLower("Title: " + title)) != std::string::npos)
            return true;
    }
    return false;
}

LoanResult LoanService::calculateDates() const {
    time_t now = std::time(nullptr);
    tm borrow = *std::localtime(&now);
    borrow.tm_mday += 1;
    std::mktime(&borrow);

    tm due = borrow;
    due.tm_mday += 21;
    std::mktime(&due);

    char buf1[11], buf2[11];
    std::strftime(buf1, sizeof(buf1), "%Y-%m-%d", &borrow);
    std::strftime(buf2, sizeof(buf2), "%Y-%m-%d", &due);

    return {buf1, buf2};
}

void LoanService::saveRequest(const std::string& title, const LoanResult& lr) const {
    std::ofstream out(requestFile_, std::ios::app);
    out << "Book Title: " << title << "\n"
        << "Borrow Date: " << lr.borrowDate << "\n"
        << "Due Date: " << lr.dueDate << "\n"
        << "-------------------\n";
}

std::optional<LoanResult> LoanService::borrowBook(const std::string& title) {
    if (!existsInCatalog(title)) return std::nullopt;
    auto lr = calculateDates();
    saveRequest(title, lr);
    return lr;
}
