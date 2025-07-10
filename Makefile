# Compiler and compiler flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall

# Source files
SRCS = main.cpp product.cpp

# Default settings for Linux/macOS
TARGET = stock_management
RM = rm -f
RUN = ./$(TARGET)

# --- OS-specific overrides ---
# Check if the OS is Windows_NT (the name for Windows)
ifeq ($(OS), Windows_NT)
    TARGET = stock_management.exe
    RM = del /F /Q
    RUN = $(TARGET)
endif

# --- Build Rules ---

# The .PHONY rule tells make that 'all', 'run', and 'clean' are not files
.PHONY: all run clean

# Default target: builds the executable
all: $(TARGET)

# Rule to link the object files into the final executable
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

# Rule to run the executable
run: all
	@echo --- Running $(TARGET) ---
	$(RUN)

# Rule to remove the compiled executable and other generated files
clean:
	@echo --- Cleaning up project files ---
	$(RM) $(TARGET)