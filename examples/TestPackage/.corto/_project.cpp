/* _project.cpp
 *
 * This file contains the project entry function. Here, we
 * start/stop corto and load all dependencies, before and after
 * invoking the main function of your project.
 */

#include <Test/Test.hpp>
#include <Test/_project.h>

int TestMain(int argc, char* argv[]);

int Test_load(void);

#ifdef __cplusplus
extern "C"
#endif
TEST_EXPORT int cortomain(int argc, char* argv[]) {
    if (corto_load("/corto/cpp", 0, NULL)) return -1;
    if (Test_load()) return -1;
    if (TestMain(argc, argv)) return -1;
    return 0;
}

