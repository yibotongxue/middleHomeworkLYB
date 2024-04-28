#pragma once
#ifndef WEBPAGE_H
#define WEBPAGE_H

#include "citation.h"

/**
 * @brief WebPage class represents a citation for a webpage.
 * 
 * This class extends the functionality of the Citation class to represent
 * a citation for a webpage. It inherits the unique identifier from the Citation
 * class and may contain additional attributes specific to webpages, such as title
 * and website URL.
 * 
 * The WebPage class provides methods to create, copy and print webpage citations.
*/
class WebPage : public Citation {
private:
    std::string title;   //!< The title of the webpage.
    std::string url;     //!< The website URL of the webpage.

public:
    /**
     * @brief Delete default constructor for WebPage class.
     * 
     * This default constructor is deleted to prevent accidental creation
     * of WebPae objects without specifying requried attributes such as ID,
     * title, and website URL.
     * 
     * To create a WebPage object, use the constructor with approprite parameters.
    */
    WebPage() = delete;

    /**
     * @brief Construct a new WebPage object with the given attributes.
     * 
     * @param id The unique identifier for the webpage citation.
     * @param title The title of the webpage.
     * @param url The website URL of the webpage.
    */
    WebPage(const std::string& id, const std::string& title, const std::string& url);

    /**
     * @brief Construct a new WebPage object with the given attributes.
     * 
     * This constructor initializes a new WebPage object with given arrtibutes: id and url.
     * It retrieves the webpage title from an external API using the provided URL.
     * 
     * @param id The unique identifier for the webpage citation.
     * @param url The website URL of the webpage citation.
     * 
     * @note This constructor fetches the webpage title from an external API using the provided URL.
     *       If the request is successful, the title is extracted from the response body and assigned
     *       to the WebPage object. If the request fails, an error message is printed to stanndanr error.
     * 
     * @note It is recommended to use try-catch blocks to handle potential exceptions
     *       when calling this constructor, such as network errors or JSON parsing errors.
    */
    WebPage(const std::string& id, const std::string& url);

    /**
     * @brief Copy constructor for WebPage objects.
     * 
     * This constructor creates a new WebPage object as a copy of anotheer WebPage object.
     * 
     * @param other The WebPage object to be copied.
    */
    WebPage(const WebPage& other);

   /**
    * @brief Default virtual destructor for WebPage objects.
    * 
    * This virtual destructor allows derived classes to properly clean up resources
    * when objects are destroyed. It is provided with a default implementation.
   */
    virtual ~WebPage() = default;

    /**
     * @brief Clone the content of another WebPage object.
     * 
     * This virtual function creates and returns a copy of the current WebPage object,
     * effectively avoiding the slicing problem. Derived classes should override this
     * function to provide proper cloning behavior specific to their type.
     * 
     * @param another The Citation object to clone, must be of type WebPage.
     * @return A reference to the current WebPage object.
     * 
     * @throws std::invalid_argument If the type of 'another' is not WebPage.
     * 
     * @note This function overrides the Clone function from the base class Citation.
     * @note It is recommended to use try-catch blocks to handle potential exceptions
     *       when calling this function.
     */
    virtual Citation& Clone(const Citation& another) override;

    /**
     * @brief Print the webpage citation information.
     * 
     * This function prints the citation information specific to a WebPage object to the specified output stream.
     * It includes the webpage's unique identifier, title, and website URL.
     * 
     * @param output The output stream to which the citation information will be printed.
     *               This can be std::cout for printing to the console or any other output stream.
     * 
     * @note This function does not modify the object's state and is declared as const.
     *       The citation information is formatted according to the conventions of a webpage citation.
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