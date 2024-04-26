#include "book.h"

/**
 * @brief Construct a new Book object.
 * 
 * This constructor initializes a new Book object with the given attributes.
 * 
 * @param id The unique identifier for the book citation.
 * @param authors The author(s) of the book.
 * @param title The title of the book.
 * @param publisher The publisher of the book.
 * @param year The publication year of the book.
*/
Book::Book(const std::string& id, const std::vector<std::string>& authors, const std::string& title,
           const std::string& publisher, const std::string& year) :
           Citation{id}, authors{authors}, title{title}, publisher{publisher}, year{year} {}

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