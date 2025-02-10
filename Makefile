SRC1 = pong.c
SRC2 = game.c
SRCS = $(SRC1) $(SRC2)
OBJ1 = $(SRC1:.c=.o)
OBJ2 = $(SRC2:.c=.o)
OBJS = $(OBJ1) $(OBJ2)
EXE  = $(SRC1:.c=.e)

RAYLIBFLAGS = -I inc/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm
GCCFLAGS    = -O1 -Wall -Werror -std=c99 -Wno-missing-braces

$(EXE) : $(OBJS)
	gcc -o $(EXE) $(OBJS) $(GCCFLAGS) $(RAYLIBFLAGS) 
	rm *.o
$(OBJS) : $(SRCS)
	gcc -c $(SRCS) $(GCCFLAGS) $(RAYLIBFLAGS) 
