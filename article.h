#pragma once
#ifndef ARTICLE_H
#define ARTICLE_H

#include "citation.h"
#include <vector>

/**
 * @brief Article class represents a citation for an article.
 * 
 * This class extends the functionality of the Citation class to represent
 * a citation for an article. It inherits the unique identifier from the Citation
 * class and contains additional attributes specific to articles, such as title,
 * author, journal, publication year, volume, and issue number.
 * 
 * The Article class provides methods to create, copy, and print article citations.
 * 
 * @note This class is intended to be used as a concrete implementation of the abstract
 *       base class Citation. It implements the pure virtual function print() defined
 *       in the Citation class.
*/
class Article : public Citation {
private:
    std::string title;
    std::vector<std::string> authors;
    std::string journal;
    std::string year;
    int volume;
    int issue;
public:
    /**
     * @brief Delete default constructor for the Article class.
     * 
     * This default constructor is deleted to prevent accidental creation
     * of Article objects without specifying all required attributes, such as
     * the unique identifier, title, authors, journal, publication year, volume, issue.
     * 
     * To create an Article object, u se the constructor with appropriate parameters.
    */
    Article() = delete;

    /**
     * @brief Construct a new Article object with the given attributes.
     * 
     * @param id The unique identifier for the article citation.
     * @param title The title of the article.
     * @param authors The author(s) of the article.
     * @param journal The name of the journal where the article was published.
     * @param year The publication year of the article.
     * @param volume The volume number of the journal.
     * @param issue The issue number of the journal.
    */
    Article(const std::string& id, const std::string& title, const std::vector<std::string>& authors,
     const std::string& journal, const std::string& year, const int volume, const int issue);

    /**
     * @brief Copy constructor for Article objects.
     * 
     * This constructor creates a new Article object as a copy of another Article object.
     * 
     * @param other The Article object to be copied.
    */
    Article(const Article& other);

    virtual ~Article() = default;

    /**
     * @brief Clone the content of another Article object.
     * 
     * This virtual function creates and returns a copy of the current Article object,
     * effectively avoiding the slicing problem. Derived classes should override this
     * function to provide provide proper cloning behavior specific to their type.
     * 
     * @param another The Citation object to clone, must be of type Article.
     * @return A reference to the current Article object.
     * 
     * @note This function overrides the Clone function from the base class Citation.
    */
    virtual Citation& Clone(const Citation& another) override;

    /**
     * @brief Print the article citation information.
     * 
     * This function overrides the pure virtual function print() from the base class Citation.
     * It prints the citation information specific to an Article object, including the article's
     * unique identifier, authors, title, journal, publication year, volume, and issue number.
     * 
     * @note This function does not modify the object's state and is declared as const.
    */
    virtual void print() const override;
};

#endif