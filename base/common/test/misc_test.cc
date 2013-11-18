#include <iostream>
#include "gtest/gtest.h"
#include "common/misc.h"

TEST(BasicConvertTest, Validity) {
    int x = base::basic_convert<std::string, int>("0123");
    ASSERT_EQ(x, 123);
}
