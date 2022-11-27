#pragma once
#include <vector>
#include "Card.h"
#include <iostream>
#include "DeckOfCards.h"

class PokerHand
{

public:
	PokerHand();
	PokerHand(std::vector<Card*> cards);

	const int MAX_CARDS = 5;
	void AddCardToHand(Card* card);
	void PrintCards();
	std::vector<Card*> GetCards() {return m_vHand; }

	void SortCardsLowestToHighest();
	int DetermineBestHand();

	bool ContainsPair();
	bool ContainsTwoPairs();
	bool ContainsThreeOfAKind();
	bool ContainsStraight();
	bool ContainsFlush();
	bool ContainsFullHouse();
	bool ContainsFourOfAKind();
	bool ContainsStraightFlush();
	bool ContainsRoyalFlush();
	Card* GetHighestCard();
	void ExchangeCardToDeck(DeckOfCards& deck);
	std::vector<Card*> m_vHand;
	
};

