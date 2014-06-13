all: 
	mkdir -p build && cd build && cmake .. && make && cd ../

clean:
	rm -rf build/CMakeFiles build/CMakeCache.txt

test:
	echo "Testing"

