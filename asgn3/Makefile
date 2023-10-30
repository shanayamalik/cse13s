CC=
SOURCE=test_password_checker.c password_checker.c
OBJ=test_password_checker.o password_checker.o
HEADER=password_checker.h

password_checker: ${OBJ} ${HEADER}
    $(CC) $(OBJ) -o password_checker

%.o: %.c $(HEADER)
    $(CC) $< -c

clean:
    rm -rf password_checker
    rm -rf *.o
