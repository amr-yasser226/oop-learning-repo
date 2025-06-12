cmake_minimum_required(VERSION 3.16)
project(LibraryManager VERSION 1.0 LANGUAGES CXX)
# -----------------------------------------------------------------------------
#  If this build already has a cache from elsewhere, wipe it now
# -----------------------------------------------------------------------------
if (EXISTS "${CMAKE_BINARY_DIR}/CMakeCache.txt")
  file(REMOVE "${CMAKE_BINARY_DIR}/CMakeCache.txt")
endif()
# -----------------------------------------------------------------------------
#  C++17
# -----------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# -----------------------------------------------------------------------------
#  Override data directory (for library.db, etc.)
# -----------------------------------------------------------------------------
if (NOT DEFINED DATA_DIR)
  set(DATA_DIR "${CMAKE_SOURCE_DIR}/data")
endif()
add_definitions(-DDATA_DIR="${DATA_DIR}") # Defines DATA_DIR preprocessor macro
# -----------------------------------------------------------------------------
#  Find external dependencies via vcpkg toolchain
# -----------------------------------------------------------------------------
find_package(cpr           CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
# Use CMake’s built-in FindSQLite3 module
find_package(SQLite3 REQUIRED)
# -----------------------------------------------------------------------------
#  Build the main application from all src/ files
# -----------------------------------------------------------------------------
add_executable(library_app
  src/main.cpp
  # Core
  src/Core/Utils/StringUtils.cpp
  src/Core/OnlineBookService/OnlineBookService.cpp
  src/Core/LoanService/LoanService.cpp
  src/Core/RecommenderService/RecommenderService.cpp
  src/Core/Database/ReadListDB.cpp 
  # UI
  src/UI/OnlineBookUI/OnlineBookUI.cpp
  src/UI/LoanUI/LoanUI.cpp
  src/UI/RecommenderUI/RecommenderUI.cpp
  src/UI/MainMenuUI/MainMenuUI.cpp
)
# -----------------------------------------------------------------------------
#  Test: standalone OnlineBookService search (runs the UI test)
# -----------------------------------------------------------------------------
add_executable(search_test
  tests/SearchTest.cpp
  src/Core/OnlineBookService/OnlineBookService.cpp
  src/UI/OnlineBookUI/OnlineBookUI.cpp 
  src/Core/Database/ReadListDB.cpp
  src/Core/Utils/StringUtils.cpp # OnlineBookUI might use it
)
target_include_directories(search_test PRIVATE
  ${CMAKE_SOURCE_DIR}/src/Core/OnlineBookService
  ${CMAKE_SOURCE_DIR}/src/UI/OnlineBookUI
  ${CMAKE_SOURCE_DIR}/src/Core/Database 
  ${CMAKE_SOURCE_DIR}/src/Core/Utils
)
target_link_libraries(search_test PRIVATE
  cpr::cpr
  nlohmann_json::nlohmann_json
  SQLite::SQLite3 
)
# -----------------------------------------------------------------------------
#  NEW TEST: standalone Recommender Service (runs the UI test)
# -----------------------------------------------------------------------------
add_executable(recommender_test
  tests/RecommenderTest.cpp
  src/UI/RecommenderUI/RecommenderUI.cpp
  src/Core/RecommenderService/RecommenderService.cpp
  src/Core/Database/ReadListDB.cpp
  # The service files below are included because Recommender needs OnlineBook struct and utils
  src/Core/OnlineBookService/OnlineBookService.cpp
  src/Core/Utils/StringUtils.cpp
)
target_include_directories(recommender_test PRIVATE
  ${CMAKE_SOURCE_DIR}/src/UI/RecommenderUI
  ${CMAKE_SOURCE_DIR}/src/Core/RecommenderService
  ${CMAKE_SOURCE_DIR}/src/Core/Database
  ${CMAKE_SOURCE_DIR}/src/Core/OnlineBookService # For OnlineBook struct
  ${CMAKE_SOURCE_DIR}/src/Core/Utils
)
target_link_libraries(recommender_test PRIVATE
  cpr::cpr
  nlohmann_json::nlohmann_json
  SQLite::SQLite3
)
# -----------------------------------------------------------------------------
#  Include paths (for main library_app)
# -----------------------------------------------------------------------------
target_include_directories(library_app PRIVATE
  ${CMAKE_SOURCE_DIR}/src/Core
  ${CMAKE_SOURCE_DIR}/src/Core/Utils
  ${CMAKE_SOURCE_DIR}/src/Core/OnlineBookService
  ${CMAKE_SOURCE_DIR}/src/Core/LoanService
  ${CMAKE_SOURCE_DIR}/src/Core/RecommenderService
  ${CMAKE_SOURCE_DIR}/src/Core/Database 
  ${CMAKE_SOURCE_DIR}/src/UI/OnlineBookUI
  ${CMAKE_SOURCE_DIR}/src/UI/RecommenderUI
  ${CMAKE_SOURCE_DIR}/src/UI/LoanUI
  ${CMAKE_SOURCE_DIR}/src/UI/MainMenuUI
)
# -----------------------------------------------------------------------------
#  Link libraries (for main library_app)
# -----------------------------------------------------------------------------
target_link_libraries(library_app PRIVATE
  # HTTP + JSON
  cpr::cpr
  nlohmann_json::nlohmann_json
  # SQLite C API
  SQLite::SQLite3
  # Threads
  Threads::Threads
)
# -----------------------------------------------------------------------------
#  Install rule
# -----------------------------------------------------------------------------
install(TARGETS library_app RUNTIME DESTINATION bin)
# -----------------------------------------------------------------------------
#  Testing support
# -----------------------------------------------------------------------------
enable_testing()