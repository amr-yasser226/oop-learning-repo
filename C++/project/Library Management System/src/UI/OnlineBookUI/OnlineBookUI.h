#pragma once
#include "OnlineBookService.h"
#include <string>

class OnlineBookUI {
public:
    OnlineBookUI(const std::string& readListPath);
    void run();

private:
    OnlineBookService svc_;
    std::string readListPath_;

    void doSearch();
    void addToReadList(const OnlineBook& b);
};
