.PHONY : all clean test

ROOT_DIR = ../..
BASE_DIR = $(ROOT_DIR)/base

CXX = g++
AR = ar
CXXFLAGS = -O2 -Wall -Werror -std=c++0x
OBJS = string_util.o encoding_converter.o hash.o
TARGET_LIBS = libstring.a
INCLUDE = -I$(BASE_DIR)

all : $(TARGET_LIBS)

clean :
	make clean -C test
	rm -rf *.o *.a

test :
	make -C test

$(TARGET_LIBS) : $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

.cc.o :
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $<
