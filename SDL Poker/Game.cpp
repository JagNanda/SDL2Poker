#include "Game.h"

using namespace std;


Game* Game::Instance() {
	static Game* game = new Game();
	return game;
}

bool Game::Init(const char* title, const int xpos, const int ypos, const int flags) {

	bool initFlag = true;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {


		m_gWindow = SDL_CreateWindow(title, xpos, ypos, WINDOW_WIDTH, WINDOW_HEIGHT, flags);


		if (m_gWindow != nullptr) {

			m_gRenderer = SDL_CreateRenderer(m_gWindow, -1, SDL_RENDERER_SOFTWARE);
			if (m_gRenderer != nullptr) {

				//renderer created

				if (IMG_Init(IMG_INIT_PNG) == IMG_INIT_PNG) {
					//init text loading
					if (TTF_Init() == 0) {


						//init sdl_mixer
						if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == 0) {


							//Load game images, music, fonts
							LoadMedia();
		
						}
						else {
							initFlag = false;
							cout << SDL_GetError() << "\n";
						}
					}
					else {
						initFlag = false;
						cout << SDL_GetError() << "\n";
					}

				}
				else {
					initFlag = false;
					cout << SDL_GetError() << "\n";
				}
			}
			else {
				initFlag = false;
				cout << SDL_GetError() << "\n";
			}
		}
		else {
			initFlag = false;
			cout << SDL_GetError() << "\n";
		}
	}
	else {
		initFlag = false;
		cout << SDL_GetError();
	}


	if (initFlag) {
		m_bRunning = true;
		m_keyStates = SDL_GetKeyboardState(nullptr);

		//shuffle deck and add cards to player hands
		m_deck.Shuffle();
		for (int i = 0; i < 10; i++) {
			m_player1.AddCardToHand(m_deck.DealCard());
			m_player2.AddCardToHand(m_deck.DealCard());
		}
		

	}


	return initFlag;
}

void Game::LoadMedia() {

	/*Example*/
	//render at bottom of screen
	//AssignRectDimensions(&m_rectMsg, WINDOW_WIDTH / 2 - 405, WINDOW_HEIGHT - 100, 810, 55);
	//int index = static_cast<int>(MESSAGE_PNGS::KEY_PRESS_INSTRUCTIONS);
	//LoadTexture(&m_msgTextures[index], "images/keyPressInstructions.png");
}



bool Game::LoadTexture(SDL_Texture** textureToLoad, string path) {

	Game* instance = Game::Instance();
	int successFlag = true;
	instance->m_gSurface = IMG_Load(path.c_str());

	if (instance->m_gSurface != nullptr) {

		*textureToLoad = SDL_CreateTextureFromSurface(instance->m_gRenderer, instance->m_gSurface);
		SDL_FreeSurface(instance->m_gSurface);
		if (textureToLoad == nullptr) {
			cout << "Couldn't load texture\n";
			successFlag = false;
		}
	}
	else {
		cout << "Couldn't load surface\n";
		successFlag = false;
	}

	return successFlag;

}

bool Game::KeyDown(SDL_Scancode c) {

	if (m_keyStates != nullptr) {
		if (m_keyStates[c] == 1) {
			return true;
		}
		else {
			return false;
		}
	}
	return false;

}

void Game::Update() {
	if (m_continuePlaying) {
		//incase we run out of cards
		m_deck.RestockDeck();
		m_deck.Shuffle();

		std::cout << "Before Exchanging\n\nPlayer1 Cards: \n";
		m_player1.PrintCards();
		std::cout << "\n\nPlayer2 Cards:\n";
		m_player2.PrintCards();
		std::cout << "\n\n";

		char exchangePlayer1;
		std::cout << "Exchange cards Player1? Enter y for Yes, otherwise press any key for No: ";
		std::cin >> exchangePlayer1;
		if (exchangePlayer1 == 'y') {
			m_player1.ExchangeCardToDeck(m_deck);
		}


		char exchangePlayer2;
		std::cout << "Exchange cards Player2? Enter y for Yes, otherwise press any key for No: ";
		std::cin >> exchangePlayer2;
		if (exchangePlayer2 == 'y') {
			m_player2.ExchangeCardToDeck(m_deck);
		}

		std::cout << "\nAfter Exchanging Cards\n\nPlayer 1 Cards: \n";
		m_player1.PrintCards();
		std::cout << "\nPlayer2 Cards:\n";
		m_player2.PrintCards();

		//determine winner
		std::cout << "\nPlayer1 Hand Value: ";
		int player1Hand = m_player1.DetermineBestHand();

		std::cout << "\nPlayer2 Hand Value: ";
		int player2Hand = m_player2.DetermineBestHand();


		if (player1Hand > player2Hand) {
			std::cout << "\nPlayer 1 Wins!\n";
			m_player1WinCount++;
		}
		else if (player1Hand == player2Hand) {
			std::cout << "\nIt was a tie.\n";
		}
		else {
			std::cout << "\nPlayer 2 Wins!\n";
			m_player2WinCount++;
		}

		//print out current scores
		std::cout << "Player 1 Score: " << m_player1WinCount << "\nPlayer 2 Score: " << m_player2WinCount;

		if (m_player1WinCount == 3 || m_player2WinCount == 3) {
			char continuePlayingChar;
			std::cout << "\nContinue Playing? Enter y for Yes, otherwise press any key for No: ";
			std::cin >> continuePlayingChar;
			std::cout << "\n\n\n";
			if (continuePlayingChar != 'y') {
				m_continuePlaying = false;
			}
			else {
				m_player1WinCount = 0;
				m_player2WinCount = 0;
			}
		}

		//just used to wait for player to continue game
		if (m_continuePlaying) {
			char c;
			std::cout << "\nNext Round! Press Any Key And Then ENTER To Continue.";
			std::cin >> c;
			std::cout << "\n\n";
		}
	}
}

void Game::HandleEvents()
{

	SDL_Event e;

	while (SDL_PollEvent(&e) != 0)
	{
		switch (e.type)
		{
		case SDL_QUIT:
			m_bRunning = false;
			break;
		case SDL_KEYUP:
			switch (e.key.keysym.sym) {
			case SDLK_UP:
				break;
			}
		}
	}

}



void Game::Render() {
	SDL_SetRenderDrawColor(m_gRenderer, 255, 255, 255, 255);
	SDL_RenderClear(m_gRenderer);
	
	/*Render copy example*/
	//SDL_RenderCopy(m_gRenderer, m_scoreTexture, nullptr, &m_rectScore);

	SDL_RenderPresent(m_gRenderer);

}


void Game::AssignRectDimensions(SDL_Rect* rect, int x, int y, int w, int h) {

	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;
}


void Game::Clean() {
	std::cout << "Cleaning game, bye!";
	SDL_DestroyWindow(m_gWindow);
	SDL_DestroyRenderer(m_gRenderer);

	SDL_Quit();
}