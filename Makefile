# A single output portable Makefile for
# simple c++ project

OBJ_DIR = obj
BIN_DIR = bin
TARGET = vsray

BIN_TARGET = $(BIN_DIR)/$(TARGET)

INCLUDE_DIR = -I src
DEFINES = -D__DEBUG_BUILD


# CXXFLAGS += -fsanitize=address -Og -g
CXXFLAGS += -O2 -DNDEBUG
CXXFLAGS += -std=c++11
CXXFLAGS += -Wall -Wextra -Wconversion #-Wno-unused-private-field
CXXFLAGS += $(INCLUDE_DIR)
CXXFLAGS += $(shell pkg-config --cflags opencv)
#CXXFLAGS += -fopenmp

LDFLAGS = -lboost_system -lboost_filesystem -lboost_thread-mt $(shell pkg-config --libs opencv)

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
	pq output.png
