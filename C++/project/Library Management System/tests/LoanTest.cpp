#include "LoanService.h"           // Include the service you want to test
#include "OnlineBookService.h"     // LoanService now depends on OnlineBookService
#include <iostream>
#include <string>
#include <cassert>                 // For basic assertions in tests

// Define DATA_DIR macro if it's not picked up from CMake for standalone test
#ifndef DATA_DIR
#define DATA_DIR "data"
#endif

// Helper function to print a test status
void printTestStatus(const std::string& testName, bool passed) {
    std::cout << "[" << (passed ? "PASS" : "FAIL") << "] " << testName << std::endl;
}

int main() {
    std::cout << "--- Running Automated LoanService Tests ---\n\n";

    // Initialize OnlineBookService (LoanService depends on it)
    OnlineBookService onlineSvc;

    // Define the path for the loan requests database (a test-specific one)
    const std::string loanDbPath = DATA_DIR "/test_loan_requests.db";

    // Instantiate LoanService
    LoanService loanService(onlineSvc, loanDbPath);

    // Test Case 1: Borrow a book that is expected to exist (e.g., "The Lord of the Rings")
    std::string testBook1 = "The Lord of the Rings";
    std::cout << "Test 1: Borrowing existing book: \"" << testBook1 << "\"\n";
    std::optional<LoanResult> result1 = loanService.borrowBook(testBook1);
    printTestStatus("Test 1: Borrow existing book", result1.has_value());
    if (result1.has_value()) {
        std::cout << "  Borrow Date: " << result1->borrowDate << ", Due Date: " << result1->dueDate << "\n";
    }
    std::cout << "\n";

    // Test Case 2: Borrow a book that is NOT expected to exist
    std::string testBook2 = "NonExistentBookXYZ123";
    std::cout << "Test 2: Borrowing non-existent book: \"" << testBook2 << "\"\n";
    std::optional<LoanResult> result2 = loanService.borrowBook(testBook2);
    printTestStatus("Test 2: Borrow non-existent book", !result2.has_value());
    std::cout << "\n";

    // Test Case 3: Borrow another existing book to verify multiple insertions
    std::string testBook3 = "The Hobbit";
    std::cout << "Test 3: Borrowing another existing book: \"" << testBook3 << "\"\n";
    std::optional<LoanResult> result3 = loanService.borrowBook(testBook3);
    printTestStatus("Test 3: Borrow another existing book", result3.has_value());
    if (result3.has_value()) {
        std::cout << "  Borrow Date: " << result3->borrowDate << ", Due Date: " << result3->dueDate << "\n";
    }
    std::cout << "\n";

    std::cout << "--- Automated LoanService Tests Complete ---\n";

    // You can manually inspect 'data/test_loan_requests.db' using a SQLite browser
    // to verify that the loan records were correctly inserted.

    return 0;
}
