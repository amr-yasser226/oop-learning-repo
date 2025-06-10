#ifndef RECOMMENDER_UI_H
#define RECOMMENDER_UI_H

#include "RecommenderService.h"
#include <string>

class RecommenderUI {
public:
    RecommenderUI(RecommenderService& svc, const std::string& readListPath);
    void runMenu();

private:
    RecommenderService& svc_;
    std::string readListPath_;

    void showTypes();
    void recommendLoop();
};

#endif // RECOMMENDER_UI_H
