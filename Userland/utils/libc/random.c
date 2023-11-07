#include <random.h>
#include <syscalls.h>

uint64_t rand(int seed, uint64_t max) {
    return random(seed) % max;
}