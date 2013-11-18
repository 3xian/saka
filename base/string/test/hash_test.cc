#include <string>
#include "gtest/gtest.h"
#include "string/hash.h"

TEST(BkdrHashTest, Validity) {
    EXPECT_EQ(base::bkdr_hash(""), 0ULL);

    uint64_t abc_key = (uint64_t)'a'*131*131 + (uint64_t)'b'*131 + 'c';
    EXPECT_EQ(base::bkdr_hash("abc"), abc_key);
}
