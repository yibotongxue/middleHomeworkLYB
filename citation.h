#pragma once
#ifndef CITATION_H
#define CITATION_H

#include <string>

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
};

#endif