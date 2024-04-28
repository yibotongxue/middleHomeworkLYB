#pragma once
#ifndef ARTICLE_H
#define ARTICLE_H

#include "citation.h"

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
    std::string title;      //!< The title of the article.
    std::string author;     //!< The author(s) of the article.
    std::string journal;    //!< The name of the journal where the article was published.
    int year;               //!< The publication year of the journal.
    int volume;             //!< The volume number of the journal.
    int issue;              //!< The issue number of the journal.
public:
    /**
     * @brief Delete default constructor for the Article class.
     * 
     * This default constructor is deleted to prevent accidental creation
     * of Article objects without specifying all required attributes, such as
     * the unique identifier, title, authors, journal, publication year, volume, issue.
     * 
     * To create an Article object, use the constructor with appropriate parameters.
    */
    Article() = delete;

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
    Article(const std::string& id, const std::string& title, const std::string& author,
     const std::string& journal, const int year, const int volume, const int issue);

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
     * This function prints the citation information specific to an Article object to the specified output stream.
     * It includes the article's unique identifier, title, authors, journal, publication year, volume, and issue number.
     * 
     * @param output The output stream to which the citation information will be printed.
     *               This can be std::cout for printing to the console or any other output stream.
     * 
     * @note This function does not modify the object's state and is declared as const.
     *       The citation information is formatted according to the conventions of an article citation.
     * 
     * @note It is the responsibility of the caller to ensure that the output stream is valid and open for writing.
     *       If the output stream is not valid, the function behavior is undefined.
     * 
     * @note Implementations of this function should avoid modifying the object's state.
     *       The primary purpose of this function is to output the citation information
     *       in a human-readable format to the specified output stream.
    */
    virtual void print(std::ostream& output) const override;
};

#endif