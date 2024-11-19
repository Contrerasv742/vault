CPP		:= $(wildcard src/*.cpp)
HEADERS := $(wildcard src/*.h)
QT_PATH	:= $(HOME)/Qt/6.7.2/gcc_64
FORMAT	:= clang-format
FLAGS	:= -style=file

.PHONY: format clean

build:
	mkdir -p build && cd build/ && cmake -DCMAKE_PREFIX_PATH=$(QT_PATH) .. && make -j`nproc`

format:
	$(FORMAT) -i $(HEADERS) $(CPP)
	# $(FORMAT) $(FLAGS) -i $(HEADERS) $(CPP)

lines:
	@ echo "Lines of Code:"
	@ cat src/* | wc -l

clean:
	rm -rf build
