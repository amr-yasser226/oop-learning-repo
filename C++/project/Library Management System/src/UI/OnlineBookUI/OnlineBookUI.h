#pragma once
#include "OnlineBookService.h"
#include "ReadListDB.h" // Include the new database class
#include <string>
#include <vector>

class OnlineBookUI {
public:
    explicit OnlineBookUI(const std::string& dbPath);
    void run();

private:
    OnlineBookService svc_;
    ReadListDB db_; // The new database member
    
    std::string currentQuery_;
    size_t currentOffset_;
    const size_t limit_ = 5;

    void doSearch();
    void displayResults(const std::vector<OnlineBook>& books);
    // Renamed and modified: This function now handles prompting and validating user input for adding books.
    void promptAndAddBooksToReadList(const std::vector<OnlineBook>& availableBooks);
    void handleSearchResults();
};
