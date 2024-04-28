#include "webpage.h"
#include <typeinfo>
#include <stdexcept>
#include "third_parties/cpp-httplib/httplib.h"
#include "third_parties/nlohmann/json.hpp"
#include "utils.hpp"

extern httplib::Client client;

/**
 * @brief Construct a new WebPage object with the given attributes.
 * 
 * @param id The unique identifier for the webpage citation.
 * @param title The title of the webpage.
 * @param website The webiste URL of the webpage.
*/
WebPage::WebPage(const std::string& id, const std::string& title, const std::string& url) :
                 Citation{id}, title{title}, url{url} {}

/**
 * @brief Construct a new WebPage object with the given attributes.
 * 
 * This constructor initializes a new WebPage object with the given attributes: id and url.
 * It retrieves the webpage title from an external API using the provided URL.
 * 
 * @param id The unique identifier for the webpage citation.
 * @param url The website URL of the webpage.
 * 
 * @note This constructor fetches the webpage title from an external API using the provided URL.
 *       If the request is successful, the title is extracted from the response body and assigned
 *       to the WebPage object. If the request fails, an error message is printed to standard error.
 * 
 * @note It is recommended to use try-catch blocks to handle potential exceptions
 *       when calling this constructor, such as network errors or JSON parsing errors.
*/
WebPage::WebPage(const std::string& id, const std::string& url) : Citation{id}, url{url} {
    // Make an HTTP GET request to retrieve the webpage title using the provided URL
    auto result = client.Get("/title/" + encodeUriComponent(url));

    // Check if the request was successful (HTTP status code 200)
    if(result && result->status == httplib::OK_200) {
        // Parse the reponse body as JSON to extract the webpage title
        auto jsonObj = nlohmann::json::parse(result->body);
        title = jsonObj["title"].get<std::string>();
    } else {
        // Handle HTTP errors
        std::exit(1);
    }
}

/**
 * @brief Copy constructor for WebPage objects.
 * 
 * This constructor creates a new WebPage object as copy of another WebPage object.
 * 
 * @parma other The WebPage object to be copied.
*/
WebPage::WebPage(const WebPage& other) :
                 Citation{other}, title{other.title}, url{other.url} {}

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
void WebPage::print(std::ostream& output) const {
    output << "[" << id << "] webpage: " << title << ". Available at " << url << "\n";
}