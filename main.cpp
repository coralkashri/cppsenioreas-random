#include "my_random.h"

int main() {
    my_random<std::normal_distribution<>> mrand(10, 50);
    mrand.distribution_test();
    return 0;
}