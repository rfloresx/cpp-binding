
#ifndef TEST_POINT3D_HPP
#define TEST_POINT3D_HPP

#include <Test/Test.hpp>

namespace Test {

// Implementation of corto type /Test/Point3D
class CPoint3D : public CPoint{
public:
    // Getters/setters
    int32_t z() const;
    void z(int32_t value);
    
    // Methods
    void add(CPoint3D p);
    
    // Operators
    
    // Constructs
    
