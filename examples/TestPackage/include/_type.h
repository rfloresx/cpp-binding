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

#ifdef __cplusplus
}
#endif
#endif

