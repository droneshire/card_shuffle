//# START_MODULE_HEADER/////////////////////////////////////////////////////
//#
//# Filename:   deck.h 
//#
//# Description: Header file for deck and card manipulation
//#
//# Authors:     Ross Yeager
//#
//# END_MODULE_HEADER///////////////////////////////////////////////////////

#ifndef DECK_H_
#define DECK_H_

//# START_STRUCTURE_HEADER/////////////////////////////////////////////////////
//#
//# Card
//#
//# Description: 	Card structure node that stores the 
//#		 			original position and pointer to next card.
//#
//# END_STRUCTURE_HEADER///////////////////////////////////////////////////////
typedef struct card_t {
	int position_start;
	struct card_t * next;
} Card;

//# START_STRUCTURE_HEADER/////////////////////////////////////////////////////
//#
//# Deck
//#
//# Description: 	Deck structure containing pointers to the head/tail of each 
//#					pile: hand and table. Also contains the number of rounds 
//#					completed as well as the deck size.
//#
//# END_STRUCTURE_HEADER///////////////////////////////////////////////////////
typedef struct deck_t {
	Card *head_deck;
	Card *tail_deck;
	Card *head_table;
	Card *tail_table;
	long num_rounds;
	int deck_size;
} Deck;

// Function declarations
void deck_create(Deck *game);

int deck_card_to_table(Deck *game);
void deck_card_to_back(Deck *game);

int deck_check_order(Card *head);
int deck_complete_round(Deck *game);

void deck_delete(Card *head);

void print_deck_order(Card *head);

#endif /* DECK_H */
