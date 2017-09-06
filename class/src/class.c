#include <driver/gen/c/common/common.h>
#include <driver/gen/cpp/common/common.h>
#include <driver/gen/cpp/class/class.h>

/*
class Point : public ::corto::Object 
{
public:
    typedef ::corto::Object Base;

    int32_t x() const;
    void x(int32_t x);

    int32_t y() const;
    void y(int32_t y);

    Point();
    Point(const Point &other);
    Point(Point &&other);
    Point(types::Point *obj);
    Point(types::Point *ptr, types::Type type);
    Point(types::Point &val);
    
    virtual ~Point();

    Point& operator=(const Point &other);
    Point& operator=(Point &&other);
    Point& operator=(types::Point *obj);
    Point& operator=(types::Point &val);
};
*/
#define TRACE(msg) printf("%s:%d\n", msg, __LINE__)
#define ERROR() printf("ERROR: %s:%d\n", __func__, __LINE__)

static corto_int16 cpp_hiddenImplOpen(cpp_classWalk_t *data) {
    data->hiddenImpl = g_hiddenFileOpen(data->g, "_api.cpp", corto_idof(g_getCurrent(data->g)));
    if (!data->hiddenImpl) {
        goto error;
    }

    corto_id mainheader;
    g_fileWrite(data->hiddenImpl,"#include <%s>\n", cpp_mainheader(data->g, mainheader));
    cpp_openScope(data->hiddenImpl, g_getCurrent(data->g));
    g_fileWrite(data->hiddenImpl, "\n");
    return 0;
error:
    ERROR();
    return -1;
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

    cpp_typeFullId(data->g, t, Cpp_Class, Cpp_ById, memberType);
    cpp_typeFullId(data->g, corto_parentof(m), Cpp_Class, Cpp_ById, classId);
    cpp_typeFullId(data->g, corto_parentof(m), Cpp_CType, Cpp_ById, cClassId);
    g_oid(data->g, m, memberId);

    /* Write header 
        {type} {name}() const;
        void {name}({type} value);
    */
    g_fileWrite(data->header, "%s %s() const;\n", memberType, memberId);
    g_fileWrite(data->header, "void %s(%s value);\n", memberId, memberType);

    /* Write implementation 
        {type} {Class}::{name}() const 
        {
            return {type}( ({c_type})this->ptr()->{name});
        }
        void {Class}::{name}({type} value) 
        {
            {type}(({c_type})this->ptr()->{name}) = value;
        }
    */
    g_fileWrite(data->hiddenImpl, "%s %s::%s() const\n", memberType, classId, memberId);
    g_fileWrite(data->hiddenImpl, "{\n");
    g_fileIndent(data->hiddenImpl);
    g_fileWrite(data->hiddenImpl, "return %s{((%s)this->ptr())->%s};\n", memberType, cClassId, memberId);
    g_fileDedent(data->hiddenImpl);
    g_fileWrite(data->hiddenImpl, "}\n");

    g_fileWrite(data->hiddenImpl, "void %s::%s(%s value)\n", classId, memberId, memberType);
    g_fileWrite(data->hiddenImpl, "{\n");
    g_fileIndent(data->hiddenImpl);
    g_fileWrite(data->hiddenImpl, "%s{((%s)this->ptr())->%s} = value;\n",memberType, cClassId, memberId);
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
static corto_int16 cpp_walkProcedureParam(corto_function f, g_file file, corto_bool c, cpp_classWalk_t *data) {
    corto_id paramTypeId;
    corto_int32 offset = 0;
    corto_int32 i = 0;
    corto_int32 length = f->parameters.length;
    if (c && c_procedureHasThis(f)) {
        length++; i++;
        offset = -1;
        
        cpp_typeFullId(data->g, corto_parentof(f), Cpp_CType, Cpp_ByRef, paramTypeId);
        g_fileWrite(file, "%s _this", paramTypeId);
    }

    if (length > 3) {
        g_fileIndent(data->header);
    }

    for (; i < length; i ++) {
        corto_parameter *p = &f->parameters.buffer[i + offset];
        if (i) {
            g_fileWrite(file, ", ");
            if (length > 3) {
                g_fileWrite(file, "\n");
            }
        }
        cpp_typeFullId(data->g, p->type, c ? Cpp_CType : Cpp_Class, c ? Cpp_ByRef : Cpp_ById, paramTypeId);
        g_fileWrite(file, "%s %s", paramTypeId, p->name);
    }

    if (length > 3) {
        g_fileDedent(data->header);
    }
    return 0;
}

/*
extern "C" {return} {c_func_name} ({cType} _this, {cType} arg0) {
    {Class} _instance(_this);
    {Class} _arg0(arg0);
    {Class} _arg1(arg1);
    ...
    {Class} _argn(argn);
    {result} = _instance.add(_arg0, _arg1, ..., _argn);
    {declare c_result}
    {copy result to c_result}
    {return c_result}
}
*/
static corto_int16 cpp_methodProxy(corto_function f, cpp_classWalk_t *data) {
    corto_id proxyId, methodId, cReturnId, cppReturnId;
    corto_id cppType;
    corto_int32 i = 0;
    corto_int32 parametersLength = f->parameters.length;
    corto_bool hasThis = c_procedureHasThis(f);
    corto_bool returnsValue = !cpp_isVoid(f->returnType);


    proxyId[0] = '_';
    corto_path(proxyId + 1, g_getCurrent(data->g), f, "_");
    corto_signatureName(proxyId, proxyId);

    strcpy(methodId, corto_idof(f));
    corto_signatureName(methodId, methodId);

    cpp_typeFullId(data->g, f->returnType, Cpp_CType, f->returnsReference ? Cpp_ByRef : Cpp_ByVal, cReturnId);
    cpp_typeFullId(data->g, f->returnType, Cpp_Class, Cpp_ById, cppReturnId);

    g_fileWrite(data->hiddenImpl, "extern \"C\" %s %s(", cReturnId, proxyId);
    
    cpp_walkProcedureParam(f, data->hiddenImpl, TRUE, data);
    g_fileWrite(data->hiddenImpl, ")\n");
    g_fileWrite(data->hiddenImpl, "{\n");
    g_fileIndent(data->hiddenImpl);

    /* Wrap C parameters in C++ types */
    if (hasThis) {
        cpp_typeFullId(data->g, corto_parentof(f), Cpp_Class, Cpp_ById, cppType);
        g_fileWrite(data->hiddenImpl, "%s _instance(_this);\n", cppType);
    }

    for (i = 0; i < parametersLength; i++) {
        corto_parameter *p = &f->parameters.buffer[i];
        cpp_typeFullId(data->g, p->type, Cpp_Class, Cpp_ById, cppType);
        g_fileWrite(data->hiddenImpl, "%s _%s(%s);\n", cppType, p->name, p->name);
    }

    if (returnsValue) {
        g_fileWrite(data->hiddenImpl, "%s result = ", cppReturnId);
    }

    if (hasThis) {
        g_fileWrite(data->hiddenImpl, "_instance.");
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
                "result",
                buffer
            )
        );
    }

    g_fileDedent(data->hiddenImpl);
    g_fileWrite(data->hiddenImpl, "}\n");
    g_fileWrite(data->hiddenImpl, "\n");


    return 0;
}

static corto_int16 cpp_visitProcedure(corto_function f, cpp_classWalk_t *data) {
    corto_id resultId, methodId, methodFullId;

    cpp_typeFullId(data->g, f->returnType, Cpp_Class, Cpp_ById, resultId);
    corto_signatureName(corto_idof(f), methodId);
    cpp_typeFullId(data->g, corto_parentof(f), Cpp_Class, Cpp_ById, methodFullId);
    strcat(methodFullId, "::");
    strcat(methodFullId, methodId);

    g_fileWrite(data->header, "%s %s(", resultId, methodId);
    if (cpp_walkProcedureParam(f, data->header, FALSE, data)) {
        goto error;
    }
    g_fileWrite(data->header, ");\n");

    char *snippetId;
    if (f->overloaded) {
        snippetId = corto_idof(f);
    } else {
        snippetId = methodId;
    }

    g_fileWrite(data->source, "%s %s(", resultId, methodFullId);
    if (cpp_walkProcedureParam(f, data->source, FALSE, data)) {
        goto error;
    }

    g_fileWrite(data->source, ")\n");
    g_fileWrite(data->source, "{\n");

    g_fileIndent(data->source);
    corto_string snippet;
    if ((snippet = g_fileLookupSnippet(data->source, snippetId))) {
        g_fileWrite(data->source, "%s", snippet);
    } else {
        g_fileWrite(data->source, "/* Insert Implementation*/\n\n");
    }
    g_fileDedent(data->source);

    g_fileWrite(data->source, "}\n");

    if (cpp_methodProxy(f, data)) {
        goto error;
    }

    return 0;
error: ERROR();
    return -1;
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

            if (cpp_visitProcedure(child, data)) {
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
    


/* Generate code for a corto interface type (interface, class, struct, procedure) */
static corto_int16 cpp_visitClass(corto_interface type, cpp_classWalk_t *data) {
    
    corto_id class, cType, baseClass, baseCType;
    corto_id mainheader;
    cpp_typeId(data->g, type, Cpp_Class, Cpp_ById, class);
    cpp_mainheader(data->g, mainheader);
    if (!type->base) {
        strcpy(baseClass, "::corto::Object");
        strcpy(baseCType, "corto_object");
    } else {
        cpp_typeFullId(data->g, type->base, Cpp_Class, Cpp_ById, baseClass);
        cpp_typeFullId(data->g, type->base, Cpp_CType, Cpp_ById, baseCType);
    }
    data->header = cpp_headerOpen(data->g, type);
    if (!data->header) {
        goto error;
    }
    /*
    #include <{mainheader}>

    namespace {ScopeName} {
        class {class} : public {baseClass} 
        {
        public:
            // Getters/setters
            {Members getters/setters}

            // Methods
            {walk procedures}
            
            // operators 
            {class operators}

            // constructs 
            {class constructs}
            ~{class}();

        }
    }
    */
    g_fileWrite(data->header, "#include <%s>\n", mainheader);
    g_fileWrite(data->header, "\n");

    cpp_openScope(data->header, g_getCurrent(data->g));
    g_fileWrite(data->header, "\n");

    g_fileWrite(data->header, "// Implementation of corto type %s\n", corto_fullpath(NULL, type));
    g_fileWrite(data->header, "class %s : public %s", class, baseClass);
    g_fileWrite(data->header, "{\n");
    g_fileWrite(data->header, "public:\n");
    g_fileIndent(data->header);

    g_fileWrite(data->header, "// Getters/setters\n");
    if (cpp_walkMembers(type, data)) {
        goto error;
    }
    g_fileWrite(data->header, "\n");

    g_fileWrite(data->header, "// Methods\n");
    if (cpp_walkProcedures(type, data)) {
        goto error;
    }
    g_fileWrite(data->header, "\n");

    g_fileWrite(data->header, "// Operators\n");
    // if (cpp_classOperators(type, data)) {
    //     goto error;
    // }
    g_fileWrite(data->header, "\n");
    g_fileWrite(data->header, "// Constructs\n");
    // if (cpp_classConstructs(type, data)) {
    //     goto error;
    // }
    g_fileWrite(data->header, "\n");
    return 0;
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
    return 1; /* continue */
error:
ERROR();
    return 0;
}

corto_int16 corto_genMain(g_generator g) {
    cpp_classWalk_t walkData = {g, NULL, NULL, NULL};
    if (cpp_hiddenImplOpen(&walkData)) {
        goto error;
    }
    if (!g_walkRecursive(g, cpp_walkTypes, &walkData)) {
        goto error;
    }
    
    cpp_sourceClose(g, walkData.hiddenImpl);
    return 0;
error:
ERROR();
    return -1;
}
