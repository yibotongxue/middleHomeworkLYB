#include <fstream>
#include <iostream>
#include <vector>

#include "utils.hpp"
#include "citation.h"

#include "third_parties/nlohmann/json.hpp"
#include "book.h"
#include "webpage.h"
#include "article.h"

std::vector<Citation*> loadCitations(const std::string& filename) {
    // FIXME: load citations from file
    std::ifstream file{ filename };
    nlohmann::json data = nlohmann::json::parse(file);
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
