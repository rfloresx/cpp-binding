#include <driver/gen/c/common/common.h>
#include <driver/gen/cpp/common/common.h>
#include <driver/gen/cpp/main/main.h>

#define ERROR() printf("ERROR: %s:%s:%d\n",__FILE__, __func__, __LINE__)

/*
// header 
#include <Test/test.h>

#include <Test/Point.hpp>
#include <Test/Point3D.hpp>
#include <Test/Point4D.hpp>

namespace Test {
    void FOO(Point p);
    void WHAT(int32_t v);
}

// source.h
#include <Test/Test.hpp>

void Test::FOO(Test::Point p) {
    // TODO:
}
void Test::WHAT(int32_t v) {
    // TODO:
}
*/

static int cpp_walkTypes(corto_object o, void* userData) {
    cpp_mainWalk_t *data = userData;

    if (corto_instanceof(corto_interface_o, o)) {
        cpp_include(data->g, data->header, o);
    } 
    return 1; /* continue */
}

static int cpp_walkFunctions(corto_object o, void* userData) {
    cpp_mainWalk_t *data = userData;
    
    if (corto_instanceof(corto_function_o, o) && 
        corto_parentof(o) == g_getCurrent(data->g)) 
    {
        cpp_visitProcedure(data->g, data->header, data->source, corto_function(o), FALSE);
    }
    return 1; /* continue */
}

static int cpp_genMain(g_generator g, g_file file) {
    corto_id mainId;

    cpp_objectId(g, g_getCurrent(g), Cpp_Type, Cpp_ById, mainId); 

    g_fileWrite(file, "int %sMain(int argc, char* argv[])\n", mainId);
    g_fileWrite(file, "{\n");
    g_fileIndent(file);
    
    // TODO 
    g_fileWrite(file, "\n/*TODO*/\n\n");

    g_fileDedent(file);
    g_fileWrite(file, "}\n\n");

}

static int cpp_processInterface(g_generator g) {
    corto_id mainheader;
    cpp_mainWalk_t walkData = {g, NULL, NULL};

    walkData.header = cpp_headerOpen(g, g_getCurrent(g), "hpp");
    walkData.source = cpp_sourceOpen(g, g_getCurrent(g));

    g_fileWrite(walkData.header, "#include <corto/cpp/cpp.hpp>\n");
    g_fileWrite(walkData.header, "#include <%s>\n\n", c_mainheader(g, mainheader));
    
    if (!g_walkRecursive(g, cpp_walkTypes, &walkData)) {
        goto error;
    }

    g_fileWrite(walkData.header, "\n");
    cpp_openScope(walkData.header, g_getCurrent(g));
    g_fileIndent(walkData.header);
    g_fileWrite(walkData.header, "\n");

    if (!g_walkRecursive(g, cpp_walkFunctions, &walkData)) {
        goto error;
    }

    g_fileDedent(walkData.header);
    cpp_closeScope(walkData.header);

    cpp_genMain(g, walkData.source);

    cpp_headerClose(g, walkData.header);
    cpp_sourceClose(g, walkData.source);

    return 0;
 error:
    ERROR();
    return -1;
}

static int cpp_includePackage(g_file header, corto_object import) {
    corto_string str = corto_path(NULL, NULL, import, "/");
    corto_string package = corto_locate(str, NULL, CORTO_LOCATION_FULLNAME);
    if (!package) {
        corto_seterr("project configuration contains unresolved package '%s'", str);
        goto error;
    } else {
        corto_string name = corto_locate(str, NULL, CORTO_LOCATION_NAME);
        g_fileWrite(header, "#include <%s/%s.h>\n", package, name);
        corto_dealloc(name);
        corto_dealloc(package);
    }
    return 0;
error:
    return -1;
}

static int cpp_createCHeader(g_generator g) {
    g_file header = cpp_headerOpen(g, g_getCurrent(g), "h");

    c_includeFrom(g, header, corto_o, "corto.h");

    if (g->imports) {
        corto_iter iter = corto_ll_iter(g->imports);
        while(corto_iter_hasNext(&iter)) {
            corto_object import = corto_iter_next(&iter);
            cpp_includePackage(header, import);
        }
    }
    g_fileWrite(header, "\n");

    c_includeFrom(g, header, g_getCurrent(g), "_load.h");
    c_includeFrom(g, header, g_getCurrent(g), "_project.h");
    c_includeFrom(g, header, g_getCurrent(g), "_type.h");

    cpp_headerClose(g, header);
    return 0;
}

corto_int16 corto_genMain(g_generator g) {
    if (cpp_processInterface(g) || cpp_createCHeader(g) ) {
        goto error;
    }

    return 0;
error:
    return -1;
}