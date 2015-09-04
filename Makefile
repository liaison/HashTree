# ============================================================================ #
# @Author:  Lisong Guo <lisong.guo@me.com>
# @Date:    Sep 4, 2015
# ============================================================================ #

OBJ_DIR=obj
BIN_DIR=bin
INCLUDE=include

BOOST_ROOT=/remote/intdeliv/components/osp/Boost/12-0-0-2/include

TARGETS=hashedtree_test
SOURCES=$(shell ls *.cpp)

CC=g++
CFLAGS=-Wall -g -c -I $(INCLUDE) -I $(BOOST_ROOT)
LDFLAGS=


# Replace the postfix of sources
OBJECTS=$(SOURCES:.cpp=.o)


# Entrance rule
all: $(TARGETS)


# Compile the hashedtree_test
hashedtree_test: hashedtree_test.o
	$(CC) $(LDFLAGS) $(OBJ_DIR)/$^ -o $(BIN_DIR)/$@


# Compile each source file
.cpp.o:
	$(CC) $(CFLAGS) $< -o $(OBJ_DIR)/$@


# Clean the object files and targets
clean:
	rm -rf $(OBJ_DIR)/*.o $(BIN_DIR)/* $(OBJ_DIR)/*.dSYM


# Print the source code to screen
view: $(SOURCES)
	less $^




