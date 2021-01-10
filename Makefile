CC=g++

TARGET_EXEC ?= Executable/eXtended.exe
BUILD_DIR ?= out

SRCS := $(wildcard *.cpp) $(wildcard Commands/*.cpp) $(wildcard Helpers/*.cpp) $(wildcard Parser/*.cpp)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

CPPFLAGS ?= -std=gnu++20 -Ofast
LDFLAGS ?= -m32 -static -static-libgcc

# Linking
$(BUILD_DIR)/$(TARGET_EXEC): $(BUILD_DIR) $(OBJS)
	@echo Linking
	@$(CC) $(LDFLAGS) $(OBJS) -o $@

# C++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	@echo Building $<
	@$(CC) $(CPPFLAGS) -c $< -o $@


.PHONY: clean run make
clean:
	@echo Cleaning
	@rmdir /s /q $(BUILD_DIR)

$(BUILD_DIR):
	@echo Making directories
	@if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
	@if not exist $(BUILD_DIR)\\Commands mkdir $(BUILD_DIR)\\Commands
	@if not exist $(BUILD_DIR)\\Helpers mkdir $(BUILD_DIR)\\Helpers
	@if not exist $(BUILD_DIR)\\Parser mkdir $(BUILD_DIR)\\Parser
	@if not exist $(BUILD_DIR)\\Executable mkdir $(BUILD_DIR)\\Executable

make: $(BUILD_DIR)/$(TARGET_EXEC)

run:
	@echo Running
	$(BUILD_DIR)/$(TARGET_EXEC)
