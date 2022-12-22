CC=gcc
SOURCE=kruskals.c main.c ../../../datastructures/graph_theory/ufds/ufds.c ../../../datastructures/vector/vector.c
INC=-I../../../datastructures/graph_theory/ufds/ -I../../../datastructures/vector/
FLAGS=-Wall
CFG=release

ifneq ($(CFG),debug)
ifneq ($(CFG),release)
	@echo "Invalid CFG. Try 'debug' or 'release'"
endif
endif

ifeq ($(CFG), debug)
	FLAGS+=-g3 -O0
endif

all:
	$(CC) $(INC) $(SOURCE) -o run $(FLAGS)
clean:
	rm run
