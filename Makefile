SOURCES         := $(shell find src -name '*.cpp')
HEADERS         := $(shell find src -name '*.h' -o -name '*.hpp')

CMAKE           := cmake
BUILD_DIR       := build
QT_PATH         := $(HOME)/Qt/6.7.2/gcc_64
CMAKE_FLAGS     := -DCMAKE_PREFIX_PATH=$(QT_PATH)
NPROC           := $(shell nproc)

FORMAT          := clang-format
FLAGS           := -style=file

.DEFAULT_GOAL   := all

.PHONY: all cmake_build format clean

# Main targets
all: format cmake_build

# Cmake build director
cmake_build:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && $(CMAKE) $(CMAKE_FLAGS) .. && make -j$(NPROC)

format:
	@echo "Formatting source files"
	$(FORMAT) -i $(SOURCES) $(HEADERS)
	@echo "Formatting complete"

# TODO: Check for formatting

clean:
	rm -rf $(BUILD_DIR)
