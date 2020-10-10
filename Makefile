CC=g++

TARGET_EXEC ?= Executable/eXtended.exe

BUILD_DIR ?= build

SRCS := main.cpp $(wildcard Commands/*.cpp) $(wildcard Helpers/*.cpp) $(wildcard Parser/*.cpp)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

CPPFLAGS ?= -std=gnu++20 -static -static-libgcc

$(BUILD_DIR)/$(TARGET_EXEC): mkdirs $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@


.PHONY: clean

clean:
	del /s /q $(BUILD_DIR)

mkdirs:
	if not exist build mkdir build
	if not exist build\\Commands mkdir build\\Commands
	if not exist build\\Helpers mkdir build\\Helpers
	if not exist build\\Parser mkdir build\\Parser
	if not exist build\\Executable mkdir build\\Executable

run:
	$(BUILD_DIR)/$(TARGET_EXEC)