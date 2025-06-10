#include "RecommenderService.h"
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using util::trim;

RecommenderService::RecommenderService(const std::string& recommendationFilePath)
  : sourceFile_(recommendationFilePath)
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

void RecommenderService::load() {
    byType_.clear();
    std::ifstream file(sourceFile_);
    std::string line;
    while (std::getline(file, line)) {
        line = trim(line);
        if (line.empty()) continue;
        Book b = BookService::parseLine(line);
        byType_[b.type].push_back(b);
    }
}

std::vector<std::string> RecommenderService::getTypes() const {
    std::vector<std::string> types;
    for (auto& kv : byType_) {
        types.push_back(kv.first);
    }
    return types;
}

std::vector<Book> RecommenderService::recommend(const std::string& type, size_t count) {
    auto& pool = byType_.at(type);
    auto& last = lastRecs_[type];

    // Exclude last recommendations
    std::vector<Book> candidates;
    for (auto& b : pool) {
        if (std::find(last.begin(), last.end(), b) == last.end()) {
            candidates.push_back(b);
        }
    }
    if (candidates.empty()) {
        candidates = pool;  // reset if exhausted
    }

    // Pick random up to count
    std::vector<Book> result;
    for (size_t i = 0; i < std::min(count, candidates.size()); ++i) {
        size_t idx = std::rand() % candidates.size();
        result.push_back(candidates[idx]);
        candidates.erase(candidates.begin() + idx);
    }
    last = result;
    return result;
}

void RecommenderService::addToReadList(const Book& book, const std::string& readListPath) const {
    std::ofstream out(readListPath, std::ios::app);
    out << book.title << " by " << book.author << "\n";
}
