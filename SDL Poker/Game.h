#pragma once
#include "SDL.h"
#include "string"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <iostream>
#include "SDL_mixer.h"
#include "Card.h"
#include "DeckOfCards.h"
#include "PokerHand.h"


class Game
{

private:
	Game() :
		m_bRunning(false), m_deck(), m_player1(), m_player2(),
		m_continuePlaying(true), m_player1WinCount(0), m_player2WinCount(0) {}
	bool m_bRunning;

	bool m_continuePlaying;
	int m_player1WinCount;
	int m_player2WinCount;

	SDL_Renderer* m_gRenderer;
	SDL_Window* m_gWindow;
	SDL_Surface* m_gSurface;

	const Uint8* m_keyStates;

	DeckOfCards m_deck;
	PokerHand m_player1;
	PokerHand m_player2;

public:

	static const int WINDOW_WIDTH = 1000;
	static const int WINDOW_HEIGHT = 400;

	//Create and return static Game* instance
	static Game* Instance();

	bool Init(const char* title, const int xpos, const int ypos, const int flags);
	void Update();
	void HandleEvents();
	void Render();
	void Clean();
	
	bool KeyDown(SDL_Scancode c);

	//load starting images, music, and fonts 
	void LoadMedia();
	//load any texture
	static bool LoadTexture(SDL_Texture** textureToLoad, std::string path);
	//set a size for any SDL_Rect
	static void AssignRectDimensions(SDL_Rect* rect, int x, int y, int w, int h);


	bool IsRunning() { return m_bRunning; }

	SDL_Window* GetGameWindow() const { return m_gWindow; }
	SDL_Renderer* GetGameRenderer() const { return m_gRenderer; }
	SDL_Surface* GetGameSurface() const { return m_gSurface; }

};

