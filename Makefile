#
# $File: Makefile
# $Date: Thu Jun 27 02:56:32 2013 +0800
#
# A single output portable Makefile for
# simple c++ project

OBJ_DIR = obj
BIN_DIR = bin
TARGET = vsray
HEADER = src/core/vsray.hpp

BIN_TARGET = $(BIN_DIR)/$(TARGET)

INCLUDE_DIR = -I src
DEFINES = -D__DEBUG_BUILD


CXXFLAGS += -O0 -g -msse2
CXXFLAGS += -std=c++11
CXXFLAGS += -Wall -Wextra -Wconversion
CXXFLAGS += $(INCLUDE_DIR)
#CXXFLAGS += $(shell pkg-config --libs --cflags opencv)
#CXXFLAGS += -fopenmp

LDFLAGS = -lboost_system

CXX = g++
CXXSOURCES = $(shell find src/ -name "*.cpp")
OBJS = $(addprefix $(OBJ_DIR)/,$(CXXSOURCES:.cpp=.o))
DEPFILES = $(OBJS:.o=.d)

.PHONY: all clean run rebuild gdb

all: $(BIN_TARGET)


$(OBJ_DIR)/%.o: %.cpp
	@echo "[cc] $< ..."
	@$(CXX) -c $< $(CXXFLAGS) -o $@

$(OBJ_DIR)/%.d: %.cpp
	@mkdir -pv $(dir $@)
	@echo "[dep] $< ..."
	@$(CXX) $(INCLUDE_DIR) $(CXXFLAGS) -MM -MT "$(OBJ_DIR)/$(<:.cpp=.o) $(OBJ_DIR)/$(<:.cpp=.d)" "$<" > "$@"

sinclude $(DEPFILES)

$(BIN_TARGET): $(OBJS)
	@echo "[link] $< ..."
	@mkdir -p $(BIN_DIR)
	@$(CXX) $(OBJS) -o $@ $(LDFLAGS) $(CXXFLAGS)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

run: $(BIN_TARGET)
	./$(BIN_TARGET)

rebuild:
	+@make clean 
	+@make

gdb: $(BIN_TARGET)
	gdb ./$(BIN_TARGET)

show: 
	geeqie output.png
