.DEFAULT_GOAL := build

.PHONY: build
build:
	mkdir -p build
	cd build; cmake -DCMAKE_BUILD_TYPE=Release ..; make
