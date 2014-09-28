CXX = gcc
FLAGS = -ggdb -Wall

all: deckshuffleprog

deckshuffleprog: deckshuffleprog.o deck.o
	${CXX} ${FLAGS} deckshuffleprog.o deck.o -o deckshuffleprog

deck.o: deck.c
	${CXX} ${FLAGS} -c deck.c

deckshuffleprog.o: deckshuffleprog.c 
	${CXX} ${FLAGS} -c deckshuffleprog.c
clean: 
	rm -f *o deckshuffleprog
