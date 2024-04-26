#include "book.h"
#include <iostream>

/**
 * @brief Construct a new Book object.
 * 
 * This constructor initializes a new Book object with the given attributes.
 * 
 * @param id The unique identifier for the book citation.
 * @param author The author(s) of the book.
 * @param title The title of the book.
 * @param publisher The publisher of the book.
 * @param year The publication year of the book.
*/
Book::Book(const std::string& id, const std::string& author, const std::string& title,
           const std::string& publisher, const int year) :
           Citation{id}, author{author}, title{title}, publisher{publisher}, year{year} {}
           
/**
 * @brief Copy constructor for Book class.
 * 
 * This constructor creates a new Book object as a copy of another Book object.
 * 
 * @param another The Book object to be copied.
 */
Book::Book(const Book& other)
          : Citation(other), author(other.author), title(other.title),
            publisher(other.publisher), year(other.year) {}

/**
 * @brief Clone the content of another Book object.
 * 
 * This function clones the content of another Book object and assigns it to
 * the current Book object, effecively avoiding the slicing problem.
 * 
 * @param another The Book object to clone.
 * @return A referenct to the current Book object.
 * 
 * @note This function overrides the Clone function from the Citation class.
*/
Citation& Book::Clone(const Citation& another) {
    auto bRef = dynamic_cast<const Book&>(another);
    return Book::operator=(bRef);
}

/**
 * @brief Print the book citation information.
 * 
 * This function prints the citation information specific to a Book object.
 * It prints the book's unique identifier, authors, title, publisher, and publication year.
 * 
 * @note This function dose not modify the object's state and is declared as const.
 * @note This function is an overload of the print() function from the base class Citation.
*/
void Book::print() const {
   std::cout << "[" << id << "] book: " << author << ", " << title << ", " << publisher << ", " << year << std::endl;    
}