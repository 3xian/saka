#include <string>
#include "gtest/gtest.h"
#include "string/string_util.h"

TEST(TrimFrontTest, Validity) {
    std::string s1 = " aa  bbb ";
    EXPECT_EQ(base::trim_front(s1), "aa  bbb ");

    std::string s2 = "  aa  bbb ";
    EXPECT_EQ(base::trim_front(s2), "aa  bbb ");

    std::string s3 = "\t  aa  bbb ";
    EXPECT_EQ(base::trim_front(s3), "aa  bbb ");

    std::string s4 = "\r\naa  bbb ";
    EXPECT_EQ(base::trim_front(s4), "aa  bbb ");

    std::string s5 = "   ";
    EXPECT_EQ(base::trim_front(s5), "");

    std::string s6 = "";
    EXPECT_EQ(base::trim_front(s6), "");

    std::string s7 = "aa  bbb ";
    EXPECT_EQ(base::trim_front(s7), "aa  bbb ");
}

TEST(TrimFrontTest, Performance) {
    std::string s1 = std::string(1000000, ' ') + "a";
    EXPECT_EQ(base::trim_front(s1), "a");

    std::string s2 = std::string(1000000, 'a') + "a";
    EXPECT_EQ(base::trim_front(s2), s2);
}

TEST(TrimBackTest, Validity) {
    std::string s1 = " aa  bbb\t\r\n ";
    EXPECT_EQ(base::trim_back(s1), " aa  bbb");

    std::string s2 = "   ";
    EXPECT_EQ(base::trim_back(s2), "");

    std::string s3 = "";
    EXPECT_EQ(base::trim_back(s3), "");
}

TEST(TrimTest, Validity) {
    std::string s1 = " aa  bbb ";
    EXPECT_EQ(base::trim(s1), "aa  bbb");

    std::string s2 = "  aa  bbb";
    EXPECT_EQ(base::trim(s2), "aa  bbb");

    std::string s3 = "\t  aa  bbb \n ";
    EXPECT_EQ(base::trim(s3), "aa  bbb");

    std::string s4 = "\r\naa  bbb \r\r\r";
    EXPECT_EQ(base::trim(s4), "aa  bbb");

    std::string s5 = "   ";
    EXPECT_EQ(base::trim(s5), "");

    std::string s6 = "";
    EXPECT_EQ(base::trim(s6), "");

    std::string s7 = "aa  bbb";
    EXPECT_EQ(base::trim(s7), "aa  bbb");
}

TEST(TrimTest, Performance) {
    std::string s1 = std::string(1000000, ' ') + "a";
    EXPECT_EQ(base::trim(s1), "a");

    std::string s2 = std::string(1000000, 'a') + "a";
    EXPECT_EQ(base::trim(s2), s2);

    std::string s3 = std::string(1000000, ' ') + "bb" + std::string(1000000, '\n');
    EXPECT_EQ(base::trim(s3), "bb");
}

TEST(Utf8ToUint32Test, Validity) {
    std::string s1 = "吃饭啦";
    EXPECT_EQ(s1.size(), 9u);
    std::vector<uint32_t> v;
    EXPECT_TRUE(base::utf8_to_uint32(s1, &v));
    EXPECT_EQ(v.size(), 3u);

    std::string s2 = "吃饭啦88";
    EXPECT_EQ(s2.size(), 11u);
    EXPECT_TRUE(base::utf8_to_uint32(s2, &v));
    EXPECT_EQ(v.size(), 5u);

    std::string s3 = "志们";
    std::string s4 = "北马";
    std::vector<uint32_t> v3;
    std::vector<uint32_t> v4;
    EXPECT_EQ(s3.size(), 6u);
    EXPECT_EQ(s4.size(), 6u);
    EXPECT_TRUE(base::utf8_to_uint32(s3, &v3));
    EXPECT_TRUE(base::utf8_to_uint32(s4, &v4));
    EXPECT_NE(v3, v4);
}
