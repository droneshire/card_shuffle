//#START_MODULE_HEADER////////////////////////////////////////////////////////
//#
//# Filename:    	deck.c
//#
//# Description: 	Contains functions related to the manipulation of the decks
//#					and individual cards.
//#
//# Authors:     	Ross Yeager
//#
//#
//#END_MODULE_HEADER//////////////////////////////////////////////////////////
#include "deck.h"
#include <stdio.h>
#include <stdlib.h>

//#START_FUNCTION_HEADER//////////////////////////////////////////////////////
//#	
//# Description: 	Creates a new deck with a specified number of cards, logging 
//#		 			the cards initial position for comparison after rounds later.
//#
//# Parameters:		Deck structure pointer with the specified deck length and pointers 
//#					to the head and tail of the two "piles"
//#
//# Returns: 		Nothing
//#
//#//END_FUNCTION_HEADER////////////////////////////////////////////////////////
void deck_create(Deck *deck) {
	int i;
	Card *card;

	card = deck->head_deck;
	i=0;

	while(i++<=deck->deck_size) {
		card->next = (Card *)malloc(sizeof(Card));
		card->position_start = i;
		if (i == deck->deck_size) {
			deck->tail_deck = card;
			card->next = NULL;
			return;
		}
		card = card->next;
		if (card == NULL) {
			printf("Out of memory");
			return;
		}
		card->next = NULL;
	}
}

//#START_FUNCTION_HEADER//////////////////////////////////////////////////////
//#	
//# Description: 	Takes a card from the top of the deck in hand and puts it on 
//#		 			the top of the pile on the table.  Is the first half of a "move".
//#
//# Parameters:		Deck structure pointer
//#
//# Returns: 		0  -> Round still in progres i.e. still cards in hand deck
//#					1  -> Round complete, all cards are on the table
//#					-1 -> Deck is NULL, does not exist
//#
//#//END_FUNCTION_HEADER////////////////////////////////////////////////////////
int deck_card_to_table(Deck *deck) {
	Card *temp;

	if (deck->head_deck != NULL) {
		temp = deck->head_deck->next;

		if(deck->head_table == NULL) {
			deck->head_table = deck->head_deck;
			deck->head_table->next = NULL;
			deck->tail_table = deck->head_table;
		}
		else {
			deck->head_deck->next = deck->head_table;
			deck->head_table = deck->head_deck;	
		}

		deck->head_deck = temp;
		return (deck->head_deck == NULL) ? 1 : 0;
	} 
	else {
		printf("NULL deck!\n");
		return -1;
	}
}


//#START_FUNCTION_HEADER//////////////////////////////////////////////////////
//#	
//# Description: 	Takes a card from the top of the deck in hand and puts it on 
//#					the bottom of the deck in hand. Only need to move cards to the 
//#					back if there are 2+ cards in deck. Since this is the second 
//#					half of a "move", we will rely on deck_card_to_table to take 
//#					care of 1 card case.
//#
//# Parameters:	 	Deck structure pointer
//#
//# Returns: 	 	Nothing
//#
//#//END_FUNCTION_HEADER////////////////////////////////////////////////////////
void deck_card_to_back(Deck *deck) {
	Card *temp;
	
	temp= deck->head_deck->next;
	
	if (deck->head_deck->next != NULL) {
		deck->tail_deck->next = deck->head_deck;
		deck->tail_deck = deck->head_deck;
		deck->tail_deck->next = NULL;
		deck->head_deck = temp;
	}
}

//#START_FUNCTION_HEADER//////////////////////////////////////////////////////
//#	
//# Description: 	Checks to see if the deck is in order by comparing the current 
//# 		 		deck order to the original deck order.  It only continues to 
//# 		 		compare as long as the order is correct in order to be as efficient  
//# 		 		as possible.
//#
//# Parameters:	 	Card structure pointer to the head of the deck to be checked.
//#
//# Returns: 	 	0 -> Deck is not in original order
//#					1 -> Deck is in original order
//#
//#//END_FUNCTION_HEADER////////////////////////////////////////////////////////
int deck_check_order(Card *head) {
	int i = 1;

	while (head != NULL) {
		if (head->position_start != i++)
			return 0;	// as soon as one card is detected out of order, stop b/c we are not matching
		head = head->next;
	}
	return 1;	// we match the original order!
}

//#START_FUNCTION_HEADER//////////////////////////////////////////////////////
//#	
//# Description: 	Called at the end of each round (all cards on table) to 
//#		 			determine whether the whole process is complete.  It checks
//#		 			to see if the deck is in order, and if it is not it takes the
//#		 			deck on the table and places it back in hand to go another
//#		 			round.
//#
//# Parameters:		Deck structure pointer.
//#
//# Returns: 		0 -> Do another round
//#					1 -> No more rounds needed, deck is back in original order
//#
//#//END_FUNCTION_HEADER////////////////////////////////////////////////////////
int deck_complete_round(Deck *deck) {
		if (!deck_check_order(deck->head_table)) {
                // swap the table pile with the deck in hand for next round
                deck->head_deck = deck->head_table;
				deck->tail_deck = deck->tail_table;
                deck->head_table = NULL;
                return 0;
        }
        else {
                return 1;
		}
}

//#START_FUNCTION_HEADER//////////////////////////////////////////////////////
//#	
//# Description: 	Deletes the memory allocated for the deck.
//#
//# Parameters:		Card structure pointer to the head of the deck.
//#
//# Returns: 		Nothing
//#
//#//END_FUNCTION_HEADER////////////////////////////////////////////////////////
void deck_delete(Card *head) {
	if (head == NULL)
		return;
	else {
		deck_delete(head->next);
		free(head);
	}
}

//#START_FUNCTION_HEADER//////////////////////////////////////////////////////
//#	
//# Description: 	Prints out the deck showing the ordering of the cards based
//#		 			on current position.
//#
//# Parameters:		Card structure pointer
//#
//# Returns: 		Nothing
//#
//#//END_FUNCTION_HEADER////////////////////////////////////////////////////////
void print_deck_order(Card *head) {
	Card *card = head;
	while(card != NULL) {
		printf("%3d ", card->position_start);
		card = card->next;
	}
	printf("\n");
}
