#include "hash.h"

namespace base {

uint64_t bkdr_hash(const std::string& str) {
    uint64_t key = 0;
    uint64_t seed = 131;
    for (size_t i = 0; i < str.size(); ++i) {
        key = key * seed + (uint64_t)str[i];
    }
    return key;
}

}  // namespace base
