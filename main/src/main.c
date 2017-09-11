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
    printf("FOOO\n");
    if (corto_instanceof(corto_function_o, o) && 
        corto_parentof(o) == g_getCurrent(data->g)) 
    {
        cpp_visitProcedure(data->g, data->header, data->source, corto_function(o), FALSE);
    }
    return 1; /* continue */
}

corto_int16 corto_genMain(g_generator g) {
    corto_id mainheader;
    cpp_mainWalk_t walkData = {g, NULL, NULL};

    walkData.header = cpp_headerOpen(g, g_getCurrent(g));
    walkData.source = cpp_sourceOpen(g, g_getCurrent(g));

    g_fileWrite(walkData.header, "#include <%s>\n\n", c_mainheader(g, mainheader));
    
    if (!g_walkRecursive(g, cpp_walkTypes, &walkData)) {
        goto error;
    }

    g_fileWrite(walkData.header, "\n");
    cpp_openScope(walkData.header, g_getCurrent(g));
    g_fileWrite(walkData.header, "\n");

    if (!g_walkRecursive(g, cpp_walkFunctions, &walkData)) {

    }

    cpp_closeScope(walkData.header);

    cpp_headerClose(g, walkData.header);
    cpp_sourceClose(g, walkData.source);

    return 0;
error:
    ERROR();
    return -1;
}