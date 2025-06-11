#pragma once
#include <string>
#include <vector>

struct OnlineBook {
    std::string title;
    std::string author;
    std::string publishYear;
    std::string coverUrl;           // optional
    std::vector<std::string> subjects; // New: To hold genres/subjects
    std::string openLibraryUrl;     // New: URL to the book's page
};

class OnlineBookService {
public:
    // Query Open Library for up to `limit` matches, starting from `offset`
    std::vector<OnlineBook> search(const std::string& query, size_t limit = 5, size_t offset = 0) const;
};