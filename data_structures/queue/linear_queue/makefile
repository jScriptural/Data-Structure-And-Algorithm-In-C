CC := cc
CFLAGS := -pedantic -Wall -Werror

SRC := queue.c queue_test.c
OBJ := $(SRC:.c=.o)

EXEC := queue.exe

$(EXEC) : $(OBJ) queue.h
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC)


clean : 
	rm $(OBJ)


