#pragma once
#include "Card.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>

class DeckOfCards
{

public:
	DeckOfCards();
	void PrintCardsInDeck();
	void Shuffle();
	Card* DealCard();
	bool MoreCards();
	void RestockDeck();

private:
	std::vector<Card*> m_vCards;
	//represents the next card to deal
	int m_currentCard = 0;

};

