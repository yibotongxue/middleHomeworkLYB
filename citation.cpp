#include "citation.h"

// Constructor a new Citation object with the given ID
// @param id The ID of the citation
Citation::Citation(const std::string id) : id{id} {}

// Constructor a new Citation object as a copy of another Citation.
// @param other The Citation to copy.
Citation::Citation(const Citation& other) : id{other.id} {}

/**
 * @brief Clone the content of another Citation object.
 * 
 * This function clones the content of another Citation object and assigns it to
 * the current Citation object using the assignment operator, effectively avoiding
 * the slicing problem.
 * 
 * @param another The Citation object to clone.
 * @return A reference to the current Citation object
*/
Citation& Citation::Clone(const Citation& another) {
    return Citation::operator=(another);
}