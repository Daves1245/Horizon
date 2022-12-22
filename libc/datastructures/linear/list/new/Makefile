CC=gcc
SOURCES=main.c list.c
FLAGS=-lm

CFG=release
ifneq ($(CFG),debug)
ifneq ($(CFG),release)
	@echo "Invalid configuration specified. Valid configurations are 'release', and 'debug'"
endif
endif

ifeq ($(CFG),debug)
	FLAGS += -DDEBUG -g3 -O0
endif

.PHONY: all clean

all:
	$(CC) $(SOURCES) $(FLAGS) -o run

clean:
	rm run
