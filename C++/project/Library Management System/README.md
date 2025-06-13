# Library Management System

A comprehensive, console‑based Library Management System written in modern C++.  
Interact with a vast online book catalog, receive personalized recommendations, and manage loans through a clean, intuitive CLI. Designed with a clear, layered architecture for scalability and maintainability.

---

## Table of Contents

1. [Features](#features)  
2. [Architecture](#architecture)  
3. [Technology Stack](#technology-stack)  
4. [Project Structure](#project-structure)  
5. [Installation](#installation)  
6. [Usage](#usage)  
7. [Data Storage](#data-storage)  
8. [Testing](#testing)  
9. [Contributing](#contributing)  
10. [License](#license)  

---

## Features

- **Online Book Search**  
  Connect to the Open Library API to search millions of titles.  
- **Personalized Recommendations**  
  Suggest books based on popular genres and user history.  
- **Local Database Storage**  
  Persist reading lists and loan records via SQLite.  
- **Pagination**  
  Navigate large result sets with ease.  
- **Robust Input Handling**  
  User‑friendly CLI with graceful error recovery.  
- **Modular OOP Design**  
  Clear separation of UI, business logic, and data access layers.  
- **Automated & Manual Testing**  
  Suite of unit tests for core services and interactive UI test modules.  

---

## Architecture

Layered design ensures that each concern is isolated:

- **UI Layer** (`src/UI/`)  
  - `MainMenuUI` – Entry point and navigation  
  - `OnlineBookUI` – Book search workflows  
  - `RecommenderUI` – Recommendation interaction  
  - `LoanUI` – Borrowing flow  

- **Service Layer** (`src/Core/`)  
  - `OnlineBookService` – API integration  
  - `RecommenderService` – Recommendation logic  
  - `LoanService` – Loan management and due‑date calculation  

- **Data Layer** (`src/Core/Database/`)  
  - `ReadListDB` – User reading list storage  
  - `LoanRequestDB` – Loan record storage  

---

## Technology Stack

- **Language:** C++17  
- **Build System:** CMake ≥ 3.16  
- **Package Manager:** vcpkg  
- **Libraries:**  
  - [cpr](https://github.com/libcpr/cpr) – HTTP requests  
  - [nlohmann/json](https://github.com/nlohmann/json) – JSON parsing  
  - SQLite3 – Embedded database  

---

## Project Structure

```
.
├── data/
│   ├── test\_loan\_requests.db
│   └── test\_readlist.db
├── src/
│   ├── Core/
│   │   ├── Database/
│   │   ├── LoanService/
│   │   ├── OnlineBookService/
│   │   ├── RecommenderService/
│   │   └── Utils/
│   ├── UI/
│   │   ├── LoanUI/
│   │   ├── MainMenuUI/
│   │   ├── OnlineBookUI/
│   │   └── RecommenderUI/
│   └── main.cpp
├── tests/
│   ├── LoanTest.cpp
│   ├── RecommenderTest.cpp
│   └── SearchTest.cpp
├── .gitignore
└── CMakeLists.txt

```

---

## Installation

### Prerequisites

- C++17‑compatible compiler (GCC, Clang, MSVC)  
- CMake ≥ 3.16  
- Git  
- [vcpkg](https://github.com/microsoft/vcpkg)  

### Steps

1. **Clone the repo**  
   ```bash
   git clone https://github.com/amr-yasser226/oop-learning-repo.git
   cd oop-learning-repo/C++/project/Library\ Management\ System

2. **Install dependencies**

   ```bash
   vcpkg install cpr nlohmann-json sqlite3
   ```
3. **Configure & build**

   ```bash
   cmake -B build -S . \
     -DCMAKE_TOOLCHAIN_FILE=<path-to-vcpkg>/scripts/buildsystems/vcpkg.cmake
   cmake --build build
   ```

---

## Usage

Run the application:

```bash
./build/library_app
```

```text
=== Library Main Menu ===
1) Search for Books
2) Get Book Recommendations
3) Borrow a Book
4) Exit
Choice:
```

* **1)** Search and add books to your reading list
* **2)** Browse recommendations by genre
* **3)** Request a loan by title
* **4)** Exit

---

## Data Storage

* **`data/test_readlist.db`** – Saved search/recommendation books
* **`data/test_loan_requests.db`** – All loan request records

Databases are auto‑created on first run.

---

## Testing

After building, run tests from the project root:

* **Loan Service Tests**

  ```bash
  ./build/loan_test
  ```
* **Search UI Test**

  ```bash
  ./build/search_test
  ```
* **Recommender UI Test**

  ```bash
  ./build/recommender_test
  ```

---

## Contributing

1. Fork the repo
2. Create a branch: `git checkout -b feature/YourFeature`
3. Commit: `git commit -m "Add feature"`
4. Push: `git push origin feature/YourFeature`
5. Open a Pull Request

Please follow existing coding style and ensure all tests pass.

---

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

