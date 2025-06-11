#include "OnlineBookService.h"
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <algorithm>
#include <iostream>

using json = nlohmann::json;

// Helper to URL-encode space→'+'
static std::string encode(const std::string& s) {
    std::string r = s;
    std::replace(r.begin(), r.end(), ' ', '+');
    return r;
}

std::vector<OnlineBook> OnlineBookService::search(const std::string& query, size_t limit, size_t offset) const {
    std::vector<OnlineBook> results;
    // New: Added offset parameter to the URL for pagination
    auto url = "https://openlibrary.org/search.json?q=" + encode(query)
             + "&limit=" + std::to_string(limit)
             + "&offset=" + std::to_string(offset)
             + "&fields=key,title,author_name,first_publish_year,cover_i,subject"; // Specify fields for efficiency

    auto resp = cpr::Get(cpr::Url{url});
    if (resp.status_code != 200) {
        std::cerr << "Error: Failed to fetch data from Open Library (status code: " << resp.status_code << ")\n";
        return results;
    }

    auto j = json::parse(resp.text, nullptr, false);
    if (!j.is_object() || !j.contains("docs")) return results;

    for (auto& doc : j["docs"]) {
        if (!doc.is_object()) continue;
        OnlineBook b;
        b.title       = doc.value("title", "N/A");
        
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

        // New: Extract subjects (genres)
        if (doc.contains("subject") && doc["subject"].is_array()) {
            for (const auto& sub : doc["subject"]) {
                if (b.subjects.size() < 4) { // Limit to first 4 subjects
                    b.subjects.push_back(sub.get<std::string>());
                } else {
                    break;
                }
            }
        }
        
        // New: Construct the URL from the book's key
        if (doc.contains("key") && doc["key"].is_string()) {
            b.openLibraryUrl = "https://openlibrary.org" + doc["key"].get<std::string>();
        }

        results.push_back(std::move(b));
    }
    return results;
}