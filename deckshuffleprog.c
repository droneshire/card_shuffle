//#START_MODULE_HEADER////////////////////////////////////////////////////////
//#
//# Filename:		deckshuffleprog.c
//#
//# Description:	This program analyzes a specified deck size to calculate 
//#					how many rounds it would take to 
//#					perform a cyclical shuffle sequence (1 card on table next 1 on 
//#					bottom of deck) before the original ordered deck reappears.
//#				
//#Arguments:	 	deckshuffleprog --num-cards <size of deck>
//#		 		 	deckshuffleprog --help
//#
//# Authors:     	Ross Yeager
//#
//#END_MODULE_HEADER//////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "deck.h"

// Program actions
typedef enum { RUN, HELP, NONE } action_t;

// Prototypes
void execute_shuffle(int deck_size);
void show_help(void);

// Main loop
int main (int argc, char **argv) {

	int deck_size;
	action_t action;

	printf("-----CARD CYCLE SHUFFLE-----\n\n");
	
	if (argc >= 3 && (strcmp(argv[1], "-n") == 0 || strcmp(argv[1], "--num-cards") == 0)) {
		action = RUN;
		deck_size = (int)strtol(argv[2], NULL, 10);

		if (deck_size <= 0) 
			action = NONE;
	}
	else if (argc >= 2 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)) {
		action = HELP;
	}
	else {
		action = NONE;	
	}

	switch (action) {
		case RUN:
			execute_shuffle(deck_size);
			break;
		case HELP:
			show_help();
			break;
		case NONE:
			printf("No deck size specified, use -n <deck size> or use -h for help...\n\n");
			break;
		default:
			break;
	}
	return 0;
}

//#START_FUNCTION_HEADER//////////////////////////////////////////////////////
//#
//# Description: 	Runs the actual shuffling program to calculate how many rounds
//#					it takes to get back to the original given a specified deck size
//#
//# Parameters:	 	Deck size
//#
//# Returns: 	 	Nothing
//#
//#//END_FUNCTION_HEADER////////////////////////////////////////////////////////
void execute_shuffle(int deck_size) {

	Deck *deck = (Deck *)malloc(sizeof(Deck));

	//initialize the deck/process
	deck->head_deck = (Card *)malloc(sizeof(Card));
	deck->tail_deck = NULL;
	deck->head_table = NULL;
	deck->tail_table = NULL;
	deck->deck_size = deck_size;
	deck->num_rounds = 0;

	deck_create(deck);
	printf("----------------------------\n");
	printf("Running using %d cards...\n", deck_size);
	printf("----------------------------\n");
	do 
	{
		// run until the round is complete
		while(!deck_card_to_table(deck)) {
			deck_card_to_back(deck);
		}
		++(deck->num_rounds);
		// only print out deck info if the deck size is reasonably small
		if (deck_size < 20) {
			printf("Round %4ld: ", deck->num_rounds);
			print_deck_order(deck->head_table);
		}
	} while (!deck_complete_round(deck));	// check the ordering of the deck

	printf("%d cards--> %ld rounds\n", deck->deck_size, deck->num_rounds);

	deck_delete(deck->head_table);
	free(deck);
}

//#START_FUNCTION_HEADER//////////////////////////////////////////////////////
//#	
//# Description: 	Help menu
//#
//# Parameters:	 	None
//#
//# Returns: 	 	Nothing
//#
//#//END_FUNCTION_HEADER////////////////////////////////////////////////////////
void show_help() {
	printf("This program analyzes a specified positive numbered deck size to\n");
	printf("calculate how many rounds it would take to perform a cyclical\n");
	printf("shuffle sequence (1 on table next on bottom of deck)\n");
	printf("before the original ordered deck reappears.\n\n");

	printf("Usage: deckshuffleprog --num-cards <size of deck>\n");
	printf("       deckshuffleprog --help\n\n");
	printf("       deckshuffleprog -s <size of deck>\n");
	printf("       deckshuffleprog -h \n\n");
}
