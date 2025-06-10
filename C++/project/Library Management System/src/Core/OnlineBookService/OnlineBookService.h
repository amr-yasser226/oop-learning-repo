#pragma once
#include <string>
#include <vector>

struct OnlineBook {
    std::string title;
    std::string author;
    std::string publishYear;
    std::string coverUrl;  // optional
};

class OnlineBookService {
public:
    // Query Open Library for up to `limit` matches
    std::vector<OnlineBook> search(const std::string& query, size_t limit = 10) const;
};
