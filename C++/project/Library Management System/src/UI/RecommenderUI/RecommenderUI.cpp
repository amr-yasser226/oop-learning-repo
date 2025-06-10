#include "RecommenderUI.h"
#include <iostream>
#include <limits>

RecommenderUI::RecommenderUI(RecommenderService& svc, const std::string& readListPath)
  : svc_(svc), readListPath_(readListPath)
{}

void RecommenderUI::runMenu() {
    svc_.load();
    int choice = 0;
    do {
        std::cout << "\n=== Recommender Menu ===\n"
                  << "1) List types\n"
                  << "2) Recommend by type\n"
                  << "3) Back to Main Menu\n"
                  << "Choice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (choice) {
            case 1: showTypes();      break;
            case 2: recommendLoop();  break;
            case 3: break;
            default: std::cout << "Invalid\n";
        }
    } while (choice != 3);
}

void RecommenderUI::showTypes() {
    auto types = svc_.getTypes();
    std::cout << "\nAvailable types:\n";
    for (auto& t : types) {
        std::cout << "- " << t << "\n";
    }
}

void RecommenderUI::recommendLoop() {
    std::cout << "Enter type: ";
    std::string type;
    std::getline(std::cin, type);

    auto recs = svc_.recommend(type);
    for (size_t i = 0; i < recs.size(); ++i) {
        std::cout << i+1 << ") " << recs[i].title
                  << " by " << recs[i].author << "\n";
    }

    std::cout << "Add any to ReadList? (number, or 0 to skip): ";
    int sel;
    std::cin >> sel;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (sel > 0 && sel <= (int)recs.size()) {
        svc_.addToReadList(recs[sel-1], readListPath_);
        std::cout << "Added to ReadList!\n";
    }
}
