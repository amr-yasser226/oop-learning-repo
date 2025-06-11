#include "OnlineBookUI.h" // Include the OnlineBookUI header
#include <iostream>
#include <string>
#include <limits>

// Define DATA_DIR macro. This tells the compiler where to find your 'data' folder.
// This is typically passed by CMake, but for a standalone test that relies on it,
// defining it here as a relative path from the *build directory* where the executable runs
// ensures it's available.
#ifndef DATA_DIR
#define DATA_DIR "../data"
#endif

int main() {
    std::cout << "--- Running Isolated Online Book Search UI Test with SQLite ---\n";

    // Pass the path to your SQLite database file.
    // Using DATA_DIR ensures it goes into your project's data folder.
    // For this test, it will create/use 'data/test_readlist.db'.
    OnlineBookUI onlineBookInterface(DATA_DIR "/test_readlist.db"); 

    // This will start the interactive search loop from OnlineBookUI
    onlineBookInterface.run();

    std::cout << "\n--- Isolated Online Book Search UI Test Complete ---\n";

    return 0;
}
