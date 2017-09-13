
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
enum cpp_modifier {
    Cpp_Owned = 0x01,
    Cpp_Ptr = 0x02,
    Cpp_Optional = 0x04,
    Cpp_NoCopy = 0x08
};
typedef int32_t cpp_modifierMask;

typedef enum cpp_idKind {
    Cpp_Id,
    Cpp_FullId,
    Cpp_AbsoluteId
} cpp_idKind;

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

char* cpp_objectId(g_generator g, corto_object o, cpp_context context, cpp_refKind refKind, corto_id buffer);
char* cpp_objectFullId(g_generator g, corto_object o, cpp_context context, cpp_refKind refKind, corto_id buffer);
char* cpp_objectAbsoluteId(g_generator g, corto_object o, cpp_context context, cpp_refKind refKind, corto_id buffer);

g_file cpp_headerOpen(g_generator g, corto_object o, corto_id ext);
void cpp_headerClose(g_generator g, g_file file);

g_file cpp_sourceOpen(g_generator g, corto_object o);
void cpp_sourceClose(g_generator g, g_file file);

char* cpp_mainheader(g_generator g, corto_id header);
void cpp_include(g_generator g, g_file file, corto_object o);

/* Open & close namespaces. Used for C++ compatibility */
void cpp_useNamespace(g_generator g, g_file file, corto_object to);

void cpp_openScope(g_file file, corto_object o);
void cpp_closeScope(g_file file);

char *cpp_cprefix(void);

corto_int16 cpp_isVoid(corto_type t);

char* cpp_typeCastCppTypeToCType(g_generator g, corto_type t, cpp_modifierMask modifiers, corto_string rvalue, corto_string buffer);
char* cpp_typeCastCTypeToCppType(g_generator g, corto_type t, cpp_modifierMask modifiers, corto_string rvalue, corto_string buffer);

corto_int16 cpp_walkProcedureParam(g_generator g, g_file file, corto_function f, corto_bool c);
corto_int16 cpp_visitProcedure(g_generator g, g_file header, g_file source, corto_function f, corto_bool method);
corto_int16 cpp_apiAssign(g_generator g, g_file f, corto_type t, cpp_modifierMask modifiers, corto_string lvalue, corto_string rvalue);

// char* cpp_typeIdFromStr(g_generator g, char *str, cpp_context context, corto_id buffer);
// char* cpp_varId(g_generator g, corto_object o, corto_id buffer);

#ifdef __cplusplus
}
#endif

#endif /* COMMON_H */
