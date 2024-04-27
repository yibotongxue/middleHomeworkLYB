#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <string>

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
        citations.push_back(dynamic_cast<Citation*>(new Book(id, isbn)));
    } 
    else if(type == "webpage") {

        if(!check_string(j, "url")) {
            return false;
        }
        
        auto url = j["url"].get<std::string>();
        citations.push_back(dynamic_cast<Citation*>(new WebPage(id, url)));
    } 
    else if(type == "article") {
        
        if(!check_int(j, "year") || !check_int(j, "volume") || !check_int(j, "issue"))
            return false;

        auto title = j["title"].get<std::string>();
        auto author = j["title"].get<std::string>();
        auto journal = j["journal"].get<std::string>();
        int year = j["year"].get<int>();
        int volume = j["volume"].get<int>();
        int issue = j["issue"].get<int>();

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

/**
 * @brief Load citations from a JSON file and create Citation objects.
 * 
 * This function reads citation data from
 * a JSON file, creates Citation objects based on the data, and returns a vector containing
 * pointers to these objects.
 * 
 * @param filename The path to the JSON file containing citation data.
 * @return A vector containing pointers to the created Citation objects.
 * 
 * @note This function reads JSON data from the specified file and uses it to create Citation objects.
 * 
 * @note If the JSON file cannot be opened or parsed correctly, the function may throw exceptions or
 *       return an empty vector.
 */
std::vector<Citation*> loadCitations(const std::string& filename) {

    std::ifstream file{ filename };

    if(!file.is_open()) {
        std::cout << "文献合集打开文件失败:"  <<  filename << "\n";
        exit(1);
    }

    json data;
    file >> data;

    std::vector<Citation*>citations{};
    createCitations(citations, data);
    return citations;
}

/**
 * @brief Read text from a file and return it as a string.
 * 
 * This function reads the contents of a text file and returns them as a string.
 * 
 * @param filename The path to the text file.
 * @return A string containing the contents of the text file.
 * 
 * @note This function reads the entire contents of the specified file into memory as a string.
 * 
 * @note If the file cannot be opened or read, the function may throw exceptions or return an empty string.
 */
std::string readFromFile(const std::string& filename) {
    std::ifstream file{ filename };

    if(!file.is_open()) {
        std::cout << "输入文件打开失败:" << filename << "\n";
        exit(1);
    }

    try{
        std::string res = std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        return res;
    }
    catch(...) {
        std::exit(1);
    }
    return {};
}

void printCitations(const std::vector<Citation*>& printedCitations, const std::string& input, std::ostream& output) {
    output << input; // Print input text

    output << "\nReferences: \n"; // Print section header for references

    for (auto c : printedCitations) {
        c->print(output); // Print citation
    }
}

int main(int argc, char** argv) {
    // "docman", "-c", "citations.json", "input.txt"
    std::vector<Citation*> citations;
    std::string outputPath = "";
    for(int i = 0; i < argc; i++) {
        if(std::strcmp(argv[i], "-c") == 0) {
            citations = loadCitations(argv[i + 1]);
        }
        if(std::strcmp(argv[i], "-o") == 0) {
            outputPath = argv[i + 1];
        }
    }
    std::vector<Citation*> printedCitations{}; // Vector to store pointers to citations to be printed

    std::string input = "";
    if(strcmp(argv[argc - 1], "-") == 0) {
        std::getline(std::cin, input, '\0');
    }
    else {
        input = readFromFile(argv[argc - 1]);
    }
    std::vector<std::string::size_type>left, right;
    auto it = input.find("[");
    while(it != input.npos) {
        left.push_back(it);
        try{
            it = input.find("[", it + 1);
        }
        catch(...) {
            break;
        }
    }
    it = input.find("]");
    while(it != input.npos) {
        right.push_back(it);
        try{
            it = input.find("]", it + 1);
        }
        catch(...) {
            break;
        }
    }
    if(left.size() == 0 || right.size() == 0 || left.size() != right.size()) std::exit(1); // check for mismatched brackets in input text
    std::vector<std::string>ids;
    for(int i = 0; i < left.size(); i++) {
        ids.push_back(input.substr(left[i] + 1, right[i] - left[i] - 1)); // Extract IDs enclosed in brackets from input text
    }
    std::sort(ids.begin(), ids.end());
    for(auto& id : ids) {
        for(Citation* citation : citations) {
            if(citation->getId() == id)
                printedCitations.push_back(citation);
        }
    }

    if(ids.size() != printedCitations.size()) std::exit(1);

    if(outputPath == "") {
        printCitations(printedCitations, input, std::cout);
    }
    else {
        try{
            std::ofstream output = std::ofstream{outputPath};
            printCitations(printedCitations, input, output);
        }
        catch(...) {
            exit(1);
        }
    }
    for (auto c : citations) {
        delete c; // Deallocate memory for citations
    }
}
