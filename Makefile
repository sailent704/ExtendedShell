CC=g++

TARGET_EXEC ?= Executable/eXtended.exe

BUILD_DIR ?= build

SRCS := main.cpp $(wildcard Commands/*.cpp) $(wildcard Helpers/*.cpp) $(wildcard Parser/*.cpp)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

CPPFLAGS ?= -std=gnu++20 -Ofast
LDFLAGS ?= -m32 -static -static-libgcc

$(BUILD_DIR)/$(TARGET_EXEC): mkdirs $(OBJS)
	@echo Linking
	@$(CC) $(LDFLAGS) $(OBJS) -o $@
	@getTime.bat end

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	@echo Building $<
	@$(CC) $(CPPFLAGS) -c $< -o $@


.PHONY: clean run mkdirs

clean:
	del /s /q $(BUILD_DIR)

mkdirs:
	@getTime.bat start
	@echo Making directories if they dont exist yet
	@if not exist build mkdir build
	@if not exist build\\Commands mkdir build\\Commands
	@if not exist build\\Helpers mkdir build\\Helpers
	@if not exist build\\Parser mkdir build\\Parser
	@if not exist build\\Executable mkdir build\\Executable

make: $(BUILD_DIR)/$(TARGET_EXEC)

run:
	@echo Running
	$(BUILD_DIR)/$(TARGET_EXEC)