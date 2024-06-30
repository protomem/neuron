
.DEFAULT_GOAL := help


## help: print this help message
.PHONY: help
help:
	@echo 'Usage:'
	@sed -n 's/^##//p' ${MAKEFILE_LIST} | column -t -s ':' |  sed -e 's/^/ /'


## configure: generate the makefile and compile commands file
.PHONY: configure
configure:
	premake5 gmake2 --file=premake5.lua
	cd build && compiledb -n make


## build: compile the project
.PHONY: build
build:
	cd build && make neuron


## tests: run the unit tests
.PHONY: tests
tests: build
	cd build && make tests
	if [ -d build/Debug ]; \
		then ./build/Debug/tests; \
		else ./tests/Release/tests; \
	fi


## clean: remove all target files
.PHONY: clean
clean:
	cd build && make clean

