#include <fstream>
#include <iostream>
#include <vector>

#include "utils.hpp"
#include "citation.h"

#include "book.h"
#include "webpage.h"
#include "article.h"

#include "third_parties/nlohmann/json.hpp"

using json = nlohmann::json;

inline bool check_string(const json& j, const std::string& s) {
    return j.contains(s) && j[s].is_string();
}

inline bool check_int(const json& j, const std::string& s) {
    return j.contains(s) && j[s].is_number();
}

bool createCitationsPointer(std::vector<Citation*>& citations, const json& j) {
    if(!check_string(j, "type") || !check_string(j, "id"))
        return false;
    auto type = j["type"].get<std::string>();
    auto id = j["id"].get<std::string>();
    if(type == "book") {
        if(!check_string(j, "isbn")) {
            return false;
        }
        auto isbn = j["isbn"].get<std::string>();
    } else if(type == "webpage") {
        if(!check_string(j, "url")) {
            return false;
        }
        auto url = j["url"].get<std::string>();
    } else if(type == "article") {
        if(!check_string(j, "title") || !check_string(j, "author") || !check_string(j, "journal"))
            return false;
        if(!check_int(j, "year") || !check_int(j, "volume") || !check_int(j, "issue"))
            return false;
        auto title = j["title"].get<std::string>();
        auto author = j["title"].get<std::string>();
        auto journal = j["journal"].get<std::string>();
        int year = j["year"];
        int volume = j["volume"];
        int issue = j["issue"];
        citations.push_back(dynamic_cast<Citation*>(new Article(id, title, author, journal, year, volume, issue)));
    } else {
        return false;
    }
    return true;
}

void createCitations(std::vector<Citation*>& citations, const json& j) {
    if(createCitationsPointer(citations, j))
        return;
    for(auto& item : j.items()) {
        if(item.value().is_array()) {
            for(auto& element : item.value()) {
                if(element.is_object()){
                    createCitations(citations, element);
                }
            }
        } else if(item.value().is_object()) {
            createCitations(citations, item.value());
        }
    }
}

std::vector<Citation*> loadCitations(const std::string& filename) {
    // FIXME: load citations from file
}

int main(int argc, char** argv) {
    // "docman", "-c", "citations.json", "input.txt"

    auto citations = loadCitations(argv[2]);
    std::vector<Citation*> printedCitations{};

    // FIXME: read all input to the string, and process citations in the input text
    // auto input = readFromFile(argv[3]);
    // ...

    std::ostream& output = std::cout;

    // output << input;  // print the paragraph first
    // output << "\nReferences:\n";
    
    for (auto c : printedCitations) {
        // FIXME: print citation
    }

    for (auto c : citations) {
        delete c;
    }
}
