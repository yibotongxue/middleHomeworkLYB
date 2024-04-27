#include "book.h"
#include <iostream>
#include <typeinfo>
#include <stdexcept>
#include "third_parties/cpp-httplib/httplib.h"
#include "third_parties/nlohmann/json.hpp"
#include "utils.hpp"

extern httplib::Client client;

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
           const std::string& publisher, const std::string& year) :
           Citation{id}, author{author}, title{title}, publisher{publisher}, year{year} {}

/**
 * @brief Construct a new Book object.
 * 
 * This constructor initializes a new Book object with the given attributes.
 * It retrieves additional information about the book from an external API using the ISBN.
 * 
 * @param id The unique identifier for the book citation.
 * @param isbn The International Standard Book Number (ISBN) of the book.
 */
Book::Book(const std::string& id, const std::string& isbn) : Citation{id} {
    // Make a GET request to retrieve book information using the ISBN
    auto result = client.Get("/isbn/" + encodeUriComponent(isbn));

    // Check if the request was successful (HTTP status code 200)
    if(result && result->status == httplib::OK_200) {
        // Parse the response body as JSON
        auto jsonObj = nlohmann::json::parse(result->body);

        // Extract book information from the JSON object
        author = jsonObj["author"].get<std::string>();
        title = jsonObj["title"].get<std::string>();
        publisher = jsonObj["publisher"].get<std::string>();
        year = jsonObj["year"].get<std::string>();
    } else {
        // Handle HTTP errors
        std::exit(1);
    }
}

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
 * the current Book object, effectively avoiding the slicing problem.
 * 
 * @param another The Book object to clone.
 * @return A reference to the current Book object.
 * 
 * @throws std::invalid_argument If the type of 'another' is not Book.
 * 
 * @note This function overrides the Clone function from the Citation class.
 * @note It is recommended to use try-catch blocks to handle potential exceptions
 *       when calling this function.
 */
Citation& Book::Clone(const Citation& another) {
    if(typeid(another) == typeid(Book)) {
        auto bRef = dynamic_cast<const Book&>(another);
        return Book::operator=(bRef);
    } else {
        throw std::invalid_argument("Cannot clone from non-Book object");
        return *this;
    }
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