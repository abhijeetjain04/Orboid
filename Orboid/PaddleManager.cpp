#include "PaddleManager.hpp"
#include "Dot.hpp"
#include "Constants.hpp"

PaddleManager* PaddleManager ::Manager = nullptr;
PaddleManager* PaddleManager ::getInstance ()
{
	if (Manager == nullptr)
	{
		Manager = new PaddleManager();
	}
	else 
	{
		return Manager;
	}
}

void PaddleManager::setDot(Dot* dot){
	mDot = dot;
}

void PaddleManager::Initialize_Paddle(SDL_Renderer* render){
	
	paddleRedTexture = new LTexture(render);
	paddleBlueTexture = new LTexture(render);

	paddleRedTexture->loadfromFile("Assets/paddle_red.png");
	paddleBlueTexture->loadfromFile("Assets/paddle_blue.png");

	paddleBlue = new Paddle((800/2), 10);
	paddleBlue->setTexture(paddleBlueTexture);
	paddleBlue->setAnalogOne('a');
	paddleBlue->setAnalogTwo('d');

	paddleRed = new Paddle((800/2),(600-40));
	paddleRed->setTexture(paddleRedTexture);
	paddleRed->setAnalogOne('j');
	paddleRed->setAnalogTwo('l');

	mScratch = Mix_LoadWAV( "Assets/score.wav" );
	
}

PaddleManager::~PaddleManager(){
	paddleRedTexture->free();
	paddleBlueTexture->free();

	Mix_FreeChunk(mScratch);
	mScratch = nullptr;
}

void PaddleManager::collision_paddle (Dot *dot1)
{
	collideRed();
	collideBlue();
}

void PaddleManager::renderPaddles(){
	paddleRed->renderPaddle();
	paddleBlue->renderPaddle();
}

void PaddleManager::handleEvents(SDL_Event e){
	paddleRed->handleEvent(e);	
	paddleBlue->handleEvent(e);
}

void PaddleManager::movePaddles(){
	paddleRed->movePaddle();	
	paddleBlue->movePaddle();	
}

void PaddleManager::resetPaddles(){
	paddleBlue->reset(800/2, 10);
	paddleRed->reset(800/2, 600-40);
}

void PaddleManager::setRenderer(SDL_Renderer* renderer){
	paddleRedTexture->setRenderer(renderer);
	paddleBlueTexture->setRenderer(renderer);
}

void PaddleManager::collideRed(){

	if ((mDot->mVelY_D > 0 ) && (mDot->mPosY_D + mDot->DOT_HEIGHT >= paddleRed->mPosY_Paddle) && (mDot->mPosY_D+ mDot->DOT_HEIGHT <= paddleRed->mPosY_Paddle + paddleRed->paddleHeight()))
	{
		if (( mDot->mPosX_D <= paddleRed->mPosX_Paddle + paddleRed->paddleWidth()) && ( mDot->mPosX_D + mDot->DOT_WIDTH >= paddleRed->mPosX_Paddle))
		{
			int paddle_center = paddleRed->mPosX_Paddle + paddleRed->paddleWidth() / 2;
			int ball_center =  mDot->mPosX_D + mDot->DOT_WIDTH / 2;
			int paddle_location = ball_center - paddle_center;

			mDot->mVelX_D= paddle_location / 10;
			mDot->mVelY_D = -mDot->mVelY_D;

			Mix_PlayChannel( -1, mScratch, 0 );
		}
	}
}

void PaddleManager::collideBlue(){

	if ((mDot->mVelY_D < 0) && (mDot->mPosY_D >= paddleBlue->mPosY_Paddle) && (mDot->mPosY_D <= paddleBlue->mPosY_Paddle + paddleBlue->paddleHeight()))
	{
		if (( mDot->mPosX_D <= paddleBlue->mPosX_Paddle + paddleBlue->paddleWidth()) && ( mDot->mPosX_D + mDot->DOT_WIDTH >= paddleBlue->mPosX_Paddle))
		{
			int paddle_center = paddleBlue->mPosX_Paddle + paddleBlue->paddleWidth() / 2;
			int ball_center =  mDot->mPosX_D + mDot->DOT_WIDTH / 2;
			int paddle_location = ball_center - paddle_center;

			mDot->mVelX_D= paddle_location / 10;
			mDot->mVelY_D = -mDot->mVelY_D;

			Mix_PlayChannel( -1, mScratch, 0 );
		}
	}
}

