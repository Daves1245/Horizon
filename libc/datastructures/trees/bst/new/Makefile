CC=gcc
FLAGS=-Wall

CFG=release
ifneq ($(CFG), debug)
ifneq ($(CFG), release)
	@echo "CFG not supported. Supported: 'release', 'debug'"
endif
endif
ifeq ($(CFG), debug)
	FLAGS += -DDEBUG
endif

.PHONY: all clean

all:
	$(CC) $(FLAGS) bst.c -o run
clean:
	rm run
