#pragma once
#include <string>
#include <vector>
#include <sqlite3.h> // SQLite C interface header
#include "OnlineBookService.h" // To use the OnlineBook struct definition

// This class manages the SQLite database for the user's read list.
class ReadListDB {
public:
    // Constructor: Takes the database file path.
    // It will open the database and create the necessary table if it doesn't exist.
    explicit ReadListDB(const std::string& dbPath);

    // Destructor: Closes the database connection.
    ~ReadListDB();

    // Inserts a book into the read_list table.
    // Returns true on success, false on failure.
    bool insertBook(const OnlineBook& book);

    // TODO (Future): Add methods to retrieve, delete, or update books from the read list.
    // std::vector<OnlineBook> getAllBooks();
    // bool deleteBook(const std::string& title, const std::string& author);

private:
    sqlite3* db_; // Pointer to the SQLite database connection
    std::string dbPath_; // Path to the database file

    // Initializes the database schema (creates tables if they don't exist).
    bool initializeSchema();

    // Private helper for error handling.
    void logError(const std::string& message) const;

    // Helper to join a vector of strings into a single string (e.g., for subjects).
    std::string joinSubjects(const std::vector<std::string>& subjects) const;
};
