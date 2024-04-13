#include <fstream>
#include <iostream>
#include <vector>

#include "utils.hpp"
#include "citation.h"

std::vector<Citation*> loadCitations(const std::string& filename) {
    // FIXME: load citations from file
}

int main(int argc, char** argv) {
    // "docman", "-c", "citations.json", "input.txt"

    auto citations = loadCitations(argv[2]);
    std::vector<Citation*> printedCitations{};

    auto input = readFromFile(argv[3]);

    // FIXME: process citations in the input text

    std::ostream& output = std::cout;

    for (auto c : printedCitations) {
        output << input;
        output << "\nReference: \n";
        // FIXME: print citation
    }

    for (auto c : citations) {
        delete c;
    }
}