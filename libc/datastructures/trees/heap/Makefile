CC=gcc
SOURCE=heap.c main.c benchmarking.c 
INC=-I./
FLAGS=-lm
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
