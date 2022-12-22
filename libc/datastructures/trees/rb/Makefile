CC=gcc
FLAGS=-Wall -fstack-protector
INC=-I../include/
SOURCES = main.c rb.c ../include/traversals.c ../include/rotate.c

CFG=release
ifneq ($(CFG), release)
ifneq ($(CFG), debug)
	@echo "Invalid CFG specified. Valid options are:"
	@echo "release, debug"
endif
endif
ifeq ($(CFG), debug)
	FLAGS += -g3 -O0 -DDEBUG
else
	FLAGS += -O2
endif

.PHONY: all clean

all:
	$(CC) $(FLAGS) $(INC) $(SOURCES) -o run

clean:
	rm run
