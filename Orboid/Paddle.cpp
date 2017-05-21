#include "Paddle.hpp"
#include "Constants.hpp"

Paddle::Paddle(int x, int y )
{
	mPosX_Paddle=x;
	mPosY_Paddle=y;

	mVel_Paddle =0;
}

void Paddle::renderPaddle()
{
	paddleTexture->renderLText(mPosX_Paddle,mPosY_Paddle);
	mPadleWidth = paddleTexture->getWidth();
	mPaddleHeight = paddleTexture->getHeight();
}

void Paddle::setTexture(LTexture* texture){
	paddleTexture = texture;
}

void Paddle::setAnalogOne(int analog){
	mAnalogOne = analog;
}

void Paddle::setAnalogTwo(int analog){
	mAnalogTwo = analog;
}

int Paddle::paddleWidth() const{
	return mPadleWidth;
}

int Paddle::paddleHeight() const{
	return mPaddleHeight;
}

void Paddle::reset(int x, int y){
	mPosX_Paddle = x;
	mPosY_Paddle = y;

	mVel_Paddle =0;
}

void Paddle::setRenderer(SDL_Renderer* rendere){
	paddleTexture->setRenderer(rendere);
}

void Paddle::handleEvent(SDL_Event &e)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		if(e.key.keysym.sym == mAnalogOne){
			mVel_Paddle -= PADDLE_VEL;
		}
		else if(e.key.keysym.sym == mAnalogTwo){
			mVel_Paddle += PADDLE_VEL;
		}	
	}
	else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
	{
		if(e.key.keysym.sym == mAnalogOne){
			mVel_Paddle += PADDLE_VEL;
		}
		else if(e.key.keysym.sym == mAnalogTwo){
			mVel_Paddle -= PADDLE_VEL;
		}	
	}
}

void Paddle::movePaddle ()
{
	mPosX_Paddle += mVel_Paddle;
	if ((mPosX_Paddle < 0) || (mPosX_Paddle + mPadleWidth > 800))
	{
		mPosX_Paddle -= mVel_Paddle;
	}
}
