#include "MainMenuUI.h"
#include "OnlineBookUI.h"
#include "RecommenderUI.h"
#include "LoanUI.h"
#include "OnlineBookService.h"
#include "RecommenderService.h"
#include "LoanService.h"
#include <iostream>
#include <limits>

void MainMenuUI::run() {
    // --- Service and Database Initialization ---
    // Define the paths to your SQLite database files in the 'data' directory.
    const std::string readListDbPath = "data/test_readlist.db";
    const std::string loanDbPath     = "data/test_loan_requests.db";

    // Instantiate the services. OnlineBookService is now required by LoanService.
    OnlineBookService onlineBookService; 
    RecommenderService recommenderService; // This service is self-contained.
    LoanService loanService(onlineBookService, loanDbPath); // LoanService needs the online service and its DB path.

    // Instantiate the UI components, passing them the services or DB paths they need.
    OnlineBookUI  onlineBookUI(readListDbPath);
    RecommenderUI recommenderUI(readListDbPath);
    LoanUI        loanUI(loanService);

    int choice = 0;
    do {
        std::cout << "\n=== Library Main Menu ===\n"
                  << "1) Search for Books\n"
                  << "2) Get Book Recommendations\n"
                  << "3) Borrow a Book\n"
                  << "4) Exit\n"
                  << "Choice: ";
        
        // Input validation
        while (!(std::cin >> choice) || (choice < 1 || choice > 4)) {
            std::cout << "Invalid choice. Please enter a number between 1 and 4: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: 
                onlineBookUI.run();
                break;
            case 2: 
                recommenderUI.run(); 
                break;
            case 3: 
                loanUI.runMenu(); 
                break;
            case 4: 
                std::cout << "Goodbye!\n"; 
                break;
            default:
                // This case is handled by the validation loop, but good practice to keep.
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);
}