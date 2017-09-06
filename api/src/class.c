/*
struct point::
    x, y : int32 

class vector2f::
    x,y : float32

class Transform::
    position : point
    scale : vector2f 


typedef test_point_s test_point;
struct test_point_s {
    int32_t x,y;
};

typedef test_vector2f_s* test_vector2f;
struct test_vector2f {
    float x,y;
};

typedef test_transform_s* test_transform;
struct test_transform_s {
    test_point position;
    test_vector2f scale;
};

namespace Test 
{
    namespace types 
    {
        typedef test_point Point;
        typedef test_vector2f Vector2f;
        typedef test_transform Transform;
    }

    class Point : public ::corto::Object 
    {
    public:
        typedef ::corto::Object Base;

        int32_t x() const;
        void x(int32_t x);

        int32_t y() const;
        void y(int32_t y);

        Point();
        Point(const Point &other);
        Point(Point &&other);
        Point(types::Point *obj);
        Point(types::Point *ptr, types::Type type);
        Point(types::Point &val);
        
        virtual ~Point();

        Point& operator=(const Point &other);
        Point& operator=(Point &&other);
        Point& operator=(types::Point *obj);
        Point& operator=(types::Point &val);
    };

    class Vector2f : public ::corto::Object 
    {
    public:
        typedef ::corto::Object Base;

        float x() const;
        void x(float x);

        float y() const;
        void y(float y);

        Vector2f();
        Vector2f(const Vector2f &other);
        Vector2f(Vector2f &&other);
        Vector2f(types::Vector2f obj);
        Vector2f(types::Vector2f ptr, types::Type type);

        virtual ~Vector2f();

        Vector2f& operator=(const Vector2f &other);
        Vector2f& operator=(Vector2f &&other);
        Vector2f& operator=(types::Vector2f obj);
    };

    class Transform : public ::corto::Object 
    {
    public:
        typedef ::corto::Object Base;
        
        // Getters/Setters
        Point position() const;
        void position(Point value);

        Transform scale() const;
        void scale(Transform value);

        Transform();
        Transform(const Transform &other);
        Transform(Transform &&other);
        Transform(types::Transform obj);
        Transform(types::Transform ptr, types::Type type);

        virtual ~Transform();

        Transform& operator=(const Transform &other);
        Transform& operator=(Transform &&other);
        Transform& operator=(types::Transform obj);
    };
}
*/

//  corto_int16 cpp_apiClassMember(corto_walk_opt* s, corto_value* v, void* userData) {
//     cpp_classWalk_t* data;
//     corto_member m;
    
//     if (v->kind == CORTO_MEMBER) {
//         m = v->is.member.t;
//         data = userData;
//         corto_id getter, setter;
//         // corto_bool isUnionCase = corto_instanceof(corto_union_o, corto_parentof(m));
//         // Getter 
//         // type name() const;
//         sprintf(getter, "%s %s() const;");
//         // Setter 
//         // void name(type value);
//         sprintf(setter, "void %s(%s value);");
//     }
// }