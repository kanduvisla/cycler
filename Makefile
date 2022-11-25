# Compile the ADS code:
ads.o: ads.cpp
	gcc -c ads.cpp

# Compile the Cycler code:
cycler.o: cycler.cpp
	gcc -c cycler.cpp

# Compile the test code, only if test does not exist, or cycler.o is newer than test:
test: cycler.o test.cpp
	gcc -c test.cpp
	gcc -Wall -o test test.o cycler.o
	./test
	make clean
	
# Run the tests:
run_test:
	./test

# Compile the code:
main: cycler.o
	gcc -c main.c
	gcc -o main cycler.o main.o

# Clean up:
clean:
	rm *.o
	rm -f test