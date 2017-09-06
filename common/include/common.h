
#ifndef COMMON_H
#define COMMON_H

/* Add include files here */
#include <corto/g/g.h>
#include <driver/gen/c/common/common.h>

#ifdef __cplusplus
extern "C" {
#endif
/*
cpp_context::
    Cpp_Class       C{Name};
    Cpp_Template    T{Name};
    Cpp_Type        {Name};
    Cpp_CType       {c_type};

cpp_refKind::
    Cpp_ById {cpp_context};
    Cpp_ByVal if Class -> C{Name}Ref; if CType {c_type}; else {cpp_context}
    Cpp_ByRef if Class -> C{Name}Val; if CType {c_type || c_type*}; else {cpp_context}
*/

typedef enum cpp_context {
    Cpp_Class,
    Cpp_Template,
    Cpp_Type,
    Cpp_CType
} cpp_context;

typedef enum cpp_refKind {
    Cpp_ById,
    Cpp_ByVal,
    Cpp_ByRef
} cpp_refKind;

char* _cpp_typeId(g_generator g, corto_type t, cpp_context context, cpp_refKind refKind, corto_id buffer);
char* _cpp_typeFullId(g_generator g, corto_type t, cpp_context context, cpp_refKind refKind, corto_id buffer);

#define cpp_typeId(g, t, context, refKind, buffer) _cpp_typeId(g, corto_type(t), context, refKind, buffer)
#define cpp_typeFullId(g, t, context, refKind, buffer) _cpp_typeFullId(g, corto_type(t), context, refKind, buffer)

g_file cpp_headerOpen(g_generator g, corto_object o);
void cpp_headerClose(g_generator g, g_file file);

g_file cpp_sourceOpen(g_generator g, corto_object o);
void cpp_sourceClose(g_generator g, g_file file);

char* cpp_mainheader(g_generator g, corto_id header);
void cpp_include(g_generator g, g_file file, corto_object o);

/* Open & close namespaces. Used for C++ compatibility */
void cpp_openScope(g_file file, corto_object o);
void cpp_closeScope(g_file file);

char *cpp_cprefix(void);

corto_int16 cpp_isVoid(corto_type t);

// corto_int16 cpp_assignCTypeFromCppType(
//     g_generator g,
//     g_file file, 
//     corto_type t,
//     corto_bool ptr,
//     corto_string lvalue,
//     corto_string rvalue);
// corto_int16 cpp_assignCppTypeFromCType(
//     g_generator g,
//     g_file file, 
//     corto_type t,
//     corto_bool ptr,
//     corto_string lvalue,
//     corto_string rvalue);
//
char* cpp_typeCastCppTypeToCType(
    g_generator g,
    corto_type t,
    corto_string rvalue,
    corto_string buffer);
//
char* cpp_typeCastCTypeToCppType(
    g_generator g,
    corto_type t,
    corto_bool ptr,
    corto_string rvalue,
    corto_string buffer);

// char* cpp_typeIdFromStr(g_generator g, char *str, cpp_context context, corto_id buffer);
// char* cpp_varId(g_generator g, corto_object o, corto_id buffer);

#ifdef __cplusplus
}
#endif

#endif /* COMMON_H */
