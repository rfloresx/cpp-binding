#include <Test/Test.hpp>
namespace Test {

int32_t CPoint::x() const
{
    return int32_t{((types::Point)this->ptr())->x};
}
void CPoint::x(int32_t value)
{
    int32_t{((types::Point)this->ptr())->x} = value;
}
int32_t CPoint::y() const
{
    return int32_t{((types::Point)this->ptr())->y};
}
void CPoint::y(int32_t value)
{
    int32_t{((types::Point)this->ptr())->y} = value;
}
extern "C" void _Point_add(types::Point* _this, types::Point* p)
{
    CPoint _instance(_this);
    CPoint _p(p);
    _instance.add(_p);
}

extern "C" char* _Point_boo(types::Point* _this)
{
    CPoint _instance(_this);
    ::std::string result = _instance.boo();
    return corto_strdup(result.c_str());
}

extern "C" types::Point _Point_foo(types::Point* _this)
{
    CPoint _instance(_this);
    CPoint result = _instance.foo();
    return *(types::Point*)(result.ptr());
}

extern "C" int32_t _Point_what(types::Point* _this)
{
    CPoint _instance(_this);
    int32_t result = _instance.what();
    return result;
}

int32_t CPoint3D::z() const
{
    return int32_t{((types::Point3D)this->ptr())->z};
}
void CPoint3D::z(int32_t value)
{
    int32_t{((types::Point3D)this->ptr())->z} = value;
}
extern "C" void _Point3D_add(types::Point3D* _this, types::Point3D* p)
{
    CPoint3D _instance(_this);
    CPoint3D _p(p);
    _instance.add(_p);
}

int32_t CPoint4D::w() const
{
    return int32_t{((types::Point4D)this->ptr())->w};
}
void CPoint4D::w(int32_t value)
{
    int32_t{((types::Point4D)this->ptr())->w} = value;
}
extern "C" void _Point4D_add(types::Point4D* _this, types::Point4D* p)
{
    CPoint4D _instance(_this);
    CPoint4D _p(p);
    _instance.add(_p);
}


}

