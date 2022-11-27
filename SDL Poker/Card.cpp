#include "Card.h"

const std::vector<std::string> Card::m_vFaces = {"Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace" };
const std::vector<std::string> Card::m_vSuits = { "Hearts", "Diamonds", "Spades", "Clubs" };

Card::Card(CardSuit suit, CardFace face) : m_cardSuit(suit), m_cardFace(face) {}

std::string Card::ToString() {
	return m_vFaces[(int)m_cardFace] + " of " + m_vSuits[(int)m_cardSuit];
}