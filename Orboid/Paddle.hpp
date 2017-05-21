#ifndef PADDLE_HPP
#define PADDLE_HPP

#include <SDL_events.h>
#include <SDL_render.h>

#include "LTexture.hpp"

class Paddle  {

public : 
	static const int PADDLE_VEL = 10;

	Paddle(int x, int y);
	
	int mPadleWidth;
	int mPaddleHeight;

	void handleEvent (SDL_Event &e);
	void movePaddle();
	void renderPaddle();

	int mPosX_Paddle, mPosY_Paddle;	
	int mVel_Paddle;

	void setTexture(LTexture*);

	void setAnalogOne(int);
	void setAnalogTwo(int);

	int paddleWidth() const;
	int paddleHeight() const;

	void reset(int,int);

	void setRenderer(SDL_Renderer*);


private:
	LTexture *paddleTexture;
	int mAnalogOne, mAnalogTwo;

};


#endif