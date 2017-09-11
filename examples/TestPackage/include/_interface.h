/* _interface.h
 *
 * This file contains generated package function and method declarations.
 * You should not manually modify the contents of this file.
 */

#ifndef TEST_INTERFACE_H
#define TEST_INTERFACE_H

#include <corto/corto.h>
#include <Test/_project.h>

#ifdef __cplusplus
extern "C" {
#endif

/* forward declaration of the function. the '_' in front of the name allows
 * insertion of type-safe casts */
TEST_EXPORT
void _Test_BOOO(
    Test_Point *p);

/* implicit type-safe macro (not available for project implementation) */
#ifndef BUILDING_TEST
#define Test_BOOO(p) _Test_BOOO(p)
#else
#define Test_BOOO _Test_BOOO

/* Allow for type-safe, shorthand version to be used within project. In
 * C++ the name clash risk is too big because '::' is used for scoping */
#ifndef __cplusplus
#define BOOO(p) _Test_BOOO(p)
#endif
#endif

/* explicit type-safe macro */
#define safe_Test_BOOO(p) _Test_BOOO(p)

/* forward declaration of the function. the '_' in front of the name allows
 * insertion of type-safe casts */
TEST_EXPORT
corto_mount _Test_WHAT(void);

/* implicit type-safe macro (not available for project implementation) */
#ifndef BUILDING_TEST
#define Test_WHAT() _Test_WHAT()
#else
#define Test_WHAT _Test_WHAT

/* Allow for type-safe, shorthand version to be used within project. In
 * C++ the name clash risk is too big because '::' is used for scoping */
#ifndef __cplusplus
#define WHAT() _Test_WHAT()
#endif
#endif

/* explicit type-safe macro */
#define safe_Test_WHAT() _Test_WHAT()

/* forward declaration of the function. the '_' in front of the name allows
 * insertion of type-safe casts */
TEST_EXPORT
Test_Point _Test_WHATKL(
    Test_Point *b);

/* implicit type-safe macro (not available for project implementation) */
#ifndef BUILDING_TEST
#define Test_WHATKL(b) _Test_WHATKL(b)
#else
#define Test_WHATKL _Test_WHATKL

/* Allow for type-safe, shorthand version to be used within project. In
 * C++ the name clash risk is too big because '::' is used for scoping */
#ifndef __cplusplus
#define WHATKL(b) _Test_WHATKL(b)
#endif
#endif

/* explicit type-safe macro */
#define safe_Test_WHATKL(b) _Test_WHATKL(b)


/* forward declaration of the function. the '_' in front of the name allows
 * insertion of type-safe casts */
TEST_EXPORT
void _Test_Point_add(
    Test_Point* _this,
    Test_Point *p);

/* implicit type-safe macro (not available for project implementation) */
#ifndef BUILDING_TEST
#define Test_Point_add(_this, p) _Test_Point_add(_this, p)
#else
#define Test_Point_add _Test_Point_add

/* Allow for type-safe, shorthand version to be used within project. In
 * C++ the name clash risk is too big because '::' is used for scoping */
#ifndef __cplusplus
#define Point_add(_this, p) _Test_Point_add(_this, p)
#endif
#endif

/* explicit type-safe macro */
#define safe_Test_Point_add(_this, p) _Test_Point_add(_this, p)

/* forward declaration of the function. the '_' in front of the name allows
 * insertion of type-safe casts */
TEST_EXPORT
corto_string _Test_Point_boo(
    Test_Point* _this);

/* implicit type-safe macro (not available for project implementation) */
#ifndef BUILDING_TEST
#define Test_Point_boo(_this) _Test_Point_boo(_this)
#else
#define Test_Point_boo _Test_Point_boo

/* Allow for type-safe, shorthand version to be used within project. In
 * C++ the name clash risk is too big because '::' is used for scoping */
#ifndef __cplusplus
#define Point_boo(_this) _Test_Point_boo(_this)
#endif
#endif

/* explicit type-safe macro */
#define safe_Test_Point_boo(_this) _Test_Point_boo(_this)

/* forward declaration of the function. the '_' in front of the name allows
 * insertion of type-safe casts */
TEST_EXPORT
Test_Point _Test_Point_foo(
    Test_Point* _this);

/* implicit type-safe macro (not available for project implementation) */
#ifndef BUILDING_TEST
#define Test_Point_foo(_this) _Test_Point_foo(_this)
#else
#define Test_Point_foo _Test_Point_foo

/* Allow for type-safe, shorthand version to be used within project. In
 * C++ the name clash risk is too big because '::' is used for scoping */
#ifndef __cplusplus
#define Point_foo(_this) _Test_Point_foo(_this)
#endif
#endif

/* explicit type-safe macro */
#define safe_Test_Point_foo(_this) _Test_Point_foo(_this)

/* forward declaration of the function. the '_' in front of the name allows
 * insertion of type-safe casts */
TEST_EXPORT
void _Test_Point_idk(void);

/* implicit type-safe macro (not available for project implementation) */
#ifndef BUILDING_TEST
#define Test_Point_idk() _Test_Point_idk()
#else
#define Test_Point_idk _Test_Point_idk

/* Allow for type-safe, shorthand version to be used within project. In
 * C++ the name clash risk is too big because '::' is used for scoping */
#ifndef __cplusplus
#define Point_idk() _Test_Point_idk()
#endif
#endif

/* explicit type-safe macro */
#define safe_Test_Point_idk() _Test_Point_idk()

/* forward declaration of the function. the '_' in front of the name allows
 * insertion of type-safe casts */
TEST_EXPORT
int32_t _Test_Point_what(
    Test_Point* _this);

/* implicit type-safe macro (not available for project implementation) */
#ifndef BUILDING_TEST
#define Test_Point_what(_this) _Test_Point_what(_this)
#else
#define Test_Point_what _Test_Point_what

/* Allow for type-safe, shorthand version to be used within project. In
 * C++ the name clash risk is too big because '::' is used for scoping */
#ifndef __cplusplus
#define Point_what(_this) _Test_Point_what(_this)
#endif
#endif

/* explicit type-safe macro */
#define safe_Test_Point_what(_this) _Test_Point_what(_this)

/* forward declaration of the function. the '_' in front of the name allows
 * insertion of type-safe casts */
TEST_EXPORT
void _Test_Point3D_add(
    Test_Point3D* _this,
    Test_Point3D *p);

/* implicit type-safe macro (not available for project implementation) */
#ifndef BUILDING_TEST
#define Test_Point3D_add(_this, p) _Test_Point3D_add(_this, p)
#else
#define Test_Point3D_add _Test_Point3D_add

/* Allow for type-safe, shorthand version to be used within project. In
 * C++ the name clash risk is too big because '::' is used for scoping */
#ifndef __cplusplus
#define Point3D_add(_this, p) _Test_Point3D_add(_this, p)
#endif
#endif

/* explicit type-safe macro */
#define safe_Test_Point3D_add(_this, p) _Test_Point3D_add(_this, p)

/* forward declaration of the function. the '_' in front of the name allows
 * insertion of type-safe casts */
TEST_EXPORT
void _Test_Point4D_add(
    Test_Point4D* _this,
    Test_Point4D *p);

/* implicit type-safe macro (not available for project implementation) */
#ifndef BUILDING_TEST
#define Test_Point4D_add(_this, p) _Test_Point4D_add(_this, p)
#else
#define Test_Point4D_add _Test_Point4D_add

/* Allow for type-safe, shorthand version to be used within project. In
 * C++ the name clash risk is too big because '::' is used for scoping */
#ifndef __cplusplus
#define Point4D_add(_this, p) _Test_Point4D_add(_this, p)
#endif
#endif

/* explicit type-safe macro */
#define safe_Test_Point4D_add(_this, p) _Test_Point4D_add(_this, p)

#ifdef __cplusplus
}
#endif

#endif

