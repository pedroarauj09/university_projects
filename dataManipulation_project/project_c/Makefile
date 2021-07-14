CC = gcc
FLAGS= -std=c99 -Wextra -O2 -D_GNU_SOURCE
PKG = `pkg-config --cflags --libs glib-2.0`
INCLUDES=includes
SRC=src
OBJ=obj

all: users business review sgr table aux interface allprog

prog: users business review sgr table aux interface allprog
	
users: $(SRC)/users.c $(INCLUDES)/users.h
	$(CC) $(FLAGS) -o $(OBJ)/users.o $(PKG) -c $(SRC)/users.c

business: $(SRC)/business.c $(INCLUDES)/business.h
	$(CC) $(FLAGS) -o $(OBJ)/business.o $(PKG) -c $(SRC)/business.c

review: $(SRC)/review.c $(INCLUDES)/review.h
	$(CC) $(FLAGS) -o $(OBJ)/review.o $(PKG) -c $(SRC)/review.c

sgr: $(SRC)/sgr.c $(INCLUDES)/sgr.h
	$(CC) $(FLAGS) -o $(OBJ)/sgr.o $(PKG) -c $(SRC)/sgr.c

	
table: $(SRC)/table.c $(INCLUDES)/table.h
	$(CC) $(FLAGS) -o $(OBJ)/table.o $(PKG) -c $(SRC)/table.c

aux: $(SRC)/auxStructs.c $(INCLUDES)/auxStructs.h
	$(CC) $(FLAGS) -o $(OBJ)/auxStructs.o $(PKG) -c $(SRC)/auxStructs.c

interface: $(SRC)/interface.c $(INCLUDES)/interface.h
	$(CC) $(FLAGS) -o $(OBJ)/interface.o $(PKG) -c $(SRC)/interface.c

allprog: $(SRC)/main.c $(OBJ)/users.o $(OBJ)/business.o $(OBJ)/review.o $(OBJ)/sgr.o $(OBJ)/table.o $(OBJ)/auxStructs.o $(OBJ)/interface.o  
	$(CC) $(FLAGS) $(SRC)/main.c $(OBJ)/users.o $(OBJ)/business.o $(OBJ)/review.o $(OBJ)/sgr.o $(OBJ)/table.o $(OBJ)/auxStructs.o $(OBJ)/interface.o $(PKG) -o program

memcheck:
	valgrind --leak-check=yes ./program

clean:
	rm -rf $(OBJ)/*.o program