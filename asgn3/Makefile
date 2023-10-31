#Define the GNU Compiler Collection to use
CC=gcc

#List the source C files;
#  list the object files that will be generated from the source files;
#  specify the header files
SOURCE=test_password_checker.c password_checker.c
OBJ=test_password_checker.o password_checker.o
HEADER=password_checker.h

#Write the password_checker executable file;
#  link the object files into a single executable
password_checker: ${OBJ} ${HEADER}
	$(CC) $(OBJ) -o password_checker

%.o : %.c $(HEADER)
	$(CC) -c $<

#Clean the project directory;
#  forcefully remove the compiled files
clean:
	rm -f password_checker
	rm -f *.o
