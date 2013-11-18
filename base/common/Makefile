.PHONY : all clean test

ROOT_DIR = ../..
BASE_DIR = $(ROOT_DIR)/base

CXX = g++
AR = ar
CXXFLAGS = -O2 -Wall -Werror
OBJS = file.o
TARGET_LIBS = libcommon.a
INCLUDE = -I$(BASE_DIR)

all : $(TARGET_LIBS)

clean :
	make clean -C test
	rm -f *.a *.o

test :
	make -C test

$(TARGET_LIBS) : $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

.cc.o :
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $<
