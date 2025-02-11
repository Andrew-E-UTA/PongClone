SRC1 = src/pong.c
SRC2 = src/game.c
SRCS = $(SRC1) $(SRC2)
OBJ1 = $(SRC1:.c=.o)
OBJ2 = $(SRC2:.c=.o)
OBJS = $(OBJ1) $(OBJ2)
EXE  = $(SRC1:.c=.exe)

RAYLIBFLAGS = -I inc/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm
GCCFLAGS    = -O1 -Wall -Werror -std=c99 -Wno-missing-braces

$(EXE) : $(OBJS)
	gcc -o $(EXE) $(OBJS) $(GCCFLAGS) $(RAYLIBFLAGS) 
	rm src/*.o
	mv src/*.exe ./

$(OBJS) : $(SRCS)
	gcc -c $(SRCS) $(GCCFLAGS) $(RAYLIBFLAGS) 
	mv *.o src/
