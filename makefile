DIR_SRC := ./src
DIR_INC := ./inc
DIR_LIB := ./lib
DIR_OBJ := ./obj

TARGET 	:= $(DIR_OBJ)/example.out
CC	:= gcc
CFLAGS	:= -I $(DIR_INC)

SRC := $(wildcard $(DIR_SRC)/*.c)
OBJ := $(patsubst %.c, $(DIR_OBJ)/%.o, $(notdir $(SRC)))

$(TARGET) : $(OBJ)
	$(CC) $^ -o $@

$(DIR_OBJ)/%.o : $(DIR_SRC)/%.c
	$(CC) -c $< $(CFLAGS) -o $@

.PHONY : debug
.PHONY : clean
.PHONY : lib

lib :
	$(CC) -fPIC -shared $(DIR_SRC)/queue.c $(CFLAGS) -o $(DIR_LIB)/libqueue.so
	ar crv $(DIR_LIB)/libqueue.a $(DIR_OBJ)/queue.o

debug :
	@echo SRC = $(SRC)
	@echo OBJ = $(OBJ)

clean :
	-rm $(TARGET) $(DIR_OBJ)/* $(DIR_LIB)/*
