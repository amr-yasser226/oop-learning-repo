#include "RecommenderService.h"
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <sstream>

using json = nlohmann::json;

// Helper to URL-encode strings (e.g., spaces to '%20', quotes to '%22')
static std::string url_encode(const std::string& value) {
    std::ostringstream escaped;
    escaped.fill('0');
    escaped << std::hex;

    for (char c : value) {
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            escaped << c;
            continue;
        }
        escaped << std::uppercase;
        escaped << '%' << std::setw(2) << int((unsigned char) c);
        escaped << std::nouppercase;
    }

    return escaped.str();
}


// Provides a hardcoded list of popular and diverse subjects for a better UX.
std::vector<std::string> RecommenderService::getPopularSubjects() const {
    return {
        "Fiction", "Science Fiction", "Fantasy", "Mystery", "Thriller",
        "Romance", "Historical Fiction", "Horror", "Adventure", "Biography",
        "History", "Psychology", "Science", "Business", "Programming", "Art"
    };
}

std::vector<OnlineBook> RecommenderService::recommend(const std::vector<std::string>& subjects, size_t limit, size_t offset) const {
    std::vector<OnlineBook> results;
    if (subjects.empty()) {
        return results;
    }

    // Construct a query by chaining subject filters.
    // e.g., subject:"Science Fiction" subject:"Adventure"
    std::string subjectQuery;
    for (const auto& subject : subjects) {
        subjectQuery += "subject:\"" + subject + "\" ";
    }

    auto url = "https://openlibrary.org/search.json?q=" + url_encode(subjectQuery)
             + "&limit=" + std::to_string(limit)
             + "&offset=" + std::to_string(offset)
             + "&fields=key,title,author_name,first_publish_year,cover_i,subject";

    auto resp = cpr::Get(cpr::Url{url});
    if (resp.status_code != 200) {
        std::cerr << "Error: Failed to fetch recommendations from Open Library (status code: " << resp.status_code << ")\n";
        return results;
    }

    auto j = json::parse(resp.text, nullptr, false);
    if (!j.is_object() || !j.contains("docs")) return results;

    for (auto& doc : j["docs"]) {
        if (!doc.is_object()) continue;
        OnlineBook b;
        b.title = doc.value("title", "N/A");

        if (doc.contains("author_name") && doc["author_name"].is_array() && !doc["author_name"].empty()) {
            b.author = doc["author_name"][0].get<std::string>();
        } else {
            b.author = "Unknown Author";
        }

        b.publishYear = doc.contains("first_publish_year") && doc["first_publish_year"].is_number()
                       ? std::to_string(doc["first_publish_year"].get<int>())
                       : "N/A";

        if (doc.contains("cover_i") && doc["cover_i"].is_number()) {
            b.coverUrl = "https://covers.openlibrary.org/b/id/"
                       + std::to_string(doc["cover_i"].get<int>()) + "-M.jpg";
        }

        if (doc.contains("subject") && doc["subject"].is_array()) {
            for (const auto& sub : doc["subject"]) {
                if (b.subjects.size() < 5) { // Store up to 5 subjects
                    b.subjects.push_back(sub.get<std::string>());
                } else {
                    break;
                }
            }
        }

        if (doc.contains("key") && doc["key"].is_string()) {
            b.openLibraryUrl = "https://openlibrary.org" + doc["key"].get<std::string>();
        }
        results.push_back(std::move(b));
    }
    return results;
}