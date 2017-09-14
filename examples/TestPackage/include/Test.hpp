
#ifndef TEST_HPP
#define TEST_HPP

#include <corto/cpp/cpp.hpp>
#include <Test/Test.h>

namespace Test {
namespace types {
    typedef Test_TestEnum TestEnum;
    typedef Test_TestMask TestMask;
}
}

#include <Test/Point.hpp>
#include <Test/Point3D.hpp>
#include <Test/Point4D.hpp>
#include <Test/Transform.hpp>

namespace Test {
    
    void BOOO(CPoint p);
    corto::vstore::CMount WHAT();
    CPoint WHATKL(CPoint b);

}


#endif
