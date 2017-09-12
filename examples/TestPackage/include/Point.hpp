
#ifndef TEST_POINT_HPP
#define TEST_POINT_HPP

#include <Test/Test.hpp>

namespace Test {

namespace types {
    typedef Test_Point Point;
    extern corto_struct& Point_o;
}

// Implementation of corto type /Test/Point
class CPoint : public ::corto::Object
{
public:
    typedef ::corto::Object Base;

    // Getters/setters
    int32_t x() const;
    void x(int32_t value);
    int32_t y() const;
    void y(int32_t value);
    
    // Methods
    void add(CPoint p);
    ::std::string boo();
    CPoint foo();
    static void idk();
    int32_t what();
    
    // Operators
    CPoint& operator=(const CPoint& other);
    CPoint& operator=(CPoint&& other);
    CPoint& operator=(types::Point* other);
    
    // Constructs
    CPoint();
    CPoint(const CPoint& other);
    CPoint(CPoint&& other);
    CPoint(types::Point* ref);
    CPoint(types::Point val);
    CPoint(types::Point* ref, ::corto::Type type);
    
    ~CPoint();
    
};

}


#endif
