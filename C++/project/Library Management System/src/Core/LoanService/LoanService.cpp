#include "LoanService.h"
#include <iostream>   // <--- ADDED: For std::cout and std::cerr
#include <ctime>      // For std::time, std::localtime, std::mktime, std::strftime
#include <algorithm>  // For std::transform, std::tolower if needed in StringUtils (already there)
#include <cpr/cpr.h>  // If OnlineBookService is in same compilation unit, though typically it's already linked

using util::trim;
using util::toLower; // Assuming toLower is in util namespace

// Constructor: Initializes members with provided references and database path.
LoanService::LoanService(OnlineBookService& onlineSvc, const std::string& loanDbPath)
 : onlineBookService_(onlineSvc), loanRequestDB_(loanDbPath)
{}

// Checks if a book exists in the online catalog using OnlineBookService.
bool LoanService::existsInOnlineCatalog(const std::string& title) const {
    // Use the online book service to search for the book.
    // We only need to check if *any* result comes back.
    // Limit to 1 result for efficiency if we only need to know existence.
    auto results = onlineBookService_.search(title, 1); 
    return !results.empty();
}

LoanResult LoanService::calculateDates() const {
    time_t now = std::time(nullptr);
    tm borrow = *std::localtime(&now);
    
    // Set borrow date to tomorrow
    borrow.tm_mday += 1;
    std::mktime(&borrow); // Normalize the date

    tm due = borrow;
    due.tm_mday += 21; // Add 21 days for the due date
    std::mktime(&due); // Normalize the date

    char buf1[11], buf2[11]; // Buffer for YYYY-MM-DD (10 chars + null terminator)
    std::strftime(buf1, sizeof(buf1), "%Y-%m-%d", &borrow);
    std::strftime(buf2, sizeof(buf2), "%Y-%m-%d", &due);

    return {buf1, buf2};
}

// Saves the loan request to the SQLite database.
void LoanService::saveRequest(const std::string& title, const LoanResult& lr) const {
    LoanRecord record;
    record.bookTitle = title;
    record.borrowDate = lr.borrowDate;
    record.dueDate = lr.dueDate;

    // Call insertLoan on the mutable loanRequestDB_ member
    if (!loanRequestDB_.insertLoan(record)) {
        std::cerr << "Error: Failed to save loan request for '" << title << "' to database.\n";
    }
}

// Attempts to borrow a book.
std::optional<LoanResult> LoanService::borrowBook(const std::string& title) {
    if (!existsInOnlineCatalog(title)) {
        std::cout << "Book '" << title << "' not found in online catalog.\n";
        return std::nullopt; // Book not found
    }

    auto lr = calculateDates(); // Calculate borrow and due dates
    saveRequest(title, lr);     // Save the loan request to the database
    return lr;                  // Return the loan result
}
