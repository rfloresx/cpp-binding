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
#if !defined(__cplusplus) && defined(BUILDING_TEST)
#define Point_o Test_Point_o
#endif
TEST_EXPORT extern corto_method Test_Point_boo_o;
#if !defined(__cplusplus) && defined(BUILDING_TEST)
#define Point_boo_o Test_Point_boo_o
#endif
TEST_EXPORT extern corto_method Test_Point_foo_o;
#if !defined(__cplusplus) && defined(BUILDING_TEST)
#define Point_foo_o Test_Point_foo_o
#endif
TEST_EXPORT extern corto_method Test_Point_what_o;
#if !defined(__cplusplus) && defined(BUILDING_TEST)
#define Point_what_o Test_Point_what_o
#endif
TEST_EXPORT extern corto_member Test_Point_x_o;
#if !defined(__cplusplus) && defined(BUILDING_TEST)
#define Point_x_o Test_Point_x_o
#endif
TEST_EXPORT extern corto_member Test_Point_y_o;
#if !defined(__cplusplus) && defined(BUILDING_TEST)
#define Point_y_o Test_Point_y_o
#endif
TEST_EXPORT extern corto_struct Test_Point3D_o;
#if !defined(__cplusplus) && defined(BUILDING_TEST)
#define Point3D_o Test_Point3D_o
#endif
TEST_EXPORT extern corto_member Test_Point3D_z_o;
#if !defined(__cplusplus) && defined(BUILDING_TEST)
#define Point3D_z_o Test_Point3D_z_o
#endif
TEST_EXPORT extern corto_struct Test_Point4D_o;
#if !defined(__cplusplus) && defined(BUILDING_TEST)
#define Point4D_o Test_Point4D_o
#endif
TEST_EXPORT extern corto_member Test_Point4D_w_o;
#if !defined(__cplusplus) && defined(BUILDING_TEST)
#define Point4D_w_o Test_Point4D_w_o
#endif
TEST_EXPORT extern corto_enum Test_TestEnum_o;
#if !defined(__cplusplus) && defined(BUILDING_TEST)
#define TestEnum_o Test_TestEnum_o
#endif
TEST_EXPORT extern int32_t* Test_TestEnum_E_A_o;
#if !defined(__cplusplus) && defined(BUILDING_TEST)
#define TestEnum_E_A_o Test_TestEnum_E_A_o
#endif
TEST_EXPORT extern int32_t* Test_TestEnum_E_B_o;
#if !defined(__cplusplus) && defined(BUILDING_TEST)
#define TestEnum_E_B_o Test_TestEnum_E_B_o
#endif
TEST_EXPORT extern int32_t* Test_TestEnum_E_C_o;
#if !defined(__cplusplus) && defined(BUILDING_TEST)
#define TestEnum_E_C_o Test_TestEnum_E_C_o
#endif
TEST_EXPORT extern corto_enum Test_TestMask_o;
#if !defined(__cplusplus) && defined(BUILDING_TEST)
#define TestMask_o Test_TestMask_o
#endif
TEST_EXPORT extern int32_t* Test_TestMask_M_A_o;
#if !defined(__cplusplus) && defined(BUILDING_TEST)
#define TestMask_M_A_o Test_TestMask_M_A_o
#endif
TEST_EXPORT extern int32_t* Test_TestMask_M_B_o;
#if !defined(__cplusplus) && defined(BUILDING_TEST)
#define TestMask_M_B_o Test_TestMask_M_B_o
#endif
TEST_EXPORT extern int32_t* Test_TestMask_M_C_o;
#if !defined(__cplusplus) && defined(BUILDING_TEST)
#define TestMask_M_C_o Test_TestMask_M_C_o
#endif
TEST_EXPORT extern corto_struct Test_Transform_o;
#if !defined(__cplusplus) && defined(BUILDING_TEST)
#define Transform_o Test_Transform_o
#endif
TEST_EXPORT extern corto_member Test_Transform_name_o;
#if !defined(__cplusplus) && defined(BUILDING_TEST)
#define Transform_name_o Test_Transform_name_o
#endif
TEST_EXPORT extern corto_member Test_Transform_position_o;
#if !defined(__cplusplus) && defined(BUILDING_TEST)
#define Transform_position_o Test_Transform_position_o
#endif
TEST_EXPORT extern corto_member Test_Transform_rotation_o;
#if !defined(__cplusplus) && defined(BUILDING_TEST)
#define Transform_rotation_o Test_Transform_rotation_o
#endif
TEST_EXPORT extern corto_member Test_Transform_test_enum_o;
#if !defined(__cplusplus) && defined(BUILDING_TEST)
#define Transform_test_enum_o Test_Transform_test_enum_o
#endif
TEST_EXPORT extern corto_function Test_WHAT_o;
#if !defined(__cplusplus) && defined(BUILDING_TEST)
#define WHAT_o Test_WHAT_o
#endif
TEST_EXPORT extern corto_method Test_Point4D_add_o;
#if !defined(__cplusplus) && defined(BUILDING_TEST)
#define Point4D_add_o Test_Point4D_add_o
#endif
TEST_EXPORT extern corto_method Test_Point3D_add_o;
#if !defined(__cplusplus) && defined(BUILDING_TEST)
#define Point3D_add_o Test_Point3D_add_o
#endif
TEST_EXPORT extern corto_method Test_Point_add_o;
#if !defined(__cplusplus) && defined(BUILDING_TEST)
#define Point_add_o Test_Point_add_o
#endif
TEST_EXPORT extern corto_function Test_BOOO_o;
#if !defined(__cplusplus) && defined(BUILDING_TEST)
#define BOOO_o Test_BOOO_o
#endif
TEST_EXPORT extern corto_function Test_Point_idk_o;
#if !defined(__cplusplus) && defined(BUILDING_TEST)
#define Point_idk_o Test_Point_idk_o
#endif
TEST_EXPORT extern corto_function Test_WHATKL_o;
#if !defined(__cplusplus) && defined(BUILDING_TEST)
#define WHATKL_o Test_WHATKL_o
#endif

#ifdef __cplusplus
}
#endif
#endif

