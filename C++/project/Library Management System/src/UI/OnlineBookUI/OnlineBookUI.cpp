#include "OnlineBookUI.h"
#include <iostream>
#include <limits>
#include <fstream>

OnlineBookUI::OnlineBookUI(const std::string& readListPath)
  : readListPath_(readListPath)
{}

void OnlineBookUI::run() {
    doSearch();
}

void OnlineBookUI::doSearch() {
    std::cout << "Enter book name: ";
    std::string q; std::getline(std::cin, q);
    auto list = svc_.search(q);

    if (list.empty()) {
        std::cout << "No results.\n";
        return;
    }
    for (size_t i = 0; i < list.size(); ++i) {
        auto &b = list[i];
        std::cout << i+1 << ") " << b.title << " by " << b.author
                  << " (" << b.publishYear << ")\n";
    }
    std::cout << "Add to ReadList? (number or 0 to skip): ";
    int sel; std::cin >> sel;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (sel >= 1 && sel <= (int)list.size()) {
        addToReadList(list[sel-1]);
        std::cout << "Added “" << list[sel-1].title << "”!\n";
    }
}

void OnlineBookUI::addToReadList(const OnlineBook& b) {
    std::ofstream out(readListPath_, std::ios::app);
    out << b.title << " by " << b.author << "\n";
}
