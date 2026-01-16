#include <cstdio>
#include "core.hpp"

int main() {
    int r = core::add(2, 3);
    std::printf("smoke test result = %d\n", r);
    return r == 5 ? 0 : 1;
}
