# Compile the Cycler code:
cycler.o: cycler.c
	gcc -c cycler.c

# Compile the test code, only if test does not exist, or cycler.o is newer than test:
test: cycler.o test.c
	gcc -c test.c
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