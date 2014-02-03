all:
	cd src && $(MAKE) && cp libcontainers.so ../lib && cp test ../bin

clean:
	rm -rf lib/* bin/* src/*.o src/*.so src/test
