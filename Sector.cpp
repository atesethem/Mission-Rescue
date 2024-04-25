#include "Sector.h"
#include "cmath"
#include <iostream>
// Constructor implementation

Sector::Sector(int x, int y, int z) : x(x), y(y), z(z), left(nullptr), right(nullptr), parent(nullptr), color(RED) {
    
    int distance = static_cast<int>(sqrt(x * x + y * y + z * z)); 
    double distances = sqrt(x * x + y * y + z * z);
    std::string stringx, stringy, stringz;

   
    if (x < 0) {
        stringx = "L";
    }
    else if (x == 0) {
        stringx = "S";
    }
    else {
        stringx = "R";
    }

   
    if (y < 0) {
        stringy = "D";
    }
    else if (y == 0) {
        stringy = "S";
    }
    else {
        stringy = "U";
    }

    
    if (z < 0) {
        stringz = "B";
    }
    else if (z == 0) {
        stringz = "S";
    }
    else {
        stringz = "F";
    }

  
    distance_from_earth = distances;
    sector_code = std::to_string(distance) + stringx + stringy + stringz;
}

Sector::~Sector() {
    // TODO: Free any dynamically allocated memory if necessary
}

Sector& Sector::operator=(const Sector& other) {
    // TODO: Overload the assignment operator
    return *this;
}

bool Sector::operator==(const Sector& other) const {
    return (x == other.x && y == other.y && z == other.z);
}

bool Sector::operator!=(const Sector& other) const {
    return !(*this == other);
}