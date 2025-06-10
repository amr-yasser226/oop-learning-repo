#ifndef RECOMMENDER_SERVICE_H
#define RECOMMENDER_SERVICE_H

#include <string>
#include <vector>
#include <unordered_map>
#include "BookService.h"    // brings in Book and parseLine
#include "StringUtils.h"    // brings in util::trim

class RecommenderService {
public:
    explicit RecommenderService(const std::string& recommendationFilePath);

    // Load and bucket books by type
    void load();

    // Return all available types
    std::vector<std::string> getTypes() const;

    // Recommend up to count books for a given type
    std::vector<Book> recommend(const std::string& type, size_t count = 2);

    // Persist to read list
    void addToReadList(const Book& book, const std::string& readListPath) const;

private:
    std::string sourceFile_;
    std::unordered_map<std::string, std::vector<Book>> byType_;
    std::unordered_map<std::string, std::vector<Book>> lastRecs_;
};

#endif // RECOMMENDER_SERVICE_H
