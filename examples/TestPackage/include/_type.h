/* _type.h
 *
 * This file contains generated C type definitions.
 * You should not manually modify the contents of this file.
 */

#ifndef TEST__TYPE_H
#define TEST__TYPE_H

#include <corto/vstore/_type.h>
#include <corto/lang/_type.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Native types */
#ifndef TEST_H
#endif

/* Type definitions */
/*  /Test/Point */
typedef struct Test_Point Test_Point;

struct Test_Point {
    int32_t x;
    int32_t y;
};

#if !defined(__cplusplus) && defined(BUILDING_TEST)
typedef Test_Point Point;
#endif

/*  /Test/Point3D */
typedef struct Test_Point3D Test_Point3D;

struct Test_Point3D {
    Test_Point super;
    int32_t z;
};

#if !defined(__cplusplus) && defined(BUILDING_TEST)
typedef Test_Point3D Point3D;
#endif

/*  /Test/Point4D */
typedef struct Test_Point4D Test_Point4D;

struct Test_Point4D {
    Test_Point3D super;
    int32_t w;
};

#if !defined(__cplusplus) && defined(BUILDING_TEST)
typedef Test_Point4D Point4D;
#endif

/* /Test/TestEnum */
typedef enum Test_TestEnum {
    Test_E_A = 0,
    Test_E_B = 1,
    Test_E_C = 2
} Test_TestEnum;

#if !defined(__cplusplus) && defined(BUILDING_TEST)
typedef Test_TestEnum TestEnum;
#endif

/* /Test/TestMask */
typedef enum Test_TestMask {
    Test_M_A = 1,
    Test_M_B = 2,
    Test_M_C = 4
} Test_TestMask;

#if !defined(__cplusplus) && defined(BUILDING_TEST)
typedef Test_TestMask TestMask;
#endif

/*  /Test/Transform */
typedef struct Test_Transform Test_Transform;

struct Test_Transform {
    Test_Point3D position;
    Test_Point3D rotation;
    corto_string name;
    Test_TestEnum test_enum;
};

#if !defined(__cplusplus) && defined(BUILDING_TEST)
typedef Test_Transform Transform;
#endif

#ifdef __cplusplus
}
#endif
#endif

