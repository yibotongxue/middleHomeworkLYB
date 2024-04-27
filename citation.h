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
    std::string id; 

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
     * This pure virtual function is used to print the citation information.
     * It is declared as const, indicating that it does not modify the object's state.
     * 
     * @note This function must be overridden in derived classes to provide
     *       specific print behavior for each citation type.
    */
    virtual void print(std::ostream& output) const = 0;

    const std::string getId() const {
        return id;
    }
};

#endif