.PHONY : all clean

ROOT_DIR = ../../..
BASE_DIR = $(ROOT_DIR)/base
GTEST_DIR = $(ROOT_DIR)/base/gtest
GTEST_INCLUDE = -I$(GTEST_DIR)/include
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h $(GTEST_DIR)/include/gtest/internal/*.h
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)
INCLUDE = $(GTEST_INCLUDE) -I$(BASE_DIR)

CXX = g++
AR = ar
CXXFLAGS = -O2 -Wall -Werror -std=c++0x
TESTS = string_test
LIB = -L.. -lpthread -lstring

all : $(TESTS)
	./string_test

clean :
	rm -f *.a *.o $(TESTS)

.cc.o :
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $<

string_test : hash_test.o string_util_test.o  gtest_main.a
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIB)

gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(GTEST_INCLUDE) -I$(GTEST_DIR) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(GTEST_INCLUDE) -I$(GTEST_DIR) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest_main.cc

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^
