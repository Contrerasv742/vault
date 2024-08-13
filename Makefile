.PHONY: build clean

QT_PATH := $(HOME)/Qt/6.7.2/gcc_64

build:
	mkdir -p build
	cd build && cmake -DCMAKE_PREFIX_PATH=$(QT_PATH) .. && make

clean:
	rm -rf build
