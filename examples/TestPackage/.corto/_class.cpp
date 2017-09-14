#include <Test/Test.hpp>

// Implementation for CPoint
extern corto_struct& Test::types::Point_o = Test_Point_o;

int32_t Test::CPoint::x() const
{
    return int32_t{((Test::types::Point*)this->ptr())->x};
}
void Test::CPoint::x(int32_t value)
{
    ((Test::types::Point*)this->ptr())->x = value;
}
int32_t Test::CPoint::y() const
{
    return int32_t{((Test::types::Point*)this->ptr())->y};
}
void Test::CPoint::y(int32_t value)
{
    ((Test::types::Point*)this->ptr())->y = value;
}

extern "C" void Test_Point_add(Test_Point* _this, Test_Point* p)
{
    Test::CPoint _instance(_this);
    Test::CPoint _p(p);
    _instance.add(_p);
}
extern "C" corto_string Test_Point_boo(Test_Point* _this)
{
    Test::CPoint _instance(_this);
    ::std::string result = _instance.boo();
    return corto_strdup(result.c_str());
}
extern "C" Test_Point Test_Point_foo(Test_Point* _this)
{
    Test::CPoint _instance(_this);
    Test::CPoint result = _instance.foo();
    return *(types::Point*)(result.ptr());
}
extern "C" void Test_Point_idk()
{
    Test::CPoint::idk();
}
extern "C" int32_t Test_Point_what(Test_Point* _this)
{
    Test::CPoint _instance(_this);
    int32_t result = _instance.what();
    return result;
}

Test::CPoint& Test::CPoint::operator=(const Test::CPoint& other)
{
    return Test::CPoint::Base::operator=(other);
}
Test::CPoint& Test::CPoint::operator=(Test::CPoint&& other)
{
    return Test::CPoint::Base::operator=(other);
}
Test::CPoint& Test::CPoint::operator=(Test::types::Point* other)
{
    return Test::CPoint::Base::operator=(other);
}

Test::CPoint() : Test::CPoint::Base() {}
Test::CPoint(const Test::CPoint& other) : Test::CPoint::Base(other) {}
Test::CPoint(Test::CPoint&& other) : Test::CPoint::Base(std::move(other)) {}
Test::CPoint(Test::types::Point* ref) : Test::CPoint::Base(ref) {}
Test::CPoint(Test::types::Point val) : Test::CPoint::Base(&val, Test::types::Point_o) {}
Test::CPoint(Test::types::Point* ref, ::corto::CType type) : Test::CPoint::Base(ref, type) {}
Test::~CPoint(){}

// Implementation for CPoint3D
extern corto_struct& Test::types::Point3D_o = Test_Point3D_o;

int32_t Test::CPoint3D::z() const
{
    return int32_t{((Test::types::Point3D*)this->ptr())->z};
}
void Test::CPoint3D::z(int32_t value)
{
    ((Test::types::Point3D*)this->ptr())->z = value;
}

extern "C" void Test_Point3D_add(Test_Point3D* _this, Test_Point3D* p)
{
    Test::CPoint3D _instance(_this);
    Test::CPoint3D _p(p);
    _instance.add(_p);
}

Test::CPoint3D& Test::CPoint3D::operator=(const Test::CPoint3D& other)
{
    return Test::CPoint3D::Base::operator=(other);
}
Test::CPoint3D& Test::CPoint3D::operator=(Test::CPoint3D&& other)
{
    return Test::CPoint3D::Base::operator=(other);
}
Test::CPoint3D& Test::CPoint3D::operator=(Test::types::Point3D* other)
{
    return Test::CPoint3D::Base::operator=(other);
}

Test::CPoint3D() : Test::CPoint3D::Base() {}
Test::CPoint3D(const Test::CPoint3D& other) : Test::CPoint3D::Base(other) {}
Test::CPoint3D(Test::CPoint3D&& other) : Test::CPoint3D::Base(std::move(other)) {}
Test::CPoint3D(Test::types::Point3D* ref) : Test::CPoint3D::Base(ref) {}
Test::CPoint3D(Test::types::Point3D val) : Test::CPoint3D::Base(&val, Test::types::Point3D_o) {}
Test::CPoint3D(Test::types::Point3D* ref, ::corto::CType type) : Test::CPoint3D::Base(ref, type) {}
Test::~CPoint3D(){}

// Implementation for CPoint4D
extern corto_struct& Test::types::Point4D_o = Test_Point4D_o;

int32_t Test::CPoint4D::w() const
{
    return int32_t{((Test::types::Point4D*)this->ptr())->w};
}
void Test::CPoint4D::w(int32_t value)
{
    ((Test::types::Point4D*)this->ptr())->w = value;
}

extern "C" void Test_Point4D_add(Test_Point4D* _this, Test_Point4D* p)
{
    Test::CPoint4D _instance(_this);
    Test::CPoint4D _p(p);
    _instance.add(_p);
}

Test::CPoint4D& Test::CPoint4D::operator=(const Test::CPoint4D& other)
{
    return Test::CPoint4D::Base::operator=(other);
}
Test::CPoint4D& Test::CPoint4D::operator=(Test::CPoint4D&& other)
{
    return Test::CPoint4D::Base::operator=(other);
}
Test::CPoint4D& Test::CPoint4D::operator=(Test::types::Point4D* other)
{
    return Test::CPoint4D::Base::operator=(other);
}

Test::CPoint4D() : Test::CPoint4D::Base() {}
Test::CPoint4D(const Test::CPoint4D& other) : Test::CPoint4D::Base(other) {}
Test::CPoint4D(Test::CPoint4D&& other) : Test::CPoint4D::Base(std::move(other)) {}
Test::CPoint4D(Test::types::Point4D* ref) : Test::CPoint4D::Base(ref) {}
Test::CPoint4D(Test::types::Point4D val) : Test::CPoint4D::Base(&val, Test::types::Point4D_o) {}
Test::CPoint4D(Test::types::Point4D* ref, ::corto::CType type) : Test::CPoint4D::Base(ref, type) {}
Test::~CPoint4D(){}

// Implementation for CTransform
extern corto_struct& Test::types::Transform_o = Test_Transform_o;

Test::CPoint3D Test::CTransform::position() const
{
    return Test::CPoint3D{((Test::types::Transform*)this->ptr())->position};
}
void Test::CTransform::position(Test::CPoint3D value)
{
    if ((types::Point3D*)(value.ptr())) {
        corto_ptr_copy(&((Test::types::Transform*)this->ptr())->position, Test_Point3D_o, (types::Point3D*)(value.ptr()));
    }
}
Test::CPoint3D Test::CTransform::rotation() const
{
    return Test::CPoint3D{((Test::types::Transform*)this->ptr())->rotation};
}
void Test::CTransform::rotation(Test::CPoint3D value)
{
    if ((types::Point3D*)(value.ptr())) {
        corto_ptr_copy(&((Test::types::Transform*)this->ptr())->rotation, Test_Point3D_o, (types::Point3D*)(value.ptr()));
    }
}
::std::string Test::CTransform::name() const
{
    return ::std::string{((Test::types::Transform*)this->ptr())->name};
}
void Test::CTransform::name(::std::string value)
{
    corto_ptr_setstr(&((Test::types::Transform*)this->ptr())->name, value.c_str());
}
Test::types::TestEnum Test::CTransform::test_enum() const
{
    return Test::types::TestEnum{((Test::types::Transform*)this->ptr())->test_enum};
}
void Test::CTransform::test_enum(Test::types::TestEnum value)
{
    ((Test::types::Transform*)this->ptr())->test_enum = value;
}


Test::CTransform& Test::CTransform::operator=(const Test::CTransform& other)
{
    return Test::CTransform::Base::operator=(other);
}
Test::CTransform& Test::CTransform::operator=(Test::CTransform&& other)
{
    return Test::CTransform::Base::operator=(other);
}
Test::CTransform& Test::CTransform::operator=(Test::types::Transform* other)
{
    return Test::CTransform::Base::operator=(other);
}

Test::CTransform() : Test::CTransform::Base() {}
Test::CTransform(const Test::CTransform& other) : Test::CTransform::Base(other) {}
Test::CTransform(Test::CTransform&& other) : Test::CTransform::Base(std::move(other)) {}
Test::CTransform(Test::types::Transform* ref) : Test::CTransform::Base(ref) {}
Test::CTransform(Test::types::Transform val) : Test::CTransform::Base(&val, Test::types::Transform_o) {}
Test::CTransform(Test::types::Transform* ref, ::corto::CType type) : Test::CTransform::Base(ref, type) {}
Test::~CTransform(){}


