#include "BookService.h"
#include "StringUtils.h"
#include <fstream>
#include <sstream>

using util::trim;
using util::toLower;

BookService::BookService(const std::string& booksFilePath)
  : sourceFile_(booksFilePath)
{}

void BookService::load() {
    allBooks_.clear();
    std::ifstream file(sourceFile_);
    std::string line;
    while (std::getline(file, line)) {
        line = trim(line);
        if (line.empty()) continue;
        allBooks_.push_back(parseLine(line));
    }
}

Book BookService::parseLine(const std::string& line) {
    Book b;
    std::istringstream iss(line);
    std::string segment;
    while (std::getline(iss, segment, ',')) {
        auto pos = segment.find(':');
        if (pos == std::string::npos) continue;
        std::string key   = trim(segment.substr(0, pos));
        std::string value = trim(segment.substr(pos + 1));
        if (key == "Title")        b.title       = value;
        else if (key == "Date")    b.date        = value;
        else if (key == "Author")  b.author      = value;
        else if (key == "Description") b.description = value;
        else if (key == "Type")    b.type        = value;
    }
    return b;
}

std::vector<Book> BookService::search(const std::string& query) const {
    std::vector<Book> results;
    auto q = toLower(trim(query));
    for (const auto& b : allBooks_) {
        if (toLower(b.title).find(q) != std::string::npos) {
            results.push_back(b);
        }
    }
    return results;
}

void BookService::addToReadList(const Book& book, const std::string& readListPath) const {
    std::ofstream out(readListPath, std::ios::app);
    out << book.title << " by " << book.author << "\n";
}

std::vector<std::string> BookService::getReadList(const std::string& readListPath) const {
    std::vector<std::string> lines;
    std::ifstream in(readListPath);
    std::string line;
    while (std::getline(in, line)) {
        if (!trim(line).empty())
            lines.push_back(line);
    }
    return lines;
}
