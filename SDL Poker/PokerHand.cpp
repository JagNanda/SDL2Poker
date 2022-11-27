#include "PokerHand.h"

PokerHand::PokerHand(){}

PokerHand::PokerHand(std::vector<Card* > cards) {
	for (int i = 0; i < MAX_CARDS; i++) {
		AddCardToHand(cards[i]);
	}
}


void PokerHand::AddCardToHand(Card* card) {
	
	if (m_vHand.size() < MAX_CARDS) {
		m_vHand.push_back(card);
	}
}

void PokerHand::PrintCards() {
	
	for (int i = 0; i < m_vHand.size(); i++) {
		if (i == 0) {
			std::cout << m_vHand[i]->ToString();
		}
		else {
			std::cout << ", " << m_vHand[i]->ToString();
		}
	}
}

int PokerHand::DetermineBestHand() {

	SortCardsLowestToHighest();
	if (ContainsRoyalFlush()) { std::cout << "Royal Flush"; return 100; }
	else if (ContainsStraightFlush()) { std::cout << "Straight Flush"; return 99; }
	else if (ContainsFourOfAKind()) { std::cout << "Four of a Kind"; return 98; }
	else if (ContainsFullHouse()) { std::cout << "Full House"; return 97; }
	else if (ContainsFlush()) { std::cout << "Flush"; return 96; }
	else if (ContainsStraight()) { std::cout << "Straight"; return 95; }
	else if (ContainsThreeOfAKind()) { std::cout << "Three of a Kind"; return 94; }
	else if (ContainsTwoPairs()) { std::cout << "Two Pair"; return 93; }
	else if (ContainsPair()) { std::cout << "Pair"; return 92; }
	else {
		std::cout << "Highest Card: " << GetHighestCard()->ToString();
		return (int)GetHighestCard()->GetCardFace();
	}
}

void PokerHand::SortCardsLowestToHighest() {

	for (int i = 0; i < MAX_CARDS; i++) {

		for (int j = i + 1; j < MAX_CARDS; j++) {
			
			if ((int)m_vHand[i]->GetCardFace() > (int)m_vHand[j]->GetCardFace()) {

				Card* temp = m_vHand[i];
				m_vHand[i] = m_vHand[j];
				m_vHand[j] = temp;
			}
		}
	}
}

bool PokerHand::ContainsPair() {

	for (int i = 0; i < MAX_CARDS; i++) {
		for (int j = i + 1; j < MAX_CARDS; j++) {
			if (m_vHand[i]->GetCardFace() == m_vHand[j]->GetCardFace()) {
				/*std::cout << "\n" << m_vHand[i]->ToString() << " " << m_vHand[j]->ToString();*/
				return true;
			}
		}

	}

	return false;
}

bool PokerHand::ContainsTwoPairs() {

	bool hasPair = false;

	for (int i = 0; i < MAX_CARDS; i++) {
		for (int j = i + 1; j < MAX_CARDS; j++) {
			if (m_vHand[i]->GetCardFace() == m_vHand[j]->GetCardFace()) {
				/*std::cout << "\n" << m_vHand[i]->ToString() << " " << m_vHand[j]->ToString();*/
				if (hasPair == false) {
					hasPair = true;
				}
				else {
					return true;
				}
			}
		}

	}

	return false;
	
}

bool PokerHand::ContainsThreeOfAKind() {
	
	bool hasPair = false;

	for (int i = 0; i < MAX_CARDS; i++) {

		for (int j = i + 1; j < MAX_CARDS; j++) {
			
			if (m_vHand[i]->GetCardFace() == m_vHand[j]->GetCardFace()) {

				if (!hasPair) {
					hasPair = true;
				}
				else {
					return true;
				}
			}
		}

		hasPair = false;
	}

	return false;
}

bool PokerHand::ContainsStraight() {
	

	for (int i = 0; i < MAX_CARDS - 1; i++) {
		if (!((int)m_vHand[i]->GetCardFace() + 1 == (int)m_vHand[i + 1]->GetCardFace())) {
			return false;			
		}
	}

	return true;
}

bool PokerHand::ContainsFlush() {

	
	Card::CardSuit suit = m_vHand[0]->GetCardSuite();
	for (int i = 1; i < MAX_CARDS; i++) {
		
		if (m_vHand[i]->GetCardSuite() != suit) {
			return false;
		}
	}

	return true;
}

bool PokerHand::ContainsFullHouse() {

	int aceCount = 0;
	int kingCount = 0;

	for (int i = 0; i < MAX_CARDS; i++) {
		if (m_vHand[i]->GetCardFace() == Card::CardFace::ACE) {
			aceCount++;
		}
		else if (m_vHand[i]->GetCardFace() == Card::CardFace::KING) {
			kingCount++;
		}
		else {
			return false;
		}
	}

	if (aceCount == 3 && kingCount == 2) {
		return true;
	}

	return false;

}

bool PokerHand::ContainsFourOfAKind() {

	int count = 1;
	for (int i = 0; i < 2; i++) {
		for (int j = i + 1; j < MAX_CARDS; j++) {
			if (m_vHand[i]->GetCardFace() == m_vHand[j]->GetCardFace()) {
				count++;
			}
			if (count == 4) {
				return true;
			}
		}
		count = 1;
	}

	return false;
}


bool PokerHand::ContainsStraightFlush() {
	
	Card::CardSuit startingSuit = m_vHand[0]->GetCardSuite();

	for (int i = 1; i < MAX_CARDS; i++) {
		
		if (m_vHand[i]->GetCardSuite() != startingSuit) {
			return false;
		}
		if ((int)m_vHand[i]->GetCardFace() != (int)m_vHand[i - 1]->GetCardFace() + 1) {
			return false;
		}
		
	}

	return true;
}

bool PokerHand::ContainsRoyalFlush() {

	Card::CardSuit startingSuit = m_vHand[0]->GetCardSuite();
	if (m_vHand[0]->GetCardFace() != Card::CardFace::NINE) {
		return false;
	}

	for (int i = 1; i < MAX_CARDS; i++) {

		if (m_vHand[i]->GetCardSuite() != startingSuit) {
			return false;
		}
		if ((int)m_vHand[i]->GetCardFace() != (int)m_vHand[i - 1]->GetCardFace() + 1) {
			return false;
		}

	}

	return true;
}

Card* PokerHand::GetHighestCard() {

	return m_vHand[4];
}

void PokerHand::ExchangeCardToDeck(DeckOfCards& deck) {

	int cardsExchanged = 0;
	int indexToExchange;

	std::cout << "\n";

	char contineExchanging;
	while (cardsExchanged < 3) {

		std::cout << "Pick a card to exchange by entering 1,2,3,4, or 5: ";
		std::cin >> indexToExchange;
		std::cout << "\nPlayers Previous Hand: ";
		PrintCards();
		std::cout << "\nPlayers New Hand: ";
		m_vHand[indexToExchange - 1] = deck.DealCard();
		PrintCards();
		std::cout << "\n\n";
		if (cardsExchanged < 2) {
			std::cout << "Exchange Another card? Enter y for yes or another other key for no: ";
			std::cin >> contineExchanging;
		}
		if (contineExchanging != 'y') {
			break;
		}
		cardsExchanged++;
	}

	std::cout << "\n\n\n";

}
