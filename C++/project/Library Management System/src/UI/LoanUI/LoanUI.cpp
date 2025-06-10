#include "LoanUI.h"
#include <iostream>
#include <limits>

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
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (choice) {
            case 1: doBorrow(); break;
            case 2: break;
            default: std::cout << "Invalid\n";
        }
    } while (choice != 2);
}

void LoanUI::doBorrow() {
    std::cout << "Enter book title to borrow: ";
    std::string title;
    std::getline(std::cin, title);
    auto result = svc_.borrowBook(title);
    if (!result) {
        std::cout << "Book not found in catalog.\n";
    } else {
        std::cout << "Borrow Date: " << result->borrowDate << "\n"
                  << "Due Date:    " << result->dueDate   << "\n";
    }
}
