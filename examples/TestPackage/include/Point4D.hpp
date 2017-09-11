
#ifndef TEST_POINT4D_HPP
#define TEST_POINT4D_HPP

#include <Test/Test.hpp>

namespace Test {

namespace types {
    typedef Test_Point4D Point4D;
    static corto_struct& Point4D_o;
}

// Implementation of corto type /Test/Point4D
class CPoint4D : public CPoint3D
{
public:
    // Getters/setters
    int32_t w() const;
    void w(int32_t value);
    
    // Methods
    void add(CPoint4D p);
    
    // Operators
    
    // Constructs
    
};

}


#endif
