#include <iostream>
#include "gtest/gtest.h"
#include "common/time.h"

TEST(TimeTest, Construct) {
    using namespace std;
    base::Time t;
    usleep(500000);
    long diff = t.get_time_passed();
    cout << diff << endl;
    EXPECT_TRUE(abs(t.get_time_passed() - 500) <= 1);
}

TEST(TimeTest, Start) {
    using namespace std;
    base::Time t;
    usleep(50000);
    long diff = t.get_time_passed();
    cout << diff << endl;
    EXPECT_TRUE(abs(t.get_time_passed() - 50) <= 1);

    t.start();
    usleep(123000);
    diff = t.get_time_passed();
    cout << diff << endl;
    EXPECT_TRUE(abs(t.get_time_passed() - 123) <= 1);
}
