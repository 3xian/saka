#include <algorithm>
#include <iostream>
#include <thread>
#include "gtest/gtest.h"
#include "common/file.h"

TEST(FileTest, Write) {
    std::string context = " aNy otHeR here ?? .. ";
    EXPECT_TRUE(base::write_string_to_file(context, "file_test.txt"));
}

TEST(FileTest, Read) {
    std::string context = " aNy otHeR here ?? .. ";
    std::string read_context;
    EXPECT_FALSE(base::read_file_to_string("wrong_name.txt", &read_context));
    EXPECT_TRUE(base::read_file_to_string("file_test.txt", &read_context));
    EXPECT_EQ(context, read_context);
}

void thread_write(base::FileAppender* fa) {
    std::string buf(30, 'a' + rand() % 26);
    for (int i = 0; i < 50; ++i) {
        fa->write(buf + '\n');
    }
}

TEST(FileTest, FileAppend) {
    base::FileAppender fa;
    std::string file_name = "file_append_test.txt";

    remove(file_name.c_str());
    fa.open("file_append_test.txt");

    std::vector<std::thread> threads;
    for(int i = 0; i < 5; ++i){
        threads.push_back(std::thread(thread_write, &fa));
    }
    for(int i = 0; i < 5; ++i){
        threads[i].join();
    }
    fa.close();

    fa.open("file_append_test.txt");
    fa.write("The End!\n");
    fa.write("The End!\n");
    fa.close();
    
    std::string buf;
    base::read_file_to_string(file_name, &buf);
    ASSERT_EQ(std::count(buf.begin(), buf.end(), '\n'), 5 * 50 + 2);
    remove(file_name.c_str());
}
