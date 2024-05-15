CC := cc

CFLAGS := -Wall -pedantic -Werror


SRC := jarray_test.c jarray.c 
OBJ := $(SRC:.c=.o)

EXEC := jarray.exe

$(EXEC) : $(OBJ) jarray.h
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC)

clean :
	rm $(OBJ)
