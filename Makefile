# Compile the ADS code:
ads.o: src/ads.cpp
	gcc -c src/ads.cpp

# Compile the Cycler code:
cycler.o: src/cycler.cpp
	gcc -c src/cycler.cpp

# Compile the test code, only if test does not exist, or cycler.o is newer than test:
test: ads.o cycler.o tests/test.cpp
	gcc -c tests/test.cpp
	gcc -Wall -o test test.o ads.o cycler.o
	./test
	make clean
	
# Compile the code:
main: cycler.o
	gcc -c main.c
	gcc -o main cycler.o main.o

# Clean up:
clean:
	rm *.o
	rm -f test