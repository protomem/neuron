
.PHONY: configure
configure:
	premake5 gmake2 --file=premake5.lua
	cd build && compiledb -n make


.PHONY: build
build:
	cd build && make neuron


.PHONY: tests
tests:
	cd build && make tests
	if [ -d build/Debug ]; \
		then ./build/Debug/tests; \
		else ./tests/Release/tests; \
	fi


.PHONY: clean
clean:
	cd build && make clean

