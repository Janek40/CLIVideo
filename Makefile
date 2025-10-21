# ==============================
# Project Configuration
# ==============================
TARGET_DIR := bin
TARGET := $(TARGET_DIR)/clivideo
SRC_DIR := src
BUILD_DIR := build
CONFIG_DIR := config

CXX := g++
CXXFLAGS := -Wall -Wextra -O2 -std=c++17 -Isrc/HPP

# ==============================
# Automatic source/object discovery
# ==============================
SRC_FILES := $(shell find $(SRC_DIR) -name '*.cpp')
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC_FILES))

# ==============================
# Build Rules
# ==============================
.PHONY: all clean copy-config

all: $(TARGET) copy-config

# Link final binary
$(TARGET): $(OBJ_FILES)
	@mkdir -p $(dir $@)
	$(CXX) $(OBJ_FILES) -o $@

# Compile source files to object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR) $(TARGET)


copy-config:
	@if [ -d "$(CONFIG_DIR)" ]; then \
		echo "📁 Copying config files to $(TARGET_DIR)..."; \
		mkdir -p $(TARGET_DIR); \
		cp -r $(CONFIG_DIR)/* $(TARGET_DIR)/; \
	fi
