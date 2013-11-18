#include "gtest/gtest.h"
#include "container/growing_pool.h"

TEST(GrowingPoolTest, Validity) {
    base::GrowingPool<int, 3> pool;

    EXPECT_EQ(pool.blocks_count(), 0u);
    pool.new_element();
    EXPECT_EQ(pool.blocks_count(), 1u);
    pool.new_element();
    pool.new_element();
    EXPECT_EQ(pool.blocks_count(), 1u);
    pool.new_element();
    EXPECT_EQ(pool.blocks_count(), 2u);
}
