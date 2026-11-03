OBJ = a.out
SRC = main.c
SRC += game.c
SRC += framebuffer.c
CC = gcc
INCLUDE = ../wuziqi_pro\(1\)
LIB = ../wuziqi_pro\(1\)

$(OBJ):$(SRC)
	$(CC) $^ -I$(INCLUDE) -L$(LIB) -lm

