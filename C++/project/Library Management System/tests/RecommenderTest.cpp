#include "RecommenderUI.h"
#include <iostream>

#ifndef DATA_DIR
#define DATA_DIR "../data"
#endif

int main() {
    std::cout << "--- Running Isolated Recommender UI Test with SQLite ---\n";
    
    // The UI will use the test database at 'data/test_readlist.db'
    RecommenderUI recommenderInterface(DATA_DIR "/test_readlist.db"); 
    
    // This will start the interactive recommendation flow
    recommenderInterface.run();

    std::cout << "\n--- Isolated Recommender UI Test Complete ---\n";
    return 0;
}