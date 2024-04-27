#include "webpage.h"
#include <iostream>
#include <typeinfo>
#include <stdexcept>

/**
 * @brief Construct a new WebPage object with the given attributes.
 * 
 * @param id The unique identifier for the webpage citation.
 * @param title The title of the webpage.
 * @param website The webiste URL of the webpage.
*/
WebPage::WebPage(const std::string& id, const std::string& title, const std::string& website) :
                 Citation{id}, title{title}, website{website} {}

/**
 * @brief Copy constructor for WebPage objects.
 * 
 * This constructor creates a new WebPage object as copy of another WebPage object.
 * 
 * @parma other The WebPage object to be copied.
*/
WebPage::WebPage(const WebPage& other) :
                 Citation{other}, title{other.title}, website{other.website} {}

/**
 * @brief Clone the content of another WebPage object.
 * 
 * This function clones the content of another WebPage object and assigns it to
 * the current WebPage object, effectively avoiding the slicing problem.
 * 
 * @param another The WebPage object to clone.
 * @return A reference to the current WebPage object.
 * 
 * @throws std::invalid_argument If the type of 'another' is not WebPage.
 * 
 * @note This function overrides the Clone function from the base class Citation.
 * @note It is recommended to use try-catch blocks to handle potential exceptions
 *       when calling this function.
 */
Citation& WebPage::Clone(const Citation& another) {
    if (typeid(another) == typeid(WebPage)) {
        auto wRef = dynamic_cast<const WebPage&>(another);
        return WebPage::operator=(wRef);
    } else {
        throw std::invalid_argument("Cannot clone from non-WebPage object");
        return *this;
    }
}


/**
 * @brief Print the webpage citation information.
 * 
 * This function prints the citation information specific to a WebPage object.
 * It prints the webpage's unique identifier, title, and website URL.
 */
void WebPage::print() const {
    std::cout << "[" << id << "] webpage: " << title << ". Avalable at " << website << std::endl;
}