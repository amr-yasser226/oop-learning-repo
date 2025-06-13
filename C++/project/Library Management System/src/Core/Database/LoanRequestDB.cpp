#include "LoanRequestDB.h"
#include <iostream>

// Constructor: Opens the database and initializes its schema.
LoanRequestDB::LoanRequestDB(const std::string& dbPath) : dbPath_(dbPath), db_(nullptr) {
    // Attempt to open the database. If it doesn't exist, it will be created.
    int rc = sqlite3_open(dbPath_.c_str(), &db_);
    if (rc != SQLITE_OK) {
        logError("Cannot open database: " + std::string(sqlite3_errmsg(db_)));
        sqlite3_close(db_); // Ensure db_ is closed on failure
        db_ = nullptr; // Set to nullptr to indicate failure
    } else {
        std::cout << "LoanRequestDB opened successfully: " << dbPath_ << std::endl;
        if (!initializeSchema()) {
            logError("Failed to initialize loan request database schema.");
            sqlite3_close(db_);
            db_ = nullptr;
        }
    }
}

// Destructor: Closes the database connection.
LoanRequestDB::~LoanRequestDB() {
    if (db_) {
        sqlite3_close(db_);
        std::cout << "LoanRequestDB closed." << std::endl;
    }
}

// Initializes the database schema by creating the 'loan_requests' table if it doesn't exist.
bool LoanRequestDB::initializeSchema() {
    // SQL statement to create the 'loan_requests' table.
    const char* sql = R"(
        CREATE TABLE IF NOT EXISTS loan_requests (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            book_title TEXT NOT NULL,
            borrow_date TEXT,
            due_date TEXT
        );
    )";

    char* errMsg = nullptr;
    // Execute the SQL statement.
    int rc = sqlite3_exec(db_, sql, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        logError("SQL error during loan request schema initialization: " + std::string(errMsg));
        sqlite3_free(errMsg); // Free the error message memory
        return false;
    }
    std::cout << "Loan request database schema initialized/verified." << std::endl;
    return true;
}

// Inserts a loan record into the 'loan_requests' table.
bool LoanRequestDB::insertLoan(const LoanRecord& record) {
    if (!db_) {
        logError("LoanRequestDB is not open. Cannot insert loan record.");
        return false;
    }

    // SQL statement for inserting a loan record.
    const char* sql = R"(
        INSERT INTO loan_requests (book_title, borrow_date, due_date)
        VALUES (?, ?, ?);
    )";

    sqlite3_stmt* stmt; // Prepared statement object
    // Prepare the SQL statement.
    int rc = sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        logError("Failed to prepare loan insertion statement: " + std::string(sqlite3_errmsg(db_)));
        return false;
    }

    // Bind values to the placeholders.
    sqlite3_bind_text(stmt, 1, record.bookTitle.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, record.borrowDate.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, record.dueDate.c_str(), -1, SQLITE_TRANSIENT);

    // Execute the prepared statement.
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        logError("Loan insertion failed: " + std::string(sqlite3_errmsg(db_)));
        sqlite3_finalize(stmt); // Finalize statement on failure
        return false;
    }

    sqlite3_finalize(stmt); // Finalize the prepared statement
    std::cout << "Loan record added for: " << record.bookTitle << std::endl;
    return true;
}

// Helper function to log errors.
void LoanRequestDB::logError(const std::string& message) const {
    std::cerr << "[LoanRequestDB Error] " << message << std::endl;
}
