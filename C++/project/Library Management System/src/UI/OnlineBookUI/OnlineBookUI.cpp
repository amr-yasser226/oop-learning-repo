#include "OnlineBookUI.h"
#include <iostream>
#include <limits> // Required for std::numeric_limits
#include <fstream>
#include <cctype> // Required for toupper

OnlineBookUI::OnlineBookUI(const std::string& readListPath)
  : readListPath_(readListPath), currentOffset_(0) // Initialize currentOffset_
{}

void OnlineBookUI::run() {
    doSearch();
}

void OnlineBookUI::doSearch() {
    // Reset offset for a new search
    currentOffset_ = 0; 
    
    std::cout << "Enter book name: ";
    std::getline(std::cin, currentQuery_); // Store the query

    handleSearchResults(); // Call the new function to manage search and pagination
}

void OnlineBookUI::displayResults(const std::vector<OnlineBook>& books) {
    if (books.empty()) {
        std::cout << "No more results found.\n";
        return;
    }

    std::cout << "\n--- Search Results ---\n";
    for (size_t i = 0; i < books.size(); ++i) {
        const auto& b = books[i];
        // Use currentOffset_ to display correct numbering across pages
        std::cout << currentOffset_ + i + 1 << ") " << b.title
                  << " by " << b.author
                  << " (" << b.publishYear << ")\n";
        
        // Display subjects
        if (!b.subjects.empty()) {
            std::cout << "   Subjects: ";
            for (size_t j = 0; j < b.subjects.size(); ++j) {
                std::cout << b.subjects[j] << (j == b.subjects.size() - 1 ? "" : ", ");
            }
            std::cout << "\n";
        }

        // Display URL
        if (!b.openLibraryUrl.empty()) {
            std::cout << "   URL: " << b.openLibraryUrl << "\n";
        }
        std::cout << "\n";
    }
}

void OnlineBookUI::handleSearchResults() {
    bool continue_searching_session = true; // Controls the pagination loop for a single query

    while (continue_searching_session) {
        auto results = svc_.search(currentQuery_, limit_, currentOffset_);
        
        if (results.empty() && currentOffset_ == 0) {
            std::cout << "No results found for “" << currentQuery_ << "”.\n";
            break; // Exit if no initial results
        }

        displayResults(results);

        if (results.size() < limit_) {
            std::cout << "--- End of results ---\n";
        }

        std::cout << "Add to ReadList? (number or 0 to skip): ";
        int sel;
        std::cin >> sel;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (sel >= 1 && sel <= (int)results.size()) {
            addToReadList(results[sel-1]);
            std::cout << "Added “" << results[sel-1].title << "”!\n";
        }

        // Only prompt for next page/new search if there are more results or it's not the first page
        if (results.size() == limit_ || currentOffset_ > 0) {
            char choice;
            std::cout << "\nOptions: (N)ext Page, (S)earch for a new book, (Q)uit -> ";
            std::cin >> choice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // consume newline

            switch (toupper(choice)) {
                case 'N':
                    if (results.size() < limit_) {
                        std::cout << "No more pages.\n";
                        continue_searching_session = false; // End this search session
                    } else {
                        currentOffset_ += limit_; // Move to the next page
                    }
                    break;
                case 'S':
                    continue_searching_session = false; // End current session, prompt for new search in run()
                    doSearch(); // Start a new search immediately
                    return; // Return from handleSearchResults to avoid further processing in current call
                case 'Q':
                    exit(0); // Exit the entire program
                default:
                    std::cout << "Invalid choice. Returning to main menu.\n";
                    continue_searching_session = false; // End current session
                    break;
            }
        } else {
            // If there were no more results and not on the first page, end session
            continue_searching_session = false;
        }
    }
}

void OnlineBookUI::addToReadList(const OnlineBook& b) {
    std::ofstream out(readListPath_, std::ios::app);
    out << b.title << " by " << b.author << "\n";
}