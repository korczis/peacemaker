all: 
	mkdir build && cd build && cmake ../ && make && cd ../

test:
	cd build && ls -la && cd .. /
