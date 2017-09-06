#ifndef DRIVER_GEN_CPP_API_CLASS_H
#define DRIVER_GEN_CPP_API_CLASS_H

#include <corto/corto.h>


typedef struct cpp_classWalk_t {
    g_generator g;
    g_file header;  //type.h
    g_file source;  //type.cpp
} cpp_classWalk_t;


#endif 