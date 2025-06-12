#ifndef RECOMMENDER_UI_H
#define RECOMMENDER_UI_H

#include "RecommenderService.h"
#include "ReadListDB.h" // For adding books to the database
#include <string>
#include <vector>

class RecommenderUI {
public:
    explicit RecommenderUI(const std::string& dbPath);
    void run();

private:
    RecommenderService svc_;
    ReadListDB db_;

    std::vector<std::string> currentSubjects_;
    size_t currentOffset_;
    const size_t limit_ = 5;

    void selectGenres();
    void handleRecommendations();
    void displayRecommendations(const std::vector<OnlineBook>& books);
    void promptAndAddBooksToReadList(const std::vector<OnlineBook>& availableBooks);
};

#endif // RECOMMENDER_UI_H