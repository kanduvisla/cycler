# Compile the Cycler code:
cycler.o:
	gcc -c cycler.c

# Compile the test code, only if test does not exist, or cycler.o is newer than test:
test: cycler.o
	gcc -c test.c
	gcc -o test cycler.o test.o

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
	rm test