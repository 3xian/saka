.PHONY : all clean

ROOT_DIR = ../../..
GTEST_DIR = $(ROOT_DIR)/base/gtest
GTEST_INCLUDE = -I$(GTEST_DIR)/include
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h $(GTEST_DIR)/include/gtest/internal/*.h
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)
INCLUDE = $(GTEST_INCLUDE) -I../..

CXX = g++
AR = ar
CXXFLAGS = -O2 -Wall -Werror -std=c++0x
TESTS = common_test
OBJS = time_test.o file_test.o misc_test.o
LIB = -L.. -lpthread -lcommon

all : $(TESTS)
	./common_test

clean :
	rm -f *.a *.o *.txt $(TESTS)

.cc.o :
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $<

common_test : $(OBJS) gtest_main.a
	$(CXX) $(CXXFLAGS) -lpthread $^ $(LIB) -o $@

gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(GTEST_INCLUDE) -I$(GTEST_DIR) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(GTEST_INCLUDE) -I$(GTEST_DIR) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest_main.cc

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^
