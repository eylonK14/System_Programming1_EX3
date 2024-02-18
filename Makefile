CC=gcc

FLAGS=-Wall -g

MAIN_FILES= StrList.o  Main.o
STRLIST_FILES= StrList.c  StrList.h

all: StrList

StrList: $(MAIN_FILES)
	$(CC) $(FLAGS) -o $@ $^
StrList.o: $(STRLIST_FILES)
	$(CC) $(FLAGS) -c StrList.c -o $@
Main.o: Main.c
	$(CC) $(FLAGS) -c Main.c -o $@	

.PHONY: clean all

clean:
    rm -f *.o *.a *.so *.gch  StrList.o  Main.o