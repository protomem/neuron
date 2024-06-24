
.PHONY: configure
configure:
	premake5 gmake2 --file=premake5.lua
	cd build && compiledb -n make


.PHONY: build
build:
	cd build && make


.PHONY: clean
clean:
	cd build && make clean
