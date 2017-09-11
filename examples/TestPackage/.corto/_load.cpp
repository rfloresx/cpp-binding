/* _load.cpp
 *
 * This file contains generated code to insert objects/type definitions.
 * You should not manually change the contents of this file.
 */

#include <Test/Test.h>

/* Forward declarations */

#ifdef __cplusplus
extern "C"
#endif
void _Test_BOOO(
    Test_Point *p);

#ifdef __cplusplus
extern "C"
#endif
void _Test_Point_add(
    Test_Point* _this,
    Test_Point *p);

#ifdef __cplusplus
extern "C"
#endif
corto_string _Test_Point_boo(
    Test_Point* _this);

#ifdef __cplusplus
extern "C"
#endif
Test_Point _Test_Point_foo(
    Test_Point* _this);

#ifdef __cplusplus
extern "C"
#endif
void _Test_Point_idk(void);

#ifdef __cplusplus
extern "C"
#endif
int32_t _Test_Point_what(
    Test_Point* _this);

#ifdef __cplusplus
extern "C"
#endif
void _Test_Point3D_add(
    Test_Point3D* _this,
    Test_Point3D *p);

#ifdef __cplusplus
extern "C"
#endif
void _Test_Point4D_add(
    Test_Point4D* _this,
    Test_Point4D *p);

#ifdef __cplusplus
extern "C"
#endif
corto_mount _Test_WHAT(void);

#ifdef __cplusplus
extern "C"
#endif
Test_Point _Test_WHATKL(
    Test_Point *b);

/* Variable definitions */
corto_package Test_o;
corto_struct Test_Point_o;
corto_method Test_Point_boo_o;
corto_method Test_Point_foo_o;
corto_method Test_Point_what_o;
corto_member Test_Point_x_o;
corto_member Test_Point_y_o;
corto_struct Test_Point3D_o;
corto_member Test_Point3D_z_o;
corto_struct Test_Point4D_o;
corto_member Test_Point4D_w_o;
corto_function Test_WHAT_o;
corto_method Test_Point4D_add_o;
corto_method Test_Point3D_add_o;
corto_method Test_Point_add_o;
corto_function Test_BOOO_o;
corto_function Test_Point_idk_o;
corto_function Test_WHATKL_o;

/* Load objects in object store. */
int Test_load(void) {
    corto_object _a_; /* Used for resolving anonymous objects */
    corto_object _e_; /* Used for resolving extern objects */
    (void)_e_;
    _a_ = NULL;

    corto_attr prevAttr = corto_getAttr();

    prevAttr = corto_setAttr(CORTO_ATTR_PERSISTENT);
    Test_o = corto_package(corto_declareChild(root_o, "Test", corto_package_o));
    if (!Test_o) {
        corto_error("Test_load: failed to declare 'Test_o' (%s)", corto_lasterr());
        goto error;
    }
    corto_setAttr(prevAttr);
    
    if (!corto_checkState(Test_o, CORTO_VALID)) {
        Test_o->url = corto_strdup("http://www.corto.io/doc/Test");
        Test_o->version = NULL;
        Test_o->author = NULL;
        Test_o->description = NULL;
        Test_o->env = corto_strdup("/Users/rfloresx/.corto");
        Test_o->language = NULL;
        Test_o->managed = TRUE;
        Test_o->noapi = FALSE;
        Test_o->prefix = NULL;
        Test_o->local = FALSE;
        Test_o->coverage = FALSE;
        if (corto_define(Test_o)) {
            corto_error("Test_load: failed to define 'Test_o' (%s)", corto_lasterr());
            goto error;
        }
    }

    Test_Point_o = corto_struct(corto_declareChild(Test_o, "Point", corto_struct_o));
    if (!Test_Point_o) {
        corto_error("Test_load: failed to declare 'Test_Point_o' (%s)", corto_lasterr());
        goto error;
    }
    
    Test_Point_boo_o = corto_method(corto_declareChild(Test_Point_o, "boo()", corto_method_o));
    if (!Test_Point_boo_o) {
        corto_error("Test_load: failed to declare 'Test_Point_boo_o' (%s)", corto_lasterr());
        goto error;
    }
    
    if (!corto_checkState(Test_Point_boo_o, CORTO_VALID)) {
        ((corto_function)Test_Point_boo_o)->returnType = corto_type(corto_resolve(NULL, "string"));
        ((corto_function)Test_Point_boo_o)->returnsReference = FALSE;
        
        corto_function(Test_Point_boo_o)->kind = CORTO_PROCEDURE_CDECL;
        corto_function(Test_Point_boo_o)->fptr = (corto_word)_Test_Point_boo;
        if (corto_define(Test_Point_boo_o)) {
            corto_error("Test_load: failed to define 'Test_Point_boo_o' (%s)", corto_lasterr());
            goto error;
        }
    }

    Test_Point_foo_o = corto_method(corto_declareChild(Test_Point_o, "foo()", corto_method_o));
    if (!Test_Point_foo_o) {
        corto_error("Test_load: failed to declare 'Test_Point_foo_o' (%s)", corto_lasterr());
        goto error;
    }
    
    if (!corto_checkState(Test_Point_foo_o, CORTO_VALID)) {
        ((corto_function)Test_Point_foo_o)->returnType = corto_type((corto_claim(Test_Point_o), Test_Point_o));
        ((corto_function)Test_Point_foo_o)->returnsReference = FALSE;
        
        corto_function(Test_Point_foo_o)->kind = CORTO_PROCEDURE_CDECL;
        corto_function(Test_Point_foo_o)->fptr = (corto_word)_Test_Point_foo;
        if (corto_define(Test_Point_foo_o)) {
            corto_error("Test_load: failed to define 'Test_Point_foo_o' (%s)", corto_lasterr());
            goto error;
        }
    }

    Test_Point_what_o = corto_method(corto_declareChild(Test_Point_o, "what()", corto_method_o));
    if (!Test_Point_what_o) {
        corto_error("Test_load: failed to declare 'Test_Point_what_o' (%s)", corto_lasterr());
        goto error;
    }
    
    if (!corto_checkState(Test_Point_what_o, CORTO_VALID)) {
        ((corto_function)Test_Point_what_o)->returnType = corto_type(corto_resolve(NULL, "int32"));
        ((corto_function)Test_Point_what_o)->returnsReference = FALSE;
        
        corto_function(Test_Point_what_o)->kind = CORTO_PROCEDURE_CDECL;
        corto_function(Test_Point_what_o)->fptr = (corto_word)_Test_Point_what;
        if (corto_define(Test_Point_what_o)) {
            corto_error("Test_load: failed to define 'Test_Point_what_o' (%s)", corto_lasterr());
            goto error;
        }
    }

    Test_Point_x_o = corto_member(corto_declareChild(Test_Point_o, "x", corto_member_o));
    if (!Test_Point_x_o) {
        corto_error("Test_load: failed to declare 'Test_Point_x_o' (%s)", corto_lasterr());
        goto error;
    }
    
    if (!corto_checkState(Test_Point_x_o, CORTO_VALID)) {
        Test_Point_x_o->type = corto_type(corto_resolve(NULL, "int32"));
        Test_Point_x_o->modifiers = 0x0;
        Test_Point_x_o->unit = NULL;
        Test_Point_x_o->state = 0x5;
        Test_Point_x_o->stateCondExpr = NULL;
        Test_Point_x_o->weak = FALSE;
        Test_Point_x_o->id = 0;
        if (corto_define(Test_Point_x_o)) {
            corto_error("Test_load: failed to define 'Test_Point_x_o' (%s)", corto_lasterr());
            goto error;
        }
    }

    Test_Point_y_o = corto_member(corto_declareChild(Test_Point_o, "y", corto_member_o));
    if (!Test_Point_y_o) {
        corto_error("Test_load: failed to declare 'Test_Point_y_o' (%s)", corto_lasterr());
        goto error;
    }
    
    if (!corto_checkState(Test_Point_y_o, CORTO_VALID)) {
        Test_Point_y_o->type = corto_type(corto_resolve(NULL, "int32"));
        Test_Point_y_o->modifiers = 0x0;
        Test_Point_y_o->unit = NULL;
        Test_Point_y_o->state = 0x5;
        Test_Point_y_o->stateCondExpr = NULL;
        Test_Point_y_o->weak = FALSE;
        Test_Point_y_o->id = 1;
        if (corto_define(Test_Point_y_o)) {
            corto_error("Test_load: failed to define 'Test_Point_y_o' (%s)", corto_lasterr());
            goto error;
        }
    }

    Test_Point3D_o = corto_struct(corto_declareChild(Test_o, "Point3D", corto_struct_o));
    if (!Test_Point3D_o) {
        corto_error("Test_load: failed to declare 'Test_Point3D_o' (%s)", corto_lasterr());
        goto error;
    }
    
    Test_Point3D_z_o = corto_member(corto_declareChild(Test_Point3D_o, "z", corto_member_o));
    if (!Test_Point3D_z_o) {
        corto_error("Test_load: failed to declare 'Test_Point3D_z_o' (%s)", corto_lasterr());
        goto error;
    }
    
    if (!corto_checkState(Test_Point3D_z_o, CORTO_VALID)) {
        Test_Point3D_z_o->type = corto_type(corto_resolve(NULL, "int32"));
        Test_Point3D_z_o->modifiers = 0x0;
        Test_Point3D_z_o->unit = NULL;
        Test_Point3D_z_o->state = 0x5;
        Test_Point3D_z_o->stateCondExpr = NULL;
        Test_Point3D_z_o->weak = FALSE;
        Test_Point3D_z_o->id = 0;
        if (corto_define(Test_Point3D_z_o)) {
            corto_error("Test_load: failed to define 'Test_Point3D_z_o' (%s)", corto_lasterr());
            goto error;
        }
    }

    Test_Point4D_o = corto_struct(corto_declareChild(Test_o, "Point4D", corto_struct_o));
    if (!Test_Point4D_o) {
        corto_error("Test_load: failed to declare 'Test_Point4D_o' (%s)", corto_lasterr());
        goto error;
    }
    
    Test_Point4D_w_o = corto_member(corto_declareChild(Test_Point4D_o, "w", corto_member_o));
    if (!Test_Point4D_w_o) {
        corto_error("Test_load: failed to declare 'Test_Point4D_w_o' (%s)", corto_lasterr());
        goto error;
    }
    
    if (!corto_checkState(Test_Point4D_w_o, CORTO_VALID)) {
        Test_Point4D_w_o->type = corto_type(corto_resolve(NULL, "int32"));
        Test_Point4D_w_o->modifiers = 0x0;
        Test_Point4D_w_o->unit = NULL;
        Test_Point4D_w_o->state = 0x5;
        Test_Point4D_w_o->stateCondExpr = NULL;
        Test_Point4D_w_o->weak = FALSE;
        Test_Point4D_w_o->id = 0;
        if (corto_define(Test_Point4D_w_o)) {
            corto_error("Test_load: failed to define 'Test_Point4D_w_o' (%s)", corto_lasterr());
            goto error;
        }
    }

    Test_WHAT_o = corto_function(corto_declareChild(Test_o, "WHAT()", corto_function_o));
    if (!Test_WHAT_o) {
        corto_error("Test_load: failed to declare 'Test_WHAT_o' (%s)", corto_lasterr());
        goto error;
    }
    
    if (!corto_checkState(Test_WHAT_o, CORTO_VALID)) {
        Test_WHAT_o->returnType = corto_type(corto_resolve(NULL, "/corto/vstore/mount"));
        Test_WHAT_o->returnsReference = TRUE;
        
        corto_function(Test_WHAT_o)->kind = CORTO_PROCEDURE_CDECL;
        corto_function(Test_WHAT_o)->fptr = (corto_word)_Test_WHAT;
        if (corto_define(Test_WHAT_o)) {
            corto_error("Test_load: failed to define 'Test_WHAT_o' (%s)", corto_lasterr());
            goto error;
        }
    }

    Test_Point4D_add_o = corto_method(corto_declareChild(Test_Point4D_o, "add(/Test/Point4D p)", corto_method_o));
    if (!Test_Point4D_add_o) {
        corto_error("Test_load: failed to declare 'Test_Point4D_add_o' (%s)", corto_lasterr());
        goto error;
    }
    
    if (!corto_checkState(Test_Point4D_add_o, CORTO_VALID)) {
        ((corto_function)Test_Point4D_add_o)->returnType = corto_type(corto_resolve(NULL, "void"));
        ((corto_function)Test_Point4D_add_o)->returnsReference = FALSE;
        
        corto_function(Test_Point4D_add_o)->kind = CORTO_PROCEDURE_CDECL;
        corto_function(Test_Point4D_add_o)->fptr = (corto_word)_Test_Point4D_add;
        if (corto_define(Test_Point4D_add_o)) {
            corto_error("Test_load: failed to define 'Test_Point4D_add_o' (%s)", corto_lasterr());
            goto error;
        }
    }

    Test_Point3D_add_o = corto_method(corto_declareChild(Test_Point3D_o, "add(/Test/Point3D p)", corto_method_o));
    if (!Test_Point3D_add_o) {
        corto_error("Test_load: failed to declare 'Test_Point3D_add_o' (%s)", corto_lasterr());
        goto error;
    }
    
    if (!corto_checkState(Test_Point3D_add_o, CORTO_VALID)) {
        ((corto_function)Test_Point3D_add_o)->returnType = corto_type(corto_resolve(NULL, "void"));
        ((corto_function)Test_Point3D_add_o)->returnsReference = FALSE;
        
        corto_function(Test_Point3D_add_o)->kind = CORTO_PROCEDURE_CDECL;
        corto_function(Test_Point3D_add_o)->fptr = (corto_word)_Test_Point3D_add;
        if (corto_define(Test_Point3D_add_o)) {
            corto_error("Test_load: failed to define 'Test_Point3D_add_o' (%s)", corto_lasterr());
            goto error;
        }
    }

    Test_Point_add_o = corto_method(corto_declareChild(Test_Point_o, "add(/Test/Point p)", corto_method_o));
    if (!Test_Point_add_o) {
        corto_error("Test_load: failed to declare 'Test_Point_add_o' (%s)", corto_lasterr());
        goto error;
    }
    
    if (!corto_checkState(Test_Point_add_o, CORTO_VALID)) {
        ((corto_function)Test_Point_add_o)->returnType = corto_type(corto_resolve(NULL, "void"));
        ((corto_function)Test_Point_add_o)->returnsReference = FALSE;
        
        corto_function(Test_Point_add_o)->kind = CORTO_PROCEDURE_CDECL;
        corto_function(Test_Point_add_o)->fptr = (corto_word)_Test_Point_add;
        if (corto_define(Test_Point_add_o)) {
            corto_error("Test_load: failed to define 'Test_Point_add_o' (%s)", corto_lasterr());
            goto error;
        }
    }

    if (!corto_checkState(Test_Point_o, CORTO_VALID)) {
        ((corto_type)Test_Point_o)->kind = CORTO_COMPOSITE;
        ((corto_type)Test_Point_o)->reference = FALSE;
        ((corto_type)Test_Point_o)->attr = 0x10;
        ((corto_type)Test_Point_o)->options.parentType = NULL;
        ((corto_type)Test_Point_o)->options.parentState = 0x5;
        ((corto_type)Test_Point_o)->options.defaultType = NULL;
        ((corto_type)Test_Point_o)->options.defaultProcedureType = NULL;
        ((corto_interface)Test_Point_o)->base = NULL;
        Test_Point_o->baseAccess = 0x0;
        Test_Point_o->keys.length = 0;
        Test_Point_o->keys.buffer = NULL;
        if (corto_define(Test_Point_o)) {
            corto_error("Test_load: failed to define 'Test_Point_o' (%s)", corto_lasterr());
            goto error;
        }
    }

    if (corto_type(Test_Point_o)->size != sizeof(Test_Point)) {
        corto_error("Test_load: calculated size '%d' of type 'Test_Point_o' doesn't match C-type size '%d'", corto_type(Test_Point_o)->size, sizeof(Test_Point));
    }

    Test_BOOO_o = corto_function(corto_declareChild(Test_o, "BOOO(/Test/Point p)", corto_function_o));
    if (!Test_BOOO_o) {
        corto_error("Test_load: failed to declare 'Test_BOOO_o' (%s)", corto_lasterr());
        goto error;
    }
    
    if (!corto_checkState(Test_BOOO_o, CORTO_VALID)) {
        Test_BOOO_o->returnType = corto_type(corto_resolve(NULL, "void"));
        Test_BOOO_o->returnsReference = FALSE;
        
        corto_function(Test_BOOO_o)->kind = CORTO_PROCEDURE_CDECL;
        corto_function(Test_BOOO_o)->fptr = (corto_word)_Test_BOOO;
        if (corto_define(Test_BOOO_o)) {
            corto_error("Test_load: failed to define 'Test_BOOO_o' (%s)", corto_lasterr());
            goto error;
        }
    }

    Test_Point_idk_o = corto_function(corto_declareChild(Test_Point_o, "idk()", corto_function_o));
    if (!Test_Point_idk_o) {
        corto_error("Test_load: failed to declare 'Test_Point_idk_o' (%s)", corto_lasterr());
        goto error;
    }
    
    if (!corto_checkState(Test_Point_idk_o, CORTO_VALID)) {
        Test_Point_idk_o->returnType = corto_type(corto_resolve(NULL, "void"));
        Test_Point_idk_o->returnsReference = FALSE;
        
        corto_function(Test_Point_idk_o)->kind = CORTO_PROCEDURE_CDECL;
        corto_function(Test_Point_idk_o)->fptr = (corto_word)_Test_Point_idk;
        if (corto_define(Test_Point_idk_o)) {
            corto_error("Test_load: failed to define 'Test_Point_idk_o' (%s)", corto_lasterr());
            goto error;
        }
    }

    if (!corto_checkState(Test_Point3D_o, CORTO_VALID)) {
        ((corto_type)Test_Point3D_o)->kind = CORTO_COMPOSITE;
        ((corto_type)Test_Point3D_o)->reference = FALSE;
        ((corto_type)Test_Point3D_o)->attr = 0x10;
        ((corto_type)Test_Point3D_o)->options.parentType = NULL;
        ((corto_type)Test_Point3D_o)->options.parentState = 0x5;
        ((corto_type)Test_Point3D_o)->options.defaultType = NULL;
        ((corto_type)Test_Point3D_o)->options.defaultProcedureType = NULL;
        ((corto_interface)Test_Point3D_o)->base = corto_interface((corto_claim(Test_Point_o), Test_Point_o));
        Test_Point3D_o->baseAccess = 0x0;
        Test_Point3D_o->keys.length = 0;
        Test_Point3D_o->keys.buffer = NULL;
        if (corto_define(Test_Point3D_o)) {
            corto_error("Test_load: failed to define 'Test_Point3D_o' (%s)", corto_lasterr());
            goto error;
        }
    }

    if (corto_type(Test_Point3D_o)->size != sizeof(Test_Point3D)) {
        corto_error("Test_load: calculated size '%d' of type 'Test_Point3D_o' doesn't match C-type size '%d'", corto_type(Test_Point3D_o)->size, sizeof(Test_Point3D));
    }

    if (!corto_checkState(Test_Point4D_o, CORTO_VALID)) {
        ((corto_type)Test_Point4D_o)->kind = CORTO_COMPOSITE;
        ((corto_type)Test_Point4D_o)->reference = FALSE;
        ((corto_type)Test_Point4D_o)->attr = 0x10;
        ((corto_type)Test_Point4D_o)->options.parentType = NULL;
        ((corto_type)Test_Point4D_o)->options.parentState = 0x5;
        ((corto_type)Test_Point4D_o)->options.defaultType = NULL;
        ((corto_type)Test_Point4D_o)->options.defaultProcedureType = NULL;
        ((corto_interface)Test_Point4D_o)->base = corto_interface((corto_claim(Test_Point3D_o), Test_Point3D_o));
        Test_Point4D_o->baseAccess = 0x0;
        Test_Point4D_o->keys.length = 0;
        Test_Point4D_o->keys.buffer = NULL;
        if (corto_define(Test_Point4D_o)) {
            corto_error("Test_load: failed to define 'Test_Point4D_o' (%s)", corto_lasterr());
            goto error;
        }
    }

    if (corto_type(Test_Point4D_o)->size != sizeof(Test_Point4D)) {
        corto_error("Test_load: calculated size '%d' of type 'Test_Point4D_o' doesn't match C-type size '%d'", corto_type(Test_Point4D_o)->size, sizeof(Test_Point4D));
    }

    Test_WHATKL_o = corto_function(corto_declareChild(Test_o, "WHATKL(/Test/Point b)", corto_function_o));
    if (!Test_WHATKL_o) {
        corto_error("Test_load: failed to declare 'Test_WHATKL_o' (%s)", corto_lasterr());
        goto error;
    }
    
    if (!corto_checkState(Test_WHATKL_o, CORTO_VALID)) {
        Test_WHATKL_o->returnType = corto_type((corto_claim(Test_Point_o), Test_Point_o));
        Test_WHATKL_o->returnsReference = FALSE;
        
        corto_function(Test_WHATKL_o)->kind = CORTO_PROCEDURE_CDECL;
        corto_function(Test_WHATKL_o)->fptr = (corto_word)_Test_WHATKL;
        if (corto_define(Test_WHATKL_o)) {
            corto_error("Test_load: failed to define 'Test_WHATKL_o' (%s)", corto_lasterr());
            goto error;
        }
    }

    if (_a_) {
        corto_release(_a_);
    }

    return 0;
error:
    if (_a_) {
        corto_release(_a_);
    }

    corto_setAttr(prevAttr);
    return -1;
}
