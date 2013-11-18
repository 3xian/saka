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
TESTS = container_test
LIB = -L.. -lpthread

all : $(TESTS)
	./container_test

clean :
	rm -f *.a *.o *.trie $(TESTS)

.cc.o :
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $<

#container_test : trie_test.o growing_pool_test.o dummy_map_test.o gtest_main.a
container_test : growing_pool_test.o dummy_map_test.o gtest_main.a
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIB)

gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(GTEST_INCLUDE) -I$(GTEST_DIR) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(GTEST_INCLUDE) -I$(GTEST_DIR) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest_main.cc

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^
