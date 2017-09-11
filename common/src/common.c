
#include "driver/gen/cpp/common/common.h"

corto_bool cpp_classToUpper = FALSE;

static char* cpp_objectIdIntern(
    g_generator g, 
    corto_object o, 
    cpp_context context, 
    cpp_refKind refKind, 
    cpp_idKind idKind, 
    corto_id buffer)
{
    corto_id typeName;
    typeName[0] = '\0';
    if (corto_instanceof(corto_function_o, o)) {
        corto_function f = corto_function(o);
        corto_signatureName(corto_idof(f), typeName);
    } else if (corto_instanceof(corto_type_o, o)) {
        corto_type t = corto_type(o);
        if (t->kind == CORTO_PRIMITIVE) {
            corto_primitive p = corto_primitive(t);
            if (p->kind == CORTO_TEXT && context != Cpp_CType) {
                // use std::string for CORTO_TEXT and does not ask for CType
                strcpy(buffer, "::std::string");
            } else {
                c_primitiveId(g, p, buffer);
            }
        } else if (cpp_isVoid(t)) {
            strcpy(buffer, "void");
        } else if (t->kind == CORTO_COLLECTION) {
            strcpy(buffer, "void*"); // TODO: 
        } else if (t->kind == CORTO_ITERATOR) {
            strcpy(buffer, "void*"); // TODO:
        } else {
            switch (context) {
                case Cpp_Class: {
                    if (refKind == Cpp_ById) {
                        sprintf(typeName, "C%s", corto_idof(t));
                    } else if (refKind == Cpp_ByVal) {
                        sprintf(typeName, "C%sVal", corto_idof(t));
                    } else if (refKind == Cpp_ByRef) {
                        sprintf(typeName, "C%sRef", corto_idof(t));
                    }
                    break;
                }
                case Cpp_Template: {
                    sprintf(typeName, "T%s", corto_idof(t));
                    break;
                }
                case Cpp_CType: {
                    sprintf(typeName, "%s::%s", cpp_cprefix(), corto_idof(t));
                    if ((refKind == Cpp_ByRef) && !t->reference) {
                        strcat(typeName, "*");
                    }
                    break;
                }
                default: {
                    strcpy(typeName, corto_idof(t));
                    break;
                }
            }
        }
    } else {
        strcpy(typeName, corto_idof(o));
    }

    if (typeName[0]) {
        buffer[0] = '\0';
        corto_id scope;
        switch(idKind) {
            case Cpp_AbsoluteId: {
                corto_path(scope, root_o, corto_parentof(o), "::");
                if (strcmp(scope, ".")) {
                    sprintf(buffer, "%s::", scope);
                }
                break;
            }
            case Cpp_FullId: {
                corto_path(scope, g_getCurrent(g), corto_parentof(o), "::");
                if (strcmp(scope, ".") && strcmp(scope, "..")) {
                    sprintf(buffer, "%s::", scope);
                }
                break;
            }
            default:{}
        }
        strcat(buffer, typeName);
    }

    return buffer;
}

char* cpp_objectId(g_generator g, corto_object o, cpp_context c, cpp_refKind r, corto_id b)
{
    return cpp_objectIdIntern(g, o, c, r, Cpp_Id, b);
}

char* cpp_objectFullId(g_generator g, corto_object o, cpp_context c, cpp_refKind r, corto_id b)
{
    return cpp_objectIdIntern(g, o, c, r, Cpp_FullId, b);
}

char* cpp_objectAbsoluteId(g_generator g, corto_object o, cpp_context c, cpp_refKind r, corto_id b)
{
    return cpp_objectIdIntern(g, o, c, r, Cpp_AbsoluteId, b);
}

g_file cpp_headerOpen(g_generator g, corto_object o) {
    corto_id definedMacro;
    g_file result;

    corto_path(definedMacro, root_o, o, "_");
    corto_strupper(definedMacro);

    result = g_fileOpen(g, "%s.hpp", corto_idof(o));
    g_fileWrite(result, "\n");
    g_fileWrite(result, "#ifndef %s_HPP\n", definedMacro);
    g_fileWrite(result, "#define %s_HPP\n", definedMacro);
    g_fileWrite(result, "\n");

    return result;
}

void cpp_headerClose(g_generator g, g_file file) {
    cpp_closeScope(file);
    g_fileWrite(file, "\n");
    g_fileWrite(file, "#endif\n");
    g_fileClose(file);
}

g_file cpp_sourceOpen(g_generator g, corto_object o) {
    corto_id definedMacro;
    g_file result;

    corto_path(definedMacro, root_o, o, "_");
    corto_strupper(definedMacro);

    result = g_fileOpen(g, "%s.cpp", corto_idof(o));
    g_fileWrite(result, "\n");
    cpp_include(g, result, g_getCurrent(g));

    g_fileWrite(result, "\n");
    cpp_openScope(result, g_getCurrent(g));
    g_fileWrite(result, "\n");

    return result;
}

void cpp_sourceClose(g_generator g, g_file file) {
    cpp_closeScope(file);
    g_fileWrite(file, "\n");
    g_fileClose(file);
}

char* cpp_mainheader(g_generator g, corto_id header) {
    c_mainheader(g, header);
    strcat(header, "pp");
    return header;
}

void cpp_include(g_generator g, g_file file, corto_object o) {
    corto_id name;
    corto_object package = c_findPackage(g, o);

    corto_assert (package != NULL, "can't include '%s' from non-package scopes",
        corto_fullpath(NULL, o));

    c_includeFrom(
      g,
      file,
      package,
      c_filename(g, name, o, "hpp"));
}
/* Function builds a scope-stack from root to module */
static void cpp_scopeStack(
    corto_object module,
    corto_object* stack /* corto_object[SD_MAX_SCOPE_DEPTH] */)
{
    corto_uint32 count;
    corto_object ptr;

    corto_assert(module != NULL, "NULL passed for module to sd_utilModuleStack");

    /* Count scope depth */
    ptr = module;
    count = 1; /* For self */
    while((ptr = corto_parentof(ptr))) {
        count++;
    }

    if(count > CORTO_MAX_SCOPE_DEPTH) {
        corto_error("cpp_scopeStack: unsupported scope-depth (depth=%d, max=%d).", count, CORTO_MAX_SCOPE_DEPTH);
    }
    corto_assert(count <= CORTO_MAX_SCOPE_DEPTH, "MAX_SCOPE_DEPTH overflow.");

    /* Fill module stack */
    ptr = module;
    while(count) {
        stack[count-1] = ptr;
        ptr = corto_parentof(ptr);
        count--;
    }

    /* ptr should be NULL */
    corto_assert(!ptr, "ptr is NULL.");
}

/* Find first common module in two module-stacks */
static corto_object cpp_commonScope(
    corto_object from,
    corto_object to,
    corto_object* fromStack,
    corto_object* toStack,
    corto_uint32* i_out)
{
    corto_object fromPtr, toPtr;
    corto_uint32 i;

    /* fromPtr and toPtr will initially point to base */
    i = 0;
    do {
        fromPtr = fromStack[i];
        toPtr = toStack[i];
        i++;
    }while((fromPtr != from) && (toPtr != to) && (fromStack[i] == toStack[i]));

    /* Common module is now stored in fromPtr and toPtr. */

    if(i_out) {
        *i_out = i;
    }

    return fromPtr;
}

/* Check whether a type translates to a native construct or may act as a C++ namespace */
corto_bool cpp_nativeType(corto_object o) {
	corto_bool result = FALSE;

	if(corto_class_instanceof(corto_type_o, o)) {
		switch(corto_type(o)->kind) {
		case CORTO_VOID:
		    if(corto_type(o)->reference) {
		        result = TRUE;
		    }
			break;
		default:
			result = TRUE;
			break;
		}
	}

	return result;
}

/* Open a scope */
void cpp_openScope(
    g_file file,
    corto_object to)
{
    corto_object from;

    if (to) {

        /* Do not open namespaces for non-void type-scopes */
        while(cpp_nativeType(to)) {
        	to = corto_parentof(to);
        }

        /* If context->module is NULL, start from root */
        from = g_fileScopeGet(file);
        if(!from) {
            from = root_o;
        }

        /* If from and to are not equal, find shortest path between modules. */
        if(from != to) {
            corto_object fromStack[CORTO_MAX_SCOPE_DEPTH], toStack[CORTO_MAX_SCOPE_DEPTH];
            corto_object fromPtr, toPtr;
            corto_uint32 i;

            /* Find common module. First build up a scope-stack for the two modules which
             * are ordered base -> <module>. Then walk through these stacks to find the
             * last common module. */
            cpp_scopeStack(from, fromStack);
            cpp_scopeStack(to, toStack);
            fromPtr = toPtr = cpp_commonScope(from, to, fromStack, toStack, &i);

            /* Walk down from module 'from' to 'toPtr' */
            fromPtr = from;
            while(fromPtr != toPtr) {
                g_fileWrite(file, "}\n");
                fromPtr = corto_parentof(fromPtr);
            }

            /* Walk from toPtr to 'to' */
            while(toPtr != to) {
                corto_id id;
                toPtr = toStack[i];
                g_fileWrite(file, "namespace %s {\n", g_oid(g_fileGetGenerator(file), toPtr, id));
                i++;
            }

            /* Update context->module */
            g_fileScopeSet(file, to);
        }
    }
}

void cpp_closeScope(g_file file) {
    corto_object ptr;

    g_fileWrite(file, "\n");

    if((ptr = g_fileScopeGet(file))) {
        while((ptr = corto_parentof(ptr))) {
            g_fileWrite(file, "}\n");
        }

        g_fileScopeSet(file, NULL);
    }
}

char *cpp_cprefix(void) {
    return "types";
}

corto_int16 cpp_isVoid(corto_type t) {
    return (t->kind == CORTO_VOID) && !t->reference;
}


// corto_int16 cpp_assignCTypeFromCppType(
//     g_generator g,
//     g_file file, 
//     corto_type t,
//     corto_bool ptr,
//     corto_string lvalue,
//     corto_string rvalue)
// {
//     if (t->kind == CORTO_PRIMITIVE) {
//         corto_primitive p = corto_primitive(t);
//         if (p->kind == CORTO_TEXT) {
//             // strcpy({lvalue}, {rvalue}.str());
//             g_fileWrite(file, "%s = corto_strdup(%s.c_str());\n", lvalue, rvalue);
//         } else {
//             // {lvalue} = {rvalue};
//             g_fileWrite(file, "%s = %s\n", lvalue, rvalue);
//         }
//     } else if (cpp_isVoid(t)) {

//     } else if (t->kind == CORTO_COLLECTION) {
//         // TODO:
//     } else if (t->kind == CORTO_ITERATOR) {
//         // TODO:
//     } else {
//         if (t->reference) {
//             g_fileWrite(file, "corto_ptr_setref(%s%s, %s.ptr());\n", ptr ? "" : "&", lvalue, rvalue);
//         } else {
//             if (ptr) {
//                 //g_fileWrite(file, "corto_ptr_setref(%s%s, %s.ptr());\n", lvalue, rvalue);
//             } else {
//                 g_fileWrite(file, "%s = *%s.ptr();\n", lvalue, rvalue);
//             }
//         }
//     }
// }

// corto_int16 cpp_assignCppTypeFromCType(
//     g_generator g,
//     g_file file, 
//     corto_type t,
//     corto_bool ptr,
//     corto_string lvalue,
//     corto_string rvalue)
// {
//     return 0;
// }

char* cpp_typeCastCppTypeToCType(
    g_generator g,
    corto_type t,
    corto_string rvalue,
    corto_string buffer)
{
    if (t->kind == CORTO_PRIMITIVE) {
        corto_primitive p = corto_primitive(t);
        if (p->kind == CORTO_TEXT) {
            sprintf(buffer, "corto_strdup(%s.c_str())", rvalue);
        } else {
            sprintf(buffer, rvalue);
        }
    } else if (cpp_isVoid(t)) {

    } else if (t->kind == CORTO_COLLECTION) {
        // TODO:
    } else if (t->kind == CORTO_ITERATOR) {
        // TODO:
    } else {
        // 
        corto_id cClassId;
        cpp_objectFullId(g, t, Cpp_CType, Cpp_ByRef, cClassId);
    
        if (t->reference) {
            sprintf(buffer, "(%s)(%s.ptr())", cClassId, rvalue);
        } else {
            sprintf(buffer, "*(%s)(%s.ptr())", cClassId, rvalue);
        }
    }

    return buffer;
}

char* cpp_typeCastCTypeToCppType(
    g_generator g,
    corto_type t,
    corto_bool ptr,
    corto_string rvalue,
    corto_string buffer)
{
    if (t->kind == CORTO_PRIMITIVE) {
        corto_primitive p = corto_primitive(t);
        if (p->kind == CORTO_TEXT) {
            sprintf(buffer, "::std::string(%s%s)", ptr ? "" : "*", rvalue);
        } else {
            sprintf(buffer, "%s%s", ptr ? "" : "*", rvalue);
        }
    } else if (cpp_isVoid(t)) {

    } else if (t->kind == CORTO_COLLECTION) {
        // TODO:
    } else if (t->kind == CORTO_ITERATOR) {
        // TODO:
    } else {
        // 
        corto_id classId, cTypeId;
        cpp_objectFullId(g, t, Cpp_Class, Cpp_ById, classId);
        cpp_objectFullId(g, t, Cpp_CType, Cpp_ById, cTypeId);
        
        if (t->reference) {
            sprintf(buffer, "%s(%s)", classId, rvalue);
        } else {
            sprintf(buffer, "%s(%s%s, %s_o)", classId, ptr ? "" : "&", rvalue, cTypeId);
        }
    }

    return buffer;
}


corto_int16 cpp_walkProcedureParam(
    g_generator g, 
    g_file file, 
    corto_function f, 
    corto_bool c) 
{
    corto_id paramTypeId;
    corto_int32 offset = 0;
    corto_int32 i = 0;
    corto_int32 length = f->parameters.length;
    if (c && c_procedureHasThis(f)) {
        length++; i++;
        offset = -1;
        
        c_typeret(g, corto_parentof(f), C_ByReference, paramTypeId);
        g_fileWrite(file, "%s _this", paramTypeId);
    }

    if (length > 3) {
        g_fileIndent(file);
    }

    for (; i < length; i ++) {
        corto_parameter *p = &f->parameters.buffer[i + offset];
        if (i) {
            g_fileWrite(file, ", ");
            if (length > 3) {
                g_fileWrite(file, "\n");
            }
        }
        if (c) {
            c_typeret(g, p->type, C_ByReference, paramTypeId);
        } else {
            cpp_objectFullId(g, p->type, Cpp_Class, Cpp_ById, paramTypeId);
        }

        g_fileWrite(file, "%s %s", paramTypeId, p->name);
    }

    if (length > 3) {
        g_fileDedent(file);
    }

    return 0;
}

corto_int16 cpp_visitProcedure(
    g_generator g, 
    g_file header, 
    g_file source, 
    corto_function f, 
    corto_bool method)
{
    corto_id resultId, methodId, methodFullId;

    cpp_objectFullId(g, f->returnType, Cpp_Class, Cpp_ById, resultId);
    corto_signatureName(corto_idof(f), methodId);
    cpp_objectFullId(g, f, Cpp_Type, Cpp_ById, methodFullId);
    
    if (method && !c_procedureHasThis(f)) {
        g_fileWrite(header, "static ");
    }

    g_fileWrite(header, "%s %s(", resultId, methodId);
    cpp_walkProcedureParam(g, header, f, FALSE);
    g_fileWrite(header, ");\n");

    char *snippetId;
    if (f->overloaded) {
        snippetId = corto_idof(f);
    } else {
        snippetId = methodId;
    }

    g_fileWrite(source, "%s %s(", resultId, methodFullId);
    cpp_walkProcedureParam(g, source, f, FALSE);
    g_fileWrite(source, ")\n");
    g_fileWrite(source, "{\n");

    g_fileIndent(source);
    corto_string snippet;
    if ((snippet = g_fileLookupSnippet(source, snippetId))) {
        g_fileWrite(source, "%s", snippet);
    } else {
        g_fileWrite(source, "/* Insert Implementation*/\n\n");
    }
    g_fileDedent(source);

    g_fileWrite(source, "}\n");

    return 0;
}