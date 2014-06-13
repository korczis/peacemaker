all: 
	mkdir -p build && cd build && cmake .. && make && cd ../

clean:
	rm -rf build/CMakeFiles build/CMakeCache.txt build/cmake_install.cmake build/Makefile build/apps build/bin build/lib build/tests

test:
	echo "Testing"

	cd build && ls -la apps bin lib && cd .. / && echo "" && build/bin/peacemaker-test
