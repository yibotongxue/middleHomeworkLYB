#include "article.h"
#include <iostream>

/**
 * @brief Construct a new Article object with the given attributes.
 * 
 * @param id The unique identifier for the article citation.
 * @param title The title of the article.
 * @param author The author(s) of the article.
 * @param journal The name of the journal where the article was published.
 * @param year The publication year of the article.
 * @param volume The volume number of the journal.
 * @param issue The issue number of the journal.
 */
Article::Article(const std::string& id, const std::string& title, const std::string&author,
 const std::string& journal, const int year, const int volume, const int issue) :
 Citation{id}, title{title}, author{author}, journal{journal}, year{year}, volume{volume}, issue{issue} {}

/**
 * @brief Copy constructor for Article objects.
 * 
 * This constructor creates a new Article object as a copy of another Article object.
 * 
 * @param other The Article object to be copied.
 */
Article::Article(const Article& other) : Citation{other}, title{other.title}, author{author}, journal{other.journal},
                 year{year}, volume{volume}, issue{issue} {}

/**
 * @brief Clone the content of another Article object.
 * 
 * This function clones the content of another Article object and assigns it to
 * the current Article object, effectively avoiding the slicing problem.
 * 
 * @param another The Article object to clone.
 * @return A reference to the current Article object.
 * 
 * @note This function overrides the Clone function from the base class Citation.
 */
Citation& Article::Clone(const Citation& another) {
    auto aRef = dynamic_cast<const Article&>(another);
    return Article::operator=(aRef);
}

/**
 * @brief Print the article citation information.
 * 
 * This function prints the citation information specific to an Article object.
 * It prints the article's unique identifier, authors, title, journal, publication year,
 * volume, and issue number.
 */
void Article::print() const {
    std::cout << "[" << id << "] article: ";
    for(auto author : author) {
        std::cout << author << ", ";
    }
    std::cout << title << ", " << journal << ", " << year << ", " << volume << ", " << issue << std::endl;
}