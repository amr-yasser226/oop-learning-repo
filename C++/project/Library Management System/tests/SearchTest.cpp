#include "OnlineBookUI.h" // <--- Include the OnlineBookUI header
#include <iostream>
#include <string>
#include <limits> // For std::numeric_limits, used in OnlineBookUI.cpp

// If you want to keep the "SearchTest is a placeholder" message, you can.
// But for an interactive test, we'll replace it.
// Here, we're essentially moving the interactive "main loop" for OnlineBookUI into this test file.

int main() {
    std::cout << "--- Running Isolated Online Book Search UI Test ---\n";

    // You need to pass a path for the read list.
    // Since this is just a test, you can point it to a temporary file
    // or even /dev/null on Linux for testing purposes if you don't care about saving.
    // For now, let's use a dummy path, or even your actual data path.
    // Ensure the 'data' directory exists in your project root for this to work properly.
    OnlineBookUI onlineBookInterface("data/test_readlist.txt"); 

    // This will start the interactive search loop from OnlineBookUI
    onlineBookInterface.run();

    std::cout << "\n--- Isolated Online Book Search UI Test Complete ---\n";

    return 0;
}