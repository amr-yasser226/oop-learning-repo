cmake_minimum_required(VERSION 3.16)
project(LibraryManager VERSION 1.0 LANGUAGES CXX)

# -----------------------------------------------------------------------------
#  If this build already has a cache from elsewhere, wipe it now
#  to avoid the “CMakeCache.txt directory is different” error.
# -----------------------------------------------------------------------------
if (EXISTS "${CMAKE_BINARY_DIR}/CMakeCache.txt")
  file(REMOVE "${CMAKE_BINARY_DIR}/CMakeCache.txt")
endif()

# -----------------------------------------------------------------------------
#  C++ standard
# -----------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -----------------------------------------------------------------------------
#  Allow overriding data directory (for books.db, etc.)
# -----------------------------------------------------------------------------
if (NOT DEFINED DATA_DIR)
  set(DATA_DIR "${CMAKE_SOURCE_DIR}/data")
endif()
add_definitions(-DDATA_DIR="${DATA_DIR}")

# -----------------------------------------------------------------------------
#  Find cpr (HTTP) and nlohmann_json (JSON) via vcpkg config
#  Requires you to invoke CMake with:
#    -DCMAKE_TOOLCHAIN_FILE=/home/amr-yasser/vcpkg/scripts/buildsystems/vcpkg.cmake
# -----------------------------------------------------------------------------
find_package(cpr           CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

# -----------------------------------------------------------------------------
#  Define each module as its own library target
# -----------------------------------------------------------------------------

# Book core logic
add_library(book_core
  Book/Book.cpp
)
target_include_directories(book_core PUBLIC
  ${CMAKE_SOURCE_DIR}/Book
)

# Book recommender
add_library(book_recommender
  BookRecommender/BookRecommender.cpp
)
target_include_directories(book_recommender PUBLIC
  ${CMAKE_SOURCE_DIR}/BookRecommender
)

# Feedback/rating
add_library(feedback
  FeedbackRate/FeedbackRate.cpp
)
target_include_directories(feedback PUBLIC
  ${CMAKE_SOURCE_DIR}/FeedbackRate
)

# Loan processing
add_library(loan
  Loan/Loan.cpp
)
target_include_directories(loan PUBLIC
  ${CMAKE_SOURCE_DIR}/Loan
)

# Room booking
add_library(roombooking
  RoomBooking/RoomBooking.cpp
)
target_include_directories(roombooking PUBLIC
  ${CMAKE_SOURCE_DIR}/RoomBooking
)

# Authentication: login + registration
add_library(auth
  Login/Login.cpp
  LoginRegisterHandler/LoginRegisterHandler.cpp
  Register/Register.cpp
)
target_include_directories(auth PUBLIC
  ${CMAKE_SOURCE_DIR}                      # project root
  ${CMAKE_SOURCE_DIR}/Login
  ${CMAKE_SOURCE_DIR}/LoginRegisterHandler
  ${CMAKE_SOURCE_DIR}/Register
  ${CMAKE_SOURCE_DIR}/SubscriptionPlan
)
target_link_libraries(auth
  PUBLIC
    book_core
    book_recommender
    loan
    roombooking
    feedback
    subscription
)

# Subscription plans
add_library(subscription
  SubscriptionPlan/SubscriptionPlan.cpp
)
target_include_directories(subscription PUBLIC
  ${CMAKE_SOURCE_DIR}/SubscriptionPlan
)

# Librarian admin
add_library(librarian
  Librarian/Librarian.cpp
)
target_include_directories(librarian PUBLIC
  ${CMAKE_SOURCE_DIR}/Librarian
)

# Moderator admin
add_library(moderator
  Moderator/Moderator.cpp
)
target_include_directories(moderator PUBLIC
  ${CMAKE_SOURCE_DIR}/Moderator
)

# -----------------------------------------------------------------------------
#  Main application executable
# -----------------------------------------------------------------------------
add_executable(library_app main.cpp)

target_link_libraries(library_app
  PRIVATE
    book_core
    book_recommender
    feedback
    loan
    roombooking
    auth
    subscription
    librarian
    moderator

    # HTTP client and JSON parser
    cpr::cpr
    nlohmann_json::nlohmann_json
)

target_include_directories(library_app PRIVATE
  ${CMAKE_SOURCE_DIR}
)

# -----------------------------------------------------------------------------
#  Platform-specific settings
# -----------------------------------------------------------------------------
if (UNIX)
  find_package(Threads REQUIRED)
  target_link_libraries(library_app PRIVATE Threads::Threads)
endif()

# -----------------------------------------------------------------------------
#  Installation rules (optional)
# -----------------------------------------------------------------------------
install(TARGETS library_app
        RUNTIME DESTINATION bin)

# -----------------------------------------------------------------------------
#  Testing support
# -----------------------------------------------------------------------------
enable_testing()
