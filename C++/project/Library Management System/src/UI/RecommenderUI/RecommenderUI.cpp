#include "RecommenderUI.h"
#include <iostream>
#include <limits>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype>

RecommenderUI::RecommenderUI(const std::string& dbPath)
  : svc_(), db_(dbPath), currentOffset_(0) {}

void RecommenderUI::run() {
    selectGenres();
}

void RecommenderUI::selectGenres() {
    auto available_genres = svc_.getPopularSubjects();
    
    while (true) {
        std::cout << "\n--- Book Recommendation Service ---\n";
        std::cout << "Please select one or more genres by number (space-separated):\n";
        for (size_t i = 0; i < available_genres.size(); ++i) {
            std::cout << i + 1 << ") " << available_genres[i] << "\n";
        }
        std::cout << "Your choice(s): ";

        std::string line;
        std::getline(std::cin, line);
        std::istringstream iss(line);
        int num;
        std::vector<std::string> chosen_genres;
        std::vector<int> invalid_nums;

        while (iss >> num) {
            if (num > 0 && static_cast<size_t>(num) <= available_genres.size()) {
                chosen_genres.push_back(available_genres[num - 1]);
            } else {
                invalid_nums.push_back(num);
            }
        }

        if (!invalid_nums.empty()) {
            std::cout << "Error: Invalid selection(s): ";
            for (int invalid : invalid_nums) std::cout << invalid << " ";
            std::cout << "\nPlease choose numbers between 1 and " << available_genres.size() << ".\n";
            continue; // Ask again
        }

        if (chosen_genres.empty()) {
            std::cout << "Error: You must select at least one genre.\n";
            continue; // Ask again
        }
        
        // Remove duplicates
        std::sort(chosen_genres.begin(), chosen_genres.end());
        chosen_genres.erase(std::unique(chosen_genres.begin(), chosen_genres.end()), chosen_genres.end());
        
        currentSubjects_ = chosen_genres;
        handleRecommendations();
        break; // Exit genre selection loop
    }
}


void RecommenderUI::handleRecommendations() {
    currentOffset_ = 0; // Reset for new recommendation session
    bool continue_recommendation_session = true;

    std::cout << "\nFetching recommendations for: ";
    for(size_t i = 0; i < currentSubjects_.size(); ++i) {
        std::cout << "'" << currentSubjects_[i] << "'" << (i == currentSubjects_.size() - 1 ? "" : ", ");
    }
    std::cout << "\n";

    while (continue_recommendation_session) {
        auto recommendations = svc_.recommend(currentSubjects_, limit_, currentOffset_);
        
        if (recommendations.empty() && currentOffset_ == 0) {
            std::cout << "No recommendations found for the selected combination of genres.\n";
            selectGenres(); // Go back to genre selection
            return;
        }
        
        displayRecommendations(recommendations);
        
        if (recommendations.size() < limit_) {
            std::cout << "--- End of results ---\n";
        }

        promptAndAddBooksToReadList(recommendations);

        bool validChoiceMade = false;
        while (!validChoiceMade) {
            char choice;
            std::cout << "\nOptions: (N)ext Page, (R)etry with new genres, (Q)uit -> ";
            std::cin >> choice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // consume newline

            switch (toupper(choice)) {
                case 'N':
                    if (recommendations.size() < limit_) {
                        std::cout << "No more pages available. Please make another choice.\n";
                    } else {
                        currentOffset_ += limit_;
                        validChoiceMade = true; // Continue recommendation loop
                    }
                    break;
                case 'R':
                    selectGenres(); // Start a new genre selection
                    return; // Exit current handler
                case 'Q':
                    exit(0);
                default:
                    std::cout << "Invalid choice. Please enter 'N', 'R', or 'Q'.\n";
                    break;
            }
        }
    }
}

void RecommenderUI::displayRecommendations(const std::vector<OnlineBook>& books) {
    if (books.empty()) {
        std::cout << "No more recommendations found.\n";
        return;
    }

    std::cout << "\n--- Recommended Books ---\n";
    for (size_t i = 0; i < books.size(); ++i) {
        const auto& b = books[i];
        std::cout << currentOffset_ + i + 1 << ") " << b.title
                  << " by " << b.author
                  << " (" << b.publishYear << ")\n";
        
        if (!b.subjects.empty()) {
            std::cout << "   Subjects: ";
            for (size_t j = 0; j < b.subjects.size(); ++j) {
                std::cout << b.subjects[j] << (j == b.subjects.size() - 1 ? "" : ", ");
            }
            std::cout << "\n";
        }
        if (!b.openLibraryUrl.empty()) {
            std::cout << "   URL: " << b.openLibraryUrl << "\n";
        }
        std::cout << "\n";
    }
}

void RecommenderUI::promptAndAddBooksToReadList(const std::vector<OnlineBook>& availableBooks) {
    if (availableBooks.empty()) {
        return;
    }
    
    while (true) {
        std::string input;
        std::cout << "Add to ReadList? (Enter numbers, space-separated, or 0 to skip): ";
        std::getline(std::cin, input);

        if (input == "0") {
            std::cout << "Skipping addition to ReadList.\n";
            return;
        }

        std::istringstream iss(input);
        int selection_num;
        std::vector<size_t> validIndices;
        std::vector<int> invalidNumbers;

        while (iss >> selection_num) {
            size_t indexInPage = static_cast<size_t>(selection_num) - (currentOffset_ + 1);
            if (selection_num > 0 && static_cast<size_t>(selection_num) >= (currentOffset_ + 1) && indexInPage < availableBooks.size()) {
                validIndices.push_back(indexInPage);
            } else {
                invalidNumbers.push_back(selection_num);
            }
        }

        if (!invalidNumbers.empty()) {
            std::cout << "Error: Invalid number(s): ";
            for(int num : invalidNumbers) std::cout << num << " ";
            std::cout << "\nPlease enter numbers between " << (currentOffset_ + 1) << " and " << (currentOffset_ + availableBooks.size()) << ".\n";
            continue; // Ask for input again
        }

        if (validIndices.empty()) {
            std::cout << "No valid selection found. Please try again.\n";
            continue;
        }

        std::sort(validIndices.begin(), validIndices.end());
        validIndices.erase(std::unique(validIndices.begin(), validIndices.end()), validIndices.end());
        
        bool anyAdded = false;
        for (size_t index : validIndices) {
            const OnlineBook& bookToAdd = availableBooks[index];
            if (db_.insertBook(bookToAdd)) {
                std::cout << "Successfully added “" << bookToAdd.title << "” to read list.\n";
                anyAdded = true;
            } else {
                std::cerr << "Failed to add “" << bookToAdd.title << "” to the database.\n";
            }
        }

        if (anyAdded) {
            std::cout << "Read list update complete.\n";
        }
        break; // Exit loop after processing
    }
}