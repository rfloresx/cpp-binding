
#ifndef TEST_POINT3D_HPP
#define TEST_POINT3D_HPP

#include <Test/Test.hpp>

namespace Test {

namespace types {
    typedef Test_Point3D Point3D;
    static corto_struct& Point3D_o;
}

// Implementation of corto type /Test/Point3D
class CPoint3D : public CPoint
{
public:
    // Getters/setters
    int32_t z() const;
    void z(int32_t value);
    
    // Methods
    void add(CPoint3D p);
    
    // Operators
    
    // Constructs
    
};

}


#endif
