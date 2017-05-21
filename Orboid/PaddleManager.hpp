#ifndef PADDLE_MANAGER_HPP
#define PADDLE_MANAGER_HPP

#include <SDL_events.h>
#include <SDL_mixer.h>

#include "Paddle.hpp"
#include "LTexture.hpp"

class Dot;

class PaddleManager{

	Paddle *paddleRed, *paddleBlue;
	LTexture *paddleRedTexture, *paddleBlueTexture;
	Dot* mDot;

	void collideRed();
	void collideBlue();
	
public:
	void Initialize_Paddle(SDL_Renderer*);
	~PaddleManager();

	void collision_paddle (Dot *dot1);
	void renderPaddles();
	void handleEvents(SDL_Event e);
	void movePaddles();
	void resetPaddles();
	void setDot(Dot* dot);
	void setRenderer(SDL_Renderer*);

	static PaddleManager* getInstance ();
	Mix_Chunk *mScratch;

private :
	static PaddleManager *Manager;
	        PaddleManager (){}
};


#endif