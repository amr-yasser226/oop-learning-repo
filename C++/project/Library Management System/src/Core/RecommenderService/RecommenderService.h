#ifndef RECOMMENDER_SERVICE_H
#define RECOMMENDER_SERVICE_H

#include "OnlineBookService.h" // For the OnlineBook struct
#include <string>
#include <vector>

class RecommenderService {
public:
    // Provides a curated list of popular subjects/genres for the user to choose from.
    std::vector<std::string> getPopularSubjects() const;

    // Recommends books from the Open Library API based on a list of subjects.
    // Supports pagination with limit and offset.
    std::vector<OnlineBook> recommend(const std::vector<std::string>& subjects, size_t limit = 5, size_t offset = 0) const;
};

#endif // RECOMMENDER_SERVICE_H