CC := cc

CFLAGS := -Wall -pedantic -Werror


SRC := stack_test.c stack.c 
OBJ := $(SRC:.c=.o)

EXEC := stack.exe

$(EXEC) : $(OBJ) stack.h
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC)

clean :
	rm $(OBJ)
