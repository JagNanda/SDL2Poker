#include "DeckOfCards.h"

DeckOfCards::DeckOfCards() {

	
	m_currentCard = 0;

	for (int suit = 0; suit <= (int)Card::CardSuit::CLUBS; suit++) {
		for (int face = 0; face <= (int)Card::CardFace::ACE; face++) {
			m_vCards.push_back(new Card((Card::CardSuit)suit, (Card::CardFace)face));
		}
	}

	srand(time(nullptr));
}

void DeckOfCards::PrintCardsInDeck() {

	for (int i = 0; i < m_vCards.size(); i++) {
		std::cout << m_vCards[i]->ToString() << "\n";
	}
}

void DeckOfCards::Shuffle() {
	
	//index between 0 and 52
	int randIndex;
	Card* temp;

	for (int i = 0; i < m_vCards.size(); i++) {
		randIndex = rand() % 52;
		temp = m_vCards[i];
		m_vCards[i] = m_vCards[randIndex];
		m_vCards[randIndex] = temp;

	}

}

Card* DeckOfCards::DealCard() {

	Card* current = m_vCards[m_currentCard];
	m_currentCard++;

	return current;
}

bool DeckOfCards::MoreCards() {

	if (m_currentCard == 52) {
		return false;
	}
	return true;
}

void DeckOfCards::RestockDeck() {
	m_currentCard = 0;
}
