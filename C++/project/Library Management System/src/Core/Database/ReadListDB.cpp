#include "ReadListDB.h"
#include <iostream>
#include <sstream> // For std::ostringstream to join strings

// Constructor: Opens the database and initializes its schema.
ReadListDB::ReadListDB(const std::string& dbPath) : dbPath_(dbPath), db_(nullptr) {
    // Attempt to open the database. If it doesn't exist, it will be created.
    int rc = sqlite3_open(dbPath_.c_str(), &db_);
    if (rc != SQLITE_OK) {
        logError("Cannot open database: " + std::string(sqlite3_errmsg(db_)));
        sqlite3_close(db_); // Ensure db_ is closed on failure
        db_ = nullptr; // Set to nullptr to indicate failure
    } else {
        std::cout << "Database opened successfully: " << dbPath_ << std::endl;
        if (!initializeSchema()) {
            logError("Failed to initialize database schema.");
            sqlite3_close(db_);
            db_ = nullptr;
        }
    }
}

// Destructor: Closes the database connection.
ReadListDB::~ReadListDB() {
    if (db_) {
        sqlite3_close(db_);
        std::cout << "Database closed." << std::endl;
    }
}

// Initializes the database schema by creating the 'read_list' table if it doesn't exist.
bool ReadListDB::initializeSchema() {
    // SQL statement to create the 'read_list' table.
    // 'id' is a primary key that auto-increments.
    // 'title' is NOT NULL because a book must have a title.
    // Other fields can be NULL if data is missing.
    const char* sql = R"(
        CREATE TABLE IF NOT EXISTS read_list (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            title TEXT NOT NULL,
            author TEXT,
            publish_year TEXT,
            genres TEXT,
            url TEXT
        );
    )";

    char* errMsg = nullptr;
    // Execute the SQL statement.
    int rc = sqlite3_exec(db_, sql, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        logError("SQL error during schema initialization: " + std::string(errMsg));
        sqlite3_free(errMsg); // Free the error message memory
        return false;
    }
    std::cout << "Database schema initialized/verified." << std::endl;
    return true;
}

// Inserts a book into the 'read_list' table using a prepared statement for safety.
bool ReadListDB::insertBook(const OnlineBook& book) {
    if (!db_) {
        logError("Database is not open. Cannot insert book.");
        return false;
    }

    // SQL statement for inserting a book.
    // Use '?' as placeholders for binding parameters to prevent SQL injection.
    const char* sql = R"(
        INSERT INTO read_list (title, author, publish_year, genres, url)
        VALUES (?, ?, ?, ?, ?);
    )";

    sqlite3_stmt* stmt; // Prepared statement object
    // Prepare the SQL statement.
    int rc = sqlite3_prepare_v2(db_, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        logError("Failed to prepare statement: " + std::string(sqlite3_errmsg(db_)));
        return false;
    }

    // Bind values to the placeholders.
    // sqlite3_bind_text(statement, parameter_index, value, length, destructor)
    // -1 for length means strlen will be used.
    // SQLITE_TRANSIENT means SQLite makes a copy of the string.
    sqlite3_bind_text(stmt, 1, book.title.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, book.author.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, book.publishYear.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, joinSubjects(book.subjects).c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 5, book.openLibraryUrl.c_str(), -1, SQLITE_TRANSIENT);

    // Execute the prepared statement. sqlite3_step returns SQLITE_DONE for successful INSERT.
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        logError("Execution failed: " + std::string(sqlite3_errmsg(db_)));
        sqlite3_finalize(stmt); // Finalize statement on failure
        return false;
    }

    sqlite3_finalize(stmt); // Finalize (destroy) the prepared statement
    std::cout << "Book added to read list: " << book.title << std::endl;
    return true;
}

// Helper function to log errors.
void ReadListDB::logError(const std::string& message) const {
    std::cerr << "[ReadListDB Error] " << message << std::endl;
}

// Helper function to join a vector of subjects into a comma-separated string.
std::string ReadListDB::joinSubjects(const std::vector<std::string>& subjects) const {
    if (subjects.empty()) {
        return "";
    }
    std::ostringstream oss;
    for (size_t i = 0; i < subjects.size(); ++i) {
        oss << subjects[i];
        if (i < subjects.size() - 1) {
            oss << ", ";
        }
    }
    return oss.str();
}
