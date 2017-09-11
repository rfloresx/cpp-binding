/* _load.h
 *
 * This file contains variables for objects/type definitions in the package.
 * You should not manually modify the contents of this file.
 */

#ifndef TEST_LOAD_H
#define TEST_LOAD_H

#include <corto/corto.h>
#include <Test/_project.h>
#include <corto/vstore/_type.h>
#include <corto/lang/_type.h>

#ifdef __cplusplus
extern "C" {
#endif

TEST_EXPORT extern corto_package Test_o;
TEST_EXPORT extern corto_struct Test_Point_o;
#ifdef BUILDING_TEST
#define Point_o Test_Point_o
#endif
TEST_EXPORT extern corto_method Test_Point_boo_o;
#ifdef BUILDING_TEST
#define Point_boo_o Test_Point_boo_o
#endif
TEST_EXPORT extern corto_method Test_Point_foo_o;
#ifdef BUILDING_TEST
#define Point_foo_o Test_Point_foo_o
#endif
TEST_EXPORT extern corto_method Test_Point_what_o;
#ifdef BUILDING_TEST
#define Point_what_o Test_Point_what_o
#endif
TEST_EXPORT extern corto_member Test_Point_x_o;
#ifdef BUILDING_TEST
#define Point_x_o Test_Point_x_o
#endif
TEST_EXPORT extern corto_member Test_Point_y_o;
#ifdef BUILDING_TEST
#define Point_y_o Test_Point_y_o
#endif
TEST_EXPORT extern corto_struct Test_Point3D_o;
#ifdef BUILDING_TEST
#define Point3D_o Test_Point3D_o
#endif
TEST_EXPORT extern corto_member Test_Point3D_z_o;
#ifdef BUILDING_TEST
#define Point3D_z_o Test_Point3D_z_o
#endif
TEST_EXPORT extern corto_struct Test_Point4D_o;
#ifdef BUILDING_TEST
#define Point4D_o Test_Point4D_o
#endif
TEST_EXPORT extern corto_member Test_Point4D_w_o;
#ifdef BUILDING_TEST
#define Point4D_w_o Test_Point4D_w_o
#endif
TEST_EXPORT extern corto_function Test_WHAT_o;
#ifdef BUILDING_TEST
#define WHAT_o Test_WHAT_o
#endif
TEST_EXPORT extern corto_method Test_Point4D_add_o;
#ifdef BUILDING_TEST
#define Point4D_add_o Test_Point4D_add_o
#endif
TEST_EXPORT extern corto_method Test_Point3D_add_o;
#ifdef BUILDING_TEST
#define Point3D_add_o Test_Point3D_add_o
#endif
TEST_EXPORT extern corto_method Test_Point_add_o;
#ifdef BUILDING_TEST
#define Point_add_o Test_Point_add_o
#endif
TEST_EXPORT extern corto_function Test_BOOO_o;
#ifdef BUILDING_TEST
#define BOOO_o Test_BOOO_o
#endif
TEST_EXPORT extern corto_function Test_Point_idk_o;
#ifdef BUILDING_TEST
#define Point_idk_o Test_Point_idk_o
#endif
TEST_EXPORT extern corto_function Test_WHATKL_o;
#ifdef BUILDING_TEST
#define WHATKL_o Test_WHATKL_o
#endif

#ifdef __cplusplus
}
#endif
#endif

