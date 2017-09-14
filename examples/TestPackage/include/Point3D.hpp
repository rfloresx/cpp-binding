
#ifndef TEST_POINT3D_HPP
#define TEST_POINT3D_HPP

#include <Test/Test.hpp>

namespace Test {

namespace types {
    typedef Test_Point3D Point3D;
    extern corto_struct& Point3D_o;
}

// Implementation of corto type /Test/Point3D
class CPoint3D : public CPoint
{
public:
    typedef CPoint Base;

    // Getters/setters
    int32_t z() const;
    void z(int32_t value);
    
    // Methods
    void add(CPoint3D p);
    
    // Operators
    CPoint3D& operator=(const CPoint3D& other);
    CPoint3D& operator=(CPoint3D&& other);
    CPoint3D& operator=(types::Point3D* other);
    
    // Constructs
    CPoint3D();
    CPoint3D(const CPoint3D& other);
    CPoint3D(CPoint3D&& other);
    CPoint3D(types::Point3D* ref);
    CPoint3D(types::Point3D val);
    CPoint3D(types::Point3D* ref, ::corto::CType type);
    
    ~CPoint3D();
    
};

}


#endif
