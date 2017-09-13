#include <driver/gen/c/common/common.h>
#include <driver/gen/cpp/common/common.h>
#include <driver/gen/cpp/class/class.h>

#define TRACE(msg) printf("%s:%d\n", msg, __LINE__)
#define ERROR() printf("ERROR: %s:%d\n", __func__, __LINE__)

static corto_int16 cpp_hiddenImplOpen(cpp_classWalk_t *data) {
    data->hiddenImpl = g_hiddenFileOpen(data->g, "_class.cpp", corto_idof(g_getCurrent(data->g)));
    if (!data->hiddenImpl) {
        goto error;
    }

    corto_id mainheader;
    g_fileWrite(data->hiddenImpl,"#include <%s>\n", cpp_mainheader(data->g, mainheader));

    return 0;
error:
    ERROR();
    return -1;
}

/* ******************
 * Metadata 
 * ******************/

static corto_int16 cpp_walkMetadata(corto_interface type, cpp_classWalk_t *data) {
    corto_id specifier, objectId, cTypeId, typeId, fullId;
    
    corto_type t = corto_typeof(type);

    c_typeret(data->g, t, C_ByReference, specifier);
    c_varId(data->g, type, objectId);
    c_typeId(data->g, type, cTypeId);

    cpp_objectId(data->g, type, Cpp_Type, Cpp_ById, typeId);
    cpp_objectAbsoluteId(data->g, type, Cpp_CType, Cpp_ById, fullId);

    g_fileWrite(data->header, "namespace %s {\n", cpp_cprefix());
    g_fileIndent(data->header);

    g_fileWrite(data->header, "typedef %s %s;\n", cTypeId, typeId);
    g_fileWrite(data->header, "extern %s& %s_o;\n", specifier, typeId);

    g_fileDedent(data->header);
    g_fileWrite(data->header, "}\n\n");

    g_fileWrite(data->hiddenImpl, "extern %s& %s_o = %s;\n", specifier, fullId, objectId);

    return 0;
}

/* ******************
 * Members
 * ******************/
static corto_int16 cpp_visitMember(corto_walk_opt* s, corto_value *info, void *userData) {
    cpp_classWalk_t *data = userData;
    corto_type t = corto_value_typeof(info);
    corto_member m = info->is.member.t;
    
    //corto_id id, cId, classId, memberId;
    corto_id memberType, classId, memberId, cClassId;

    cpp_objectFullId(data->g, t, Cpp_Class, Cpp_ById, memberType);
    g_oid(data->g, m, memberId);

    g_fileWrite(data->header, "%s %s() const;\n", memberType, memberId);
    g_fileWrite(data->header, "void %s(%s value);\n", memberId, memberType);

    cpp_objectAbsoluteId(data->g, t, Cpp_Class, Cpp_ById, memberType);
    cpp_objectAbsoluteId(data->g, corto_parentof(m), Cpp_Class, Cpp_ById, classId);
    cpp_objectAbsoluteId(data->g, corto_parentof(m), Cpp_CType, Cpp_ByRef, cClassId);

    g_fileWrite(data->hiddenImpl, "%s %s::%s() const\n", memberType, classId, memberId);
    g_fileWrite(data->hiddenImpl, "{\n");
    g_fileIndent(data->hiddenImpl);
    g_fileWrite(data->hiddenImpl, "return %s{((%s)this->ptr())->%s};\n", memberType, cClassId, memberId);
    g_fileDedent(data->hiddenImpl);
    g_fileWrite(data->hiddenImpl, "}\n");

    g_fileWrite(data->hiddenImpl, "void %s::%s(%s value)\n", classId, memberId, memberType);
    g_fileWrite(data->hiddenImpl, "{\n");
    g_fileIndent(data->hiddenImpl);
    
    cpp_modifierMask mask = Cpp_NoCopy | ((t->kind == CORTO_PRIMITIVE) ? 0 : Cpp_Ptr);
    corto_id cValue;
    cpp_typeCastCppTypeToCType(data->g, t, mask, "value", cValue);

    corto_id member;
    sprintf(member, "((%s)this->ptr())->%s", cClassId, memberId);

    cpp_apiAssign(data->g, data->hiddenImpl, t, Cpp_NoCopy, member, cValue);

    //g_fileWrite(data->hiddenImpl, "%s{((%s)this->ptr())->%s} = value;\n",memberType, cClassId, memberId);
    g_fileDedent(data->hiddenImpl);
    g_fileWrite(data->hiddenImpl, "}\n");

    return 0;
}

static corto_int16 cpp_walkMembers(corto_interface type, cpp_classWalk_t *data) {
    corto_walk_opt s;
    corto_walk_init(&s);
    s.metaprogram[CORTO_MEMBER] = cpp_visitMember;
    s.metaprogram[CORTO_BASE] = NULL;
    if (corto_metawalk(&s, type, data)) {
        goto error;
    }
    return 0;
error: ERROR();
    return -1;
}

/* **********************
 * Functions
 * **********************/
static corto_int16 cpp_methodProxy(corto_function f, cpp_classWalk_t *data) {
    corto_id proxyId, methodId, cReturnId, cppReturnId;
    corto_id cppType;
    corto_int32 i = 0;
    corto_int32 parametersLength = f->parameters.length;
    corto_bool hasThis = c_procedureHasThis(f);
    corto_bool returnsValue = !cpp_isVoid(f->returnType);

    c_functionName(data->g, f, proxyId);

    strcpy(methodId, corto_idof(f));
    corto_signatureName(methodId, methodId);

    c_typeret(data->g, f->returnType, f->returnsReference, cReturnId);
    cpp_objectAbsoluteId(data->g, f->returnType, Cpp_Class, Cpp_ById, cppReturnId);

    g_fileWrite(data->hiddenImpl, "extern \"C\" %s %s(", cReturnId, proxyId);
    
    cpp_walkProcedureParam(data->g, data->hiddenImpl, f, TRUE);
    g_fileWrite(data->hiddenImpl, ")\n");
    g_fileWrite(data->hiddenImpl, "{\n");
    g_fileIndent(data->hiddenImpl);

    /* Wrap C parameters in C++ types */
    if (hasThis) {
        cpp_objectAbsoluteId(data->g, corto_parentof(f), Cpp_Class, Cpp_ById, cppType);
        g_fileWrite(data->hiddenImpl, "%s _instance(_this);\n", cppType);
    }

    for (i = 0; i < parametersLength; i++) {
        corto_parameter *p = &f->parameters.buffer[i];
        cpp_objectAbsoluteId(data->g, p->type, Cpp_Class, Cpp_ById, cppType);
        g_fileWrite(data->hiddenImpl, "%s _%s(%s);\n", cppType, p->name, p->name);
    }

    if (returnsValue) {
        g_fileWrite(data->hiddenImpl, "%s result = ", cppReturnId);
    }

    if (hasThis) {
        g_fileWrite(data->hiddenImpl, "_instance.");
    } else {
        cpp_objectAbsoluteId(data->g, corto_parentof(f), Cpp_Class, Cpp_ById, cppType);
        g_fileWrite(data->hiddenImpl, "%s::", cppType);
    }
    
    g_fileWrite(data->hiddenImpl, "%s(", methodId);
    if (parametersLength > 3) {
        g_fileIndent(data->hiddenImpl);
    }
    for (i = 0; i < parametersLength; i++) {
        if (i) {
            g_fileWrite(data->hiddenImpl, ", ");
            if (parametersLength > 3) {
                g_fileWrite(data->hiddenImpl, "\n");
            }
        }
        corto_parameter *p = &f->parameters.buffer[i];
        g_fileWrite(data->hiddenImpl, "_%s", p->name);
    }
    if (parametersLength > 3) {
        g_fileDedent(data->hiddenImpl);
    }
    g_fileWrite(data->hiddenImpl, ");\n");
    
    if (returnsValue) {
        corto_id buffer;
        g_fileWrite(data->hiddenImpl, 
            "return %s;\n", 
            cpp_typeCastCppTypeToCType(
                data->g,
                f->returnType,
                0,
                "result",
                buffer
            )
        );
    }

    g_fileDedent(data->hiddenImpl);
    g_fileWrite(data->hiddenImpl, "}\n");

    return 0;
}

static corto_int16 cpp_walkProcedures(corto_interface type, cpp_classWalk_t *data) {
    corto_objectseq scope = corto_scopeClaim(type);
    corto_int32 i;

    for (i = 0; i < scope.length; i++) {
        corto_object child = scope.buffer[i];
        if (corto_instanceof(corto_function_o, child)) {
            if (!data->source) {
                data->source = cpp_sourceOpen(data->g, type);
                if (!data->source) {
                    goto error;
                }
            }

            if (cpp_visitProcedure(data->g, data->header, data->source, child, TRUE)) {
                goto error;
            }

            if (cpp_methodProxy(child, data)) {
                goto error;
            }
        }
    }

    corto_scopeRelease(scope);
    if (data->source) {
        cpp_sourceClose(data->g, data->source);
        data->source = NULL;
    }

    return 0;
error: 
    ERROR();
    return -1;
}
    

/*
    // operators 
    {Class}& operator=(const Point& p);
    {Class}& operator=({Class} &&p);
    {Class}& operator=({CTypeRef} ref);

    {Class}& operator=(const Point& p) {return {baseClass}::operator=(other);}
    {Class}& operator=({Class} &&p);
    {Class}& operator=({CTypeRef} ref);
*/

static corto_int16 cpp_classOperators(corto_interface type, cpp_classWalk_t *data) {
    corto_id classId, fullClassId, cType, fullCType;
    
    cpp_objectId(data->g, type, Cpp_Class, Cpp_ById, classId);
    cpp_objectAbsoluteId(data->g, type, Cpp_Class, Cpp_ById, fullClassId);

    cpp_objectId(data->g, type, Cpp_CType, Cpp_ByRef, cType);
    cpp_objectAbsoluteId(data->g, type, Cpp_CType, Cpp_ByRef, fullCType);

    g_fileWrite(data->header, "%s& operator=(const %s& other);\n", classId, classId);
    g_fileWrite(data->hiddenImpl, "%s& %s::operator=(const %s& other)\n", fullClassId, fullClassId, fullClassId);
    g_fileWrite(data->hiddenImpl, "{\n");
    g_fileIndent(data->hiddenImpl);
    g_fileWrite(data->hiddenImpl, "return %s::Base::operator=(other);\n", fullClassId);
    g_fileDedent(data->hiddenImpl);
    g_fileWrite(data->hiddenImpl, "}\n");
    
    g_fileWrite(data->header, "%s& operator=(%s&& other);\n", classId, classId);
    g_fileWrite(data->hiddenImpl, "%s& %s::operator=(%s&& other)\n", fullClassId, fullClassId, fullClassId);
    g_fileWrite(data->hiddenImpl, "{\n");
    g_fileIndent(data->hiddenImpl);
    g_fileWrite(data->hiddenImpl, "return %s::Base::operator=(other);\n", fullClassId);
    g_fileDedent(data->hiddenImpl);
    g_fileWrite(data->hiddenImpl, "}\n");

    g_fileWrite(data->header, "%s& operator=(%s other);\n", classId, cType);
    g_fileWrite(data->hiddenImpl, "%s& %s::operator=(%s other)\n", fullClassId, fullClassId, fullCType);
    g_fileWrite(data->hiddenImpl, "{\n");
    g_fileIndent(data->hiddenImpl);
    g_fileWrite(data->hiddenImpl, "return %s::Base::operator=(other);\n", fullClassId);
    g_fileDedent(data->hiddenImpl);
    g_fileWrite(data->hiddenImpl, "}\n");
    
    return 0;
error:
    ERROR();
    return -1;
}

/*
    CPoint();
    CPoint(const CPoint& other);
    CPoint(CPoint&& other);
    CPoint(types::Point* ref);
    CPoint(types::Point val);
    CPoint(types::Point* ref, ::corto::Type type);
    ~CPoint();

    CPoint() : Base() {}
    CPoint(const CPoint &other) : Base(other) {}

*/
static corto_int16 cpp_classConstructs(corto_interface type, cpp_classWalk_t *data) {
    corto_id classId, fullClassId, cType, fullCType;
    
    cpp_objectId(data->g, type, Cpp_Class, Cpp_ById, classId);
    cpp_objectAbsoluteId(data->g, type, Cpp_Class, Cpp_ById, fullClassId);

    cpp_objectId(data->g, type, Cpp_CType, Cpp_ByRef, cType);
    cpp_objectAbsoluteId(data->g, type, Cpp_CType, Cpp_ByRef, fullCType);

    g_fileWrite(data->header, "%s();\n", classId);
    g_fileWrite(data->hiddenImpl, "%s() : %s::Base() {}\n", fullClassId, fullClassId);

    g_fileWrite(data->header, "%s(const %s& other);\n", classId, classId);
    g_fileWrite(data->hiddenImpl, "%s(const %s& other) : %s::Base(other) {}\n", fullClassId, fullClassId, fullClassId);

    g_fileWrite(data->header, "%s(%s&& other);\n", classId, classId);
    g_fileWrite(data->hiddenImpl, "%s(%s&& other) : %s::Base(std::move(other)) {}\n", fullClassId, fullClassId, fullClassId);

    g_fileWrite(data->header, "%s(%s ref);\n", classId, cType);
    g_fileWrite(data->hiddenImpl, "%s(%s ref) : %s::Base(ref) {}\n", fullClassId, fullCType, fullClassId);
    
    if (type->kind == CORTO_STRUCT) {
        corto_id ctype, fullctype;
        cpp_objectId(data->g, type, Cpp_CType, Cpp_ByVal, ctype);
        cpp_objectAbsoluteId(data->g, type, Cpp_CType, Cpp_ByVal, fullctype);

        g_fileWrite(data->header, "%s(%s val);\n", classId, ctype);
        g_fileWrite(data->hiddenImpl, "%s(%s val) : %s::Base(&val, %s_o) {}\n", fullClassId, fullctype, fullctype, fullClassId);
    }

    g_fileWrite(data->header, "%s(%s ref, ::corto::Type type);\n", classId, cType);
    g_fileWrite(data->hiddenImpl, "%s(%s ref, ::corto::Type type) : %s::Base(ref, type) {}\n", fullClassId, fullCType, fullClassId);

    cpp_objectAbsoluteId(data->g, corto_parentof(type), Cpp_CType, Cpp_ByVal, fullClassId);
    g_fileWrite(data->header, "\n");
    g_fileWrite(data->header, "~%s();\n", classId);
    g_fileWrite(data->hiddenImpl, "%s::~%s(){}\n", fullClassId, classId);
}

/* Generate code for a corto interface type (interface, class, struct, procedure) */
static corto_int16 cpp_visitClass(corto_interface type, cpp_classWalk_t *data) {
    
    corto_id class, cType, baseClass, baseCType;
    corto_id mainheader;
    cpp_objectId(data->g, type, Cpp_Class, Cpp_ById, class);
    cpp_mainheader(data->g, mainheader);
    if (!type->base) {
        strcpy(baseClass, "::corto::Object");
        strcpy(baseCType, "corto_object");
    } else {
        cpp_objectFullId(data->g, type->base, Cpp_Class, Cpp_ById, baseClass);
        cpp_objectFullId(data->g, type->base, Cpp_CType, Cpp_ById, baseCType);
    }
    data->header = cpp_headerOpen(data->g, type, "hpp");
    if (!data->header) {
        goto error;
    }

    g_fileWrite(data->hiddenImpl, "\n");
    g_fileWrite(data->hiddenImpl, "// Implementation for %s\n", class);

    g_fileWrite(data->header, "#include <%s>\n", mainheader);
    g_fileWrite(data->header, "\n");

    cpp_openScope(data->header, g_getCurrent(data->g));
    g_fileWrite(data->header, "\n");

    if (cpp_walkMetadata(type, data)) {
        goto error;
    }

    g_fileWrite(data->header, "// Implementation of corto type %s\n", corto_fullpath(NULL, type));
    g_fileWrite(data->header, "class %s : public %s\n", class, baseClass);
    g_fileWrite(data->header, "{\n");
    g_fileWrite(data->header, "public:\n");
    g_fileIndent(data->header);
    g_fileWrite(data->header, "typedef %s Base;\n\n", baseClass);

    g_fileWrite(data->hiddenImpl, "\n");
    g_fileWrite(data->header, "// Getters/setters\n");
    if (cpp_walkMembers(type, data)) {
        goto error;
    }
    g_fileWrite(data->header, "\n");

    g_fileWrite(data->hiddenImpl, "\n");
    g_fileWrite(data->header, "// Methods\n");
    if (cpp_walkProcedures(type, data)) {
        goto error;
    }
    g_fileWrite(data->header, "\n");

    g_fileWrite(data->hiddenImpl, "\n");
    g_fileWrite(data->header, "// Operators\n");
    if (cpp_classOperators(type, data)) {
        goto error;
    }
    g_fileWrite(data->header, "\n");

    g_fileWrite(data->hiddenImpl, "\n");
    g_fileWrite(data->header, "// Constructs\n");
    if (cpp_classConstructs(type, data)) {
        goto error;
    }
    g_fileWrite(data->header, "\n");

    g_fileDedent(data->header);
    g_fileWrite(data->header, "};\n");
    cpp_closeScope(data->header);
    
    cpp_headerClose(data->g, data->header);
    return 0;
error:
ERROR();
    return -1;
}

static corto_int16 cpp_visitFunction(corto_interface f, cpp_classWalk_t *data) {
    if (!c_procedureHasThis(f)) {

    }
error:
    ERROR();
    return -1;
}



static int cpp_walkTypes(corto_object o, void* userData) {
    cpp_classWalk_t *data = userData;
    if (corto_instanceof(corto_interface_o, o)) {
        if (cpp_visitClass(corto_interface(o), data)) {
            goto error;
        }
    }

    // else if (corto_instanceof(corto_function_o, o)) {
    //     if (cpp_visitFunction(corto_function(o), data)) {
    //         goto error;            
    //     }
    // }
    return 1; /* continue */
error:
ERROR();
    return 0;
}

corto_int16 corto_genMain(g_generator g) {
    cpp_classWalk_t walkData = {g, NULL, NULL, NULL};
    
    cpp_hiddenImplOpen(&walkData);

    if (!g_walkRecursive(g, cpp_walkTypes, &walkData)) {
        goto error;
    }

    cpp_sourceClose(g, walkData.hiddenImpl);

    return 0;
error:
ERROR();
    return -1;
}
