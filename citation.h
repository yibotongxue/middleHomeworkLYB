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
    Citation(const std::string id);

    /**
     * @brief Construct a new Citation object as a copy of another Citation
     * 
     * @param other The Citation to copy
    */
    Citation(const Citation& other);

    ~Citation() = default;

    /**
     * @brief Clone the content of another CItation object.
     * 
     * This function clones the content of another Citation object and assigns it to
     * the current Citation object using the assignment operator, effectively avoiding
     * the slicing problem.
     * 
     * @param another The Citation object to clone.
     * @return A reference to the current Citation object
    */
    virtual Citation& Clone(const Citation& another);
};

#endif