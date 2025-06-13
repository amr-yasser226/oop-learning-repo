#include "LoanUI.h"
#include <iostream>
#include <limits> // For std::numeric_limits

// Constructor: Takes a reference to the LoanService.
LoanUI::LoanUI(LoanService& svc)
  : svc_(svc)
{}

void LoanUI::runMenu() {
    int choice = 0;
    do {
        std::cout << "\n=== Loan Menu ===\n"
                  << "1) Borrow a book\n"
                  << "2) Back to Main Menu\n"
                  << "Choice: ";
        // Input validation loop for menu choice
        while (!(std::cin >> choice) || (choice < 1 || choice > 2)) {
            std::cout << "Invalid choice. Please enter 1 or 2: ";
            std::cin.clear(); // Clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Consume newline

        switch (choice) {
            case 1: doBorrow(); break;
            case 2: break; // Exit loop
            default: // This default should theoretically not be reached due to validation loop
                std::cout << "An unexpected error occurred with choice selection.\n";
        }
    } while (choice != 2);
}

void LoanUI::doBorrow() {
    std::cout << "Enter book title to borrow: ";
    std::string title;
    std::getline(std::cin, title); // Read the whole line for the title

    auto result = svc_.borrowBook(title); // Call the service to borrow the book

    if (!result) {
        // LoanService will print "Book not found in online catalog." or other errors
        // so no need to print another message here unless you want a specific UI message.
        // For now, assume LoanService's internal logging/messages are sufficient.
    } else {
        std::cout << "Book borrowed successfully!\n";
        std::cout << "  Borrow Date: " << result->borrowDate << "\n"
                  << "  Due Date:    " << result->dueDate   << "\n";
    }
}
