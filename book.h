#pragma once
#ifndef BOOK_H
#define BOOK_H

#include "citation.h"

/**
 * @brief Book class represent a book citation.
 * 
 * This class extends the functionality of the Citation class to represent
 * a citation for a book. It inherits the unique identifier from the Citation
 * class and may contain additional attributes specific to books, such as author(s),
 * title, publisher, and publication year.
*/
class Book : public Citation {
private:
    std::string author;     //!< The author(s) of the book.
    std::string title;      //!< The title of the book.
    std::string publisher;  //!< The publisher of the book.
    std::string year;       //!< The publication year of the book.

public:
    /**
     * @brief Delete default constructor for Book class.
     * 
     * This default constructor is deleted to prevent accidental creation
     * of Book objects without specifying required attributes such as author(s),
     * title, publisher, and publication year.
     * 
     * To create a Book object, use the constructor with appropriate parameters.
    */
    Book() = delete;
    
    /**
     * @brief Construct a new Book object with the given attributes.
     * 
     * @param id The unique identifier for the book citation.
     * @param author Ther author(s) of the book.
     * @param title The title of the book.
     * @param publisher The publisher of the book.
     * @param year The publication year of the book.
    */
    Book(const std::string& id, const std::string& author, const std::string& title, const std::string& publisher, const std::string& year);

    /**
     * @brief Construct a new Book object with the given attributes.
     * 
     * This constructor intializes a new Book object with the given attributes.
     * It takes a unique identifier and an ISBN number to fetch book information from an external API.
     * 
     * @param id The unique identifier for the book citation.
     * @param isbn The ISBN number of the book.
    */
    Book(const std::string& id, const std::string& isbn);

    /**
     * @brief Copy constructor for Book class.
     * 
     * This constructor creates a new Book object as a copy of another Book object.
     * 
     * @param another The Book object to be copied.
    */
    Book(const Book& another);

    /**
     * @brief Default virtual destructor for Citation class.
     * 
     * This virtual destructor allows derived classes to properly clean up resources
     * when objects are destroyed. It is provided with a default implementation.
    */
    virtual ~Book() = default;

    /**
     * @brief Clone the content of another Citation object.
     * 
     * This virtual function creates and returns a copy of the current Book object,
     * effectively avoiding the slicing problem. Derived classes should override this
     * function to provide proper cloning behavior specific to their type.
     * 
     * @param another The Citation object to clone.
     * @return A reference to the current Book object.
    */
    virtual Citation& Clone(const Citation& another) override;

    /**
     * @brief Print the book citation information.
     * 
     * This function overrides the pure virtual function print() from the base class Citation.
     * It prints the citation information specific to a Book object to the specified output stream.
     * 
     * @param output The output stream to which the citation information will be printed.
     *               This can be std::cout for printing to the console or any other output stream.
     * 
     * @note This function is declared as const, indicating that it does not modify the object's state.
     *       The citation information is formatted according to the conventions of a book citation.
    */
    virtual void print(std::ostream& output) const override;
};

#endif