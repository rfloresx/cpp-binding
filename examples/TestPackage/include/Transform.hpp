
#ifndef TEST_TRANSFORM_HPP
#define TEST_TRANSFORM_HPP

#include <Test/Test.hpp>

namespace Test {

namespace types {
    typedef Test_Transform Transform;
    extern corto_struct& Transform_o;
}

// Implementation of corto type /Test/Transform
class CTransform : public ::corto::Object
{
public:
    typedef ::corto::Object Base;

    // Getters/setters
    CPoint3D position() const;
    void position(CPoint3D value);
    CPoint3D rotation() const;
    void rotation(CPoint3D value);
    ::std::string name() const;
    void name(::std::string value);
    types::TestEnum test_enum() const;
    void test_enum(types::TestEnum value);
    
    // Methods
    
    // Operators
    CTransform& operator=(const CTransform& other);
    CTransform& operator=(CTransform&& other);
    CTransform& operator=(types::Transform* other);
    
    // Constructs
    CTransform();
    CTransform(const CTransform& other);
    CTransform(CTransform&& other);
    CTransform(types::Transform* ref);
    CTransform(types::Transform val);
    CTransform(types::Transform* ref, ::corto::CType type);
    
    ~CTransform();
    
};

}


#endif
