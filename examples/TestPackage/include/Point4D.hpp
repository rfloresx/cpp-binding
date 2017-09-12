
#ifndef TEST_POINT4D_HPP
#define TEST_POINT4D_HPP

#include <Test/Test.hpp>

namespace Test {

namespace types {
    typedef Test_Point4D Point4D;
    extern corto_struct& Point4D_o;
}

// Implementation of corto type /Test/Point4D
class CPoint4D : public CPoint3D
{
public:
    typedef CPoint3D Base;

    // Getters/setters
    int32_t w() const;
    void w(int32_t value);
    
    // Methods
    void add(CPoint4D p);
    
    // Operators
    CPoint4D& operator=(const CPoint4D& other);
    CPoint4D& operator=(CPoint4D&& other);
    CPoint4D& operator=(types::Point4D* other);
    
    // Constructs
    CPoint4D();
    CPoint4D(const CPoint4D& other);
    CPoint4D(CPoint4D&& other);
    CPoint4D(types::Point4D* ref);
    CPoint4D(types::Point4D val);
    CPoint4D(types::Point4D* ref, ::corto::Type type);
    
    ~CPoint4D();
    
};

}


#endif
