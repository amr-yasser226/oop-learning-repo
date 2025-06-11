#pragma once
#include "OnlineBookService.h"
#include <string>
#include <vector> // Add this include for std::vector<OnlineBook>

class OnlineBookUI {
public:
    OnlineBookUI(const std::string& readListPath);
    void run();

private:
    OnlineBookService svc_;
    std::string readListPath_;
    
    // New members for pagination and search state
    std::string currentQuery_;
    size_t currentOffset_;
    const size_t limit_ = 5; // Define the limit for results per page

    void doSearch();
    void displayResults(const std::vector<OnlineBook>& books); // Modified to take books
    void addToReadList(const OnlineBook& b);
    void handleSearchResults(); // New function to manage pagination and user choices
};