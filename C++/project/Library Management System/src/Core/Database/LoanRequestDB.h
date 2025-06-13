#pragma once
#include <string>
#include <sqlite3.h> // SQLite C interface header

// Represents a single loan record.
struct LoanRecord {
    std::string bookTitle;
    std::string borrowDate;
    std::string dueDate;
};

// This class manages the SQLite database for loan requests.
class LoanRequestDB {
public:
    // Constructor: Takes the database file path.
    // It will open the database and create the necessary table if it doesn't exist.
    explicit LoanRequestDB(const std::string& dbPath);

    // Destructor: Closes the database connection.
    ~LoanRequestDB();

    // Inserts a loan record into the loan_requests table.
    // Returns true on success, false on failure.
    bool insertLoan(const LoanRecord& record);

    // TODO (Future): Add methods to retrieve, delete, or update loan records.
    // For example, to list all current loans, check overdue books, etc.

private:
    sqlite3* db_; // Pointer to the SQLite database connection
    std::string dbPath_; // Path to the database file

    // Initializes the database schema (creates tables if they don't exist).
    bool initializeSchema();

    // Private helper for error handling.
    void logError(const std::string& message) const;
};
