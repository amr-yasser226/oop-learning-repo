#include "MainMenuUI.h"
#include "OnlineBookUI.h"
#include <RecommenderUI.h>
#include <LoanUI.h>
#include <OnlineBookService.h>
#include <RecommenderService.h>
#include <LoanService.h>
#include <iostream>
#include <limits>


void MainMenuUI::run() {
    // Paths can be driven from config or DATA_DIR
    const std::string booksFile   = "data/Book/books.txt";
    const std::string recFile     = "data/BookRecommender/Recommendation.txt";
    const std::string readList    = "data/ReadList/ReadList.txt";
    const std::string loanReqFile = "data/Loan/requests.txt";

    BookService        bs(booksFile);
    RecommenderService rs(recFile);
    LoanService        ls(booksFile, loanReqFile);

    BookUI             bui(bs, readList);
    RecommenderUI      rui(rs, readList);
    LoanUI             lui(ls);

    int choice = 0;
    do {
        std::cout << "\n=== Main Menu ===\n"
                  << "1) Books\n"
                  << "2) Recommendations\n"
                  << "3) Loans\n"
                  << "4) Exit\n"
                  << "Choice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: 
                bui.runMenu();
                // Online lookup instead of local file
                OnlineBookUI(obt::readListPath).run();
                break;
            case 2: rui.runMenu(); break;
            case 3: lui.runMenu(); break;
            case 4: std::cout << "Goodbye!\n"; break;
            default: std::cout << "Invalid choice\n";
        }
    } while (choice != 4);
}
