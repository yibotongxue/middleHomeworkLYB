#pragma once
#ifndef CITATION_H
#define CITATION_H

#include <string>
#include <iostream>

/**
 * @brief Citation is an abstract base class representing a generic citation.
 * 
 * This class serves as the base class for various types of citations, such as books,
 * webpages, articles, etc. It provides a common interface for managing citation
 * information and defines pure virtual functions that must be implemented by derived classes.
 * 
 * The Citation class defines a unique identifier for each citation and declares virtual
 * functions for cloning and printing citation information.
 * 
 * @note This class is intended to be used as a base class for specific types of citations.
 *       Derived classes must implement the pure virtual functions print() and Clone().
 */
class Citation {

protected:
    std::string id; // The unique identifier for the citation

    // Default assignment operator for Citation class
    Citation& operator=(const Citation& c) = default; 

public:
    /**
     * @brief Delete default constructor for Citation class.
     * 
     * This default constructor is deleted to prevent accidental creation
     * of Citation objects without specifying a unique identifier.
     * 
     * To create a Citation object, use the constructor with a unique identifier parameter.
    */
    Citation() = delete; 

    /**
     * @brief Construct a new Citation object with the given string
     * 
     * @param id The id of the citation
     */
    Citation(const std::string& id);

    /**
     * @brief Construct a new Citation object as a copy of another Citation
     * 
     * @param other The Citation to copy
    */
    Citation(const Citation& other);

    /**
     * @brief Default virtual destructor for Citation class.
     * 
     * This virtual destructor is declared to ensure proper destruction of derived
     * objects through base class pointers. It allows derived classes to clean up
     * their resources properly when objects are destroyed through a base class pointer.
    */
    virtual ~Citation() = default;

    /**
     * @brief Clone the content of another Citation object.
     * 
     * This virtual function creates and returns a copy of the current Citation object,
     * effectively avoiding the slicing problem. Derived classes should override this 
     * function to provide proper cloning behavior specific to their type.
     * 
     * @param another The Citation object to clone.
     * @return A reference to the current Citation object.
    */
    virtual Citation& Clone(const Citation& another);

    /**
     * @brief Print the citation information.
     * 
     * This pure virtual function is used to print the citation information to the specified output stream.
     * It is declared as const, indicating that it does not modify the object's state.
     * 
     * Derived classes must override this function to provide specific printing behavior for each citation type.
     * When implementing this function in derived classes, the citation information should be formatted
     * according to the conventions and requirements of the respective citation type.
     * 
     * @param output The output stream to which the citation information will be printed.
     *               This can be std::cout for printing to the console or any other output stream.
     * 
     * @note Implementations of this function should avoid modifying the object's state.
     *       The primary purpose of this function is to output the citation information
     *       in a human-readable format to the specified output stream.
    */
    virtual void print(std::ostream& output) const = 0;

    /**
     * @brief Get the unique identifier of the citation.
     * 
     * This function returns the unique identifier of the citation.
     * 
     * @return const std::string& The unique identifier of the citation.
     */
    const std::string& getId() const {
        return id;
    }
};

#endif