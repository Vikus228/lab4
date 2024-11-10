.PHONY: build run test clear


build: clear
	mkdir -p build
	git submodule init
	git submodule update
	cd build && cmake .. && make lab3 && make lab3_test

run: 
	./build/lab3

test:
	./build/lab3_test

clear:
	@rm -rf ./build/