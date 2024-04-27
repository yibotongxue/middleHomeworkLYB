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
    std::string title;
    std::string url;

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
     * @param website The website URL of the webpage.
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
    * @breif Default virtual destructor for WebPage objects.
    * 
    * This virtual destructor allows derived classes to properly clean up resources
    * when objects are destroyed. It is provided with a default implementation.
   */
    virtual ~WebPage() = default;

    /**
     * @brief Clone the content of another WebPage object.
     * 
     * This virtual function creates and returns a copy of the current WebPage object,
     * effectively avoiding the slicing problem. Derived classes shoule override this
     * function to provide proper cloning behavior specific to their type.
     * 
     * @param another The Citation object to clone, must be of type WebPage.
     * @return A reference to the current WebPage object.
     * 
     * @note This function overrides the Clone function from the base class Citation.
    */
    virtual Citation& Clone(const Citation& another) override;

    /**
     * @brief Print the webpage citation information.
     * 
     * This function overrides the pure virtual function print() from the base class Citation.
     * It prints the citation information specific to a WebPage object, including the webpage's
     * unique identifier, title, and website URL.
     * 
     * @note This function does not modify the object's state and is declared as const.
    */
    virtual void print() const override;
};

#endif