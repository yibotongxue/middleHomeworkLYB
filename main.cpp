#include <fstream>
#include <iostream>
#include <vector>

#include "utils.hpp"
#include "citation.h"

#include "book.h"
#include "webpage.h"
#include "article.h"

#include "third_parties/nlohmann/json.hpp"
#include "third_parties/cpp-httplib/httplib.h"

httplib::Client client{ API_ENDPOINT };

using json = nlohmann::json;

inline bool check_string(const json& j, const std::string& s) {
    return j.contains(s) && j[s].is_string();
}

inline bool check_int(const json& j, const std::string& s) {
    return j.contains(s) && j[s].is_number();
}

/**
 * @brief Create Citation objects from JSON data and store their pointers in a vector.
 * 
 * This function parses the provided JSON data to create different types of Citation objects
 * based on the "type" field. It then stores the pointers to these objects in the citations vector.
 * 
 * @param citations A vector to store the pointers to the created Citation objects.
 * @param j The JSON data containing information about the Citation objects to be created.
 * @return true if all Citation objects were successfully created and stored, false otherwise.
 * 
 * @note This function expects the JSON data to have "type" and "id" fields to identify the
 *       type and unique identifier of each Citation object. For different types of Citations,
 *       additional fields such as "isbn", "url", or specific attributes are required.
 * 
 * @note The function performs input validation by checking the presence of required fields
 *       and their data types. If any required field is missing or has an invalid type, the
 *       function returns false indicating creation failure.
 * 
 * @note For each type of Citation (book, webpage, article), specific fields are expected
 *       in the JSON data, and their absence or invalidity results in creation failure.
 * 
 * @note If the provided "type" field does not match any supported type (book, webpage, article),
 *       the function returns false indicating creation failure.
 * 
 * @note If an error occurs during the creation of a Citation object, such as a network error
 *       or invalid JSON data, the function returns false indicating creation failure.
 * 
 * @note It is recommended to use try-catch blocks to handle potential exceptions when calling
 *       this function, such as network errors or JSON parsing errors.
*/
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
        citations.push_back(new Book(id, isbn));
    } 
    else if(type == "webpage") {

        if(!check_string(j, "url")) {
            return false;
        }
        
        auto url = j["url"].get<std::string>();
        citations.push_back(new WebPage(id, url));
    } 
    else if(type == "article") {
        
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

/**
 * @brief Recursively create Citation objects from JSON data and store their pointers in a vector.
 * 
 * This function parses the provided JSON data recursively to create different types of Citation objects
 * and stores their pointers in the citations vector. It handles nested JSON structures and arrays.
 * 
 * @param citations A vector to store the pointers to the created Citation objects.
 * @param j The JSON data containing information about the Citation objects to be created.
 * 
 * @note This function recursively traverses the JSON data to handle nested JSON structures and arrays.
 *       It creates Citation objects based on the JSON data and stores their pointers in the citations vector.
 * 
 * @note The JSON data is expected to have a specific format, with each item representing a Citation object.
 *       The function recursively processes each item to create the corresponding Citation objects.
 * 
 * @note This function modifies the citations vector to store the pointers to the created Citation objects.
 *       It does not create copies of the Citation objects, but rather stores pointers to them.
 */
void createCitations(std::vector<Citation*>& citations, const json& j) {
    // Create Citation objects and store their pointers in the citations vector
    if(createCitationsPointer(citations, j))
        return;
    
    // Traverse each item in the JSON data
    for(auto& item : j.items()) {
        // If the item's value is an array, recursively process each element in the array
        if(item.value().is_array()) {
            for(auto& element : item.value()) {
                if(element.is_object()){
                    createCitations(citations, element);
                }
            }
        } 
        // If the item's value is an object, recursively process the object
        else if(item.value().is_object()) {
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

    for (auto c : printedCitations) {
        // output << input;  // print the paragraph first
        output << "\nReferences: \n";
        // FIXME: print citation
    }

    for (auto c : citations) {
        delete c;
    }
}
