
#include <test.hpp>

namespace test {

}
int testMain(int argc, char* argv[]) {
/* $begin(main) */
    int result = 0;
    test_Runner runner = test_RunnerCreate("driver/gen/cpp/composite", argv[0], (argc > 1) ? argv[1] : NULL);
    if (!runner) return -1;
    if (corto_ll_size(runner->failures)) {
        result = -1;
    }
    corto_delete(runner);
    return result;
/* $end */
}


