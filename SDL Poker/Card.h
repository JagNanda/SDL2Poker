#pragma once
#include <vector>
#include <string>

class Card
{
public:
	enum class CardFace {TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE };
	enum class CardSuit {HEARTS, DIAMONDS, SPADES, CLUBS};

	Card(CardSuit suite, CardFace face);
	
	void SetCardSuite(CardSuit suit) { m_cardSuit = suit; }
	CardSuit GetCardSuite() const { return m_cardSuit; }

	void SetCardFace(CardFace face) { m_cardFace = face; }
	CardFace GetCardFace() const { return m_cardFace; }

	std::string ToString();

	static const std::vector<std::string> m_vSuits;
	static const std::vector<std::string> m_vFaces;

private:
	CardFace m_cardFace;
	CardSuit m_cardSuit;

};

