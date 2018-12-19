CXX = i686-w64-mingw32-g++

all : testfunction.dll

testfunction.o : testfunction.cpp Makefile
	$(CXX) -O2 -c testfunction.cpp

testfunction.dll : testfunction.o
	$(CXX) -s -O2 -shared -static-libgcc -o $@ $<

clean:
	$(RM) testfunction.o testfunction.dll
