#include "OnlineBookUI.h"
#include <iostream>
#include <limits>    // Required for std::numeric_limits
#include <sstream>   // Required for std::istringstream for parsing multiple numbers
#include <cctype>    // Required for toupper
#include <algorithm> // Required for std::sort and std::unique

// Constructor: Initialize the ReadListDB with the provided database path.
OnlineBookUI::OnlineBookUI(const std::string& dbPath)
  : svc_(), db_(dbPath), currentOffset_(0) // Initialize db_ member
{}

void OnlineBookUI::run() {
    doSearch();
}

void OnlineBookUI::doSearch() {
    currentOffset_ = 0; // Reset offset for a new search
    
    std::cout << "Enter book name: ";
    std::getline(std::cin, currentQuery_); // Store the query

    handleSearchResults(); // Call the function to manage search and pagination
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
        // Numbers displayed to user start from currentOffset_ + 1
        std::cout << currentOffset_ + i + 1 << ") " << b.title
                  << " by " << b.author
                  << " (" << b.publishYear << ")\n";
        
        // Display subjects (genres)
        if (!b.subjects.empty()) {
            std::cout << "   Subjects: ";
            for (size_t j = 0; j < b.subjects.size(); ++j) {
                std::cout << b.subjects[j] << (j == b.subjects.size() - 1 ? "" : ", ");
            }
            std::cout << "\n";
        }

        // Display Open Library URL
        if (!b.openLibraryUrl.empty()) {
            std::cout << "   URL: " << b.openLibraryUrl << "\n";
        }
        std::cout << "\n";
    }
}

// This function now manages the loop for prompting and validating book selections.
void OnlineBookUI::promptAndAddBooksToReadList(const std::vector<OnlineBook>& availableBooks) {
    // If no books are available to select, simply return.
    if (availableBooks.empty()) {
        std::cout << "No books displayed to add to read list.\n";
        return;
    }

    bool selectionComplete = false;
    while (!selectionComplete) {
        std::string input;
        std::cout << "Add to ReadList? (Enter numbers, space-separated, or 0 to skip): ";
        std::getline(std::cin, input);

        if (input == "0") {
            std::cout << "Skipping addition to ReadList.\n";
            return; // User chose to skip
        }

        std::istringstream iss(input);
        int selection_num;
        std::vector<size_t> validIndicesToProcess;
        std::vector<int> invalidNumbersEntered;

        // Parse all numbers from the input string and categorize them
        while (iss >> selection_num) {
            // Calculate the 0-based index of the book in the *currently displayed* results vector.
            // User input is 1-based and also relative to the overall search offset.
            // Example: if currentOffset = 5, and displayed books are 6, 7, 8, 9, 10
            // User inputs 6, its index in `availableBooks` (which is size 5) is 0.
            // So: selection_num - (currentOffset_ + 1)
            size_t indexInDisplayedResults = static_cast<size_t>(selection_num) - (currentOffset_ + 1);

            // Check if the number is within the valid range for the *currently displayed* books
            if (selection_num >= static_cast<int>(currentOffset_ + 1) &&
                selection_num <= static_cast<int>(currentOffset_ + availableBooks.size())) {
                validIndicesToProcess.push_back(indexInDisplayedResults);
            } else {
                invalidNumbersEntered.push_back(selection_num);
            }
        }

        // --- Handle Invalid Inputs ---
        if (!invalidNumbersEntered.empty()) {
            std::cout << "Error: The following numbers were invalid selections: ";
            for (size_t i = 0; i < invalidNumbersEntered.size(); ++i) {
                std::cout << invalidNumbersEntered[i] << (i == invalidNumbersEntered.size() - 1 ? "" : ", ");
            }
            std::cout << ".\n";
            // Provide the correct range for the *current page of results*.
            std::cout << "Please enter numbers between " << (currentOffset_ + 1) << " and "
                      << (currentOffset_ + availableBooks.size()) << ", or 0 to skip.\n";
            // Loop continues for new input
        } 
        // --- Handle No Valid Numbers Entered (but not '0' and not just invalid numbers) ---
        else if (validIndicesToProcess.empty() && input != "0") {
             std::cout << "No valid selection found in your input. ";
             std::cout << "Please enter numbers between " << (currentOffset_ + 1) << " and "
                      << (currentOffset_ + availableBooks.size()) << ", or 0 to skip.\n";
        }
        // --- Process Valid Inputs ---
        else {
            // All entered numbers were valid for the current page
            // Sort and unique to avoid double additions if user enters '1 1'
            std::sort(validIndicesToProcess.begin(), validIndicesToProcess.end());
            validIndicesToProcess.erase(std::unique(validIndicesToProcess.begin(), validIndicesToProcess.end()), validIndicesToProcess.end());

            bool anyAddedSuccessfully = false;
            for (size_t index : validIndicesToProcess) {
                const OnlineBook& bookToAdd = availableBooks[index];
                if (db_.insertBook(bookToAdd)) { // Use the database class to insert
                    std::cout << "Successfully added “" << bookToAdd.title << "” to read list.\n";
                    anyAddedSuccessfully = true;
                } else {
                    std::cerr << "Failed to add “" << bookToAdd.title << "” to the database.\n";
                }
            }

            if (anyAddedSuccessfully) {
                std::cout << "Read list update complete.\n";
            } else if (!validIndicesToProcess.empty()) {
                // This case happens if all selected books failed to add (e.g., database error)
                std::cout << "No books were successfully added (check database connection/errors).\n";
            }
            selectionComplete = true; // Exit the loop after processing valid selections
        }
    }
}


// In src/UI/OnlineBookUI/OnlineBookUI.cpp

void OnlineBookUI::handleSearchResults() {
    bool continue_pagination_session = true; 

    while (continue_pagination_session) {
        auto results = svc_.search(currentQuery_, limit_, currentOffset_);
        
        if (results.empty() && currentOffset_ == 0) {
            std::cout << "No results found for “" << currentQuery_ << "”.\n";
            break; 
        }

        displayResults(results);

        if (results.size() < limit_) {
            std::cout << "--- End of results ---\n";
        }
        
        promptAndAddBooksToReadList(results);

        bool validChoiceMade = false;
        while (!validChoiceMade) {
            char choice;
            // Changed "(Q)uit" to "(M)ain Menu"
            std::cout << "\nOptions: (N)ext Page, (S)earch again, (M)ain Menu -> ";
            std::cin >> choice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            switch (toupper(choice)) {
                case 'N':
                    if (results.empty() || results.size() < limit_) { 
                        std::cout << "No more pages available. ";
                        validChoiceMade = false;
                    } else {
                        currentOffset_ += limit_;
                        validChoiceMade = true;
                    }
                    break;
                case 'S':
                    doSearch();
                    return;
                case 'M': // Changed from 'Q'
                    // Set flags to exit the loops and return to main menu
                    continue_pagination_session = false;
                    validChoiceMade = true;
                    break;
                default:
                    std::cout << "Invalid choice. Please enter (N), (S), or (M).\n";
                    break;
            }
        }
    }
}