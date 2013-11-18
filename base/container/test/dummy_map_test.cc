#include <string>
#include "gtest/gtest.h"
#include "container/dummy_map.h"

TEST(DummyMapTest, Validity1) {
    base::DummyMap<std::string, int> m;

	m["apple"] = 1;
	m["pear"] = 2;

    EXPECT_EQ(m["apple"], 1);
    EXPECT_EQ(m["pear"], 2);
}

TEST(DummyMapTest, Validity2) {
    base::DummyMap<int, std::string> m;

	for (int i = 0; i < 10000; ++i) {
		m[i * 10] = "good";
	}

    EXPECT_TRUE(m.find(1000 + 1) == m.end());
    EXPECT_EQ(m.find(1000 - 1), m.end());
    EXPECT_NE(m.find(1000), m.end());
}
