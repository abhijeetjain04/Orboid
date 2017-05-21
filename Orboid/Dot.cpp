#include "Dot.hpp"

Dot :: Dot (int x , int y, SDL_Renderer* render)
{
	mRenderer = render;

	// INITIALIZE THE DOT POSITION
	mPosX_D = x;
	mPosY_D = y;

	// INITIALIZE THE DOT VELOCITY
	mVelX_D = 0;
	mVelY_D = 0;

	DotTexture = new LTexture(render);

	DOT_WIDTH = DotTexture->getWidth ()+20;
	DOT_HEIGHT = DotTexture->getHeight ()+20;

	//Initialize particles
	for (int i =0;i<12;i++)
	{
		int nPosX = mPosX_D - 1;
		int nPosY = mPosY_D - 1;
		particle[i] = new Particle (nPosX,nPosY,render);
	}

	DotTexture->loadfromFile( "Assets/dot_p.bmp" );
	mScore = Mix_LoadWAV( "Assets/medium.wav" );
}

Dot ::~Dot ()
{
	for (int i =0;i<12;i++)
	{
		delete particle [i];
	}
	DotTexture->free();
	Mix_FreeChunk(mScore);
	mScore = nullptr;
}

void Dot::setDifficulty(int* var){
	mDifficulty = var;
}
void Dot::setGameStarted(bool* var){
	mGameStarted = var;
}
void Dot::setFinalScreen(bool* var){
	mFinalScreen = var;
}

void Dot::setRenderer(SDL_Renderer* rendere){
	DotTexture->setRenderer(rendere);
	for (int i =0; i < 12 ; i++)
	{
		particle[i]->setRenderer(rendere);
	}

}

void Dot :: handleEvent (SDL_Event &e)
{
	if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE)
	{
		if (mVelY_D == 0)
		{
			mVelY_D=mVelY_D + *mDifficulty;
		}
	}
}

void Dot :: Move()
{
	mPosX_D += mVelX_D;
	if ((mPosX_D < 0) || ((mPosX_D + DOT_WIDTH) > 800))
	{
		mVelX_D = -mVelX_D;
	}

	mPosY_D += mVelY_D;
	if ((mPosY_D < 0)||(mPosY_D + DOT_HEIGHT > 600))
	{
		mPosX_D = (800/2);
		mPosY_D = (600/2);
		mVelX_D =0;
		mVelY_D =0;

		*mGameStarted =false;
		*mFinalScreen = true;
	}
}

void Dot ::renderDot ()
{
	//Show the dot
	DotTexture->renderLText (mPosX_D,mPosY_D);

	//Show particles on top of dot
	if ((mPosX_D < 1) ||(mPosX_D + DOT_WIDTH > 800-1))
	{
		renderParticles ();
		Mix_PlayChannel( -1, mScore, 0 );
	}
	if ((mPosY_D < 1)||(mPosY_D + DOT_HEIGHT > 600-1))
	{
		renderParticles ();
		Mix_PlayChannel( -1, mScore, 0 );
	}
}

void Dot ::renderParticles ()
{
	//Go through particles
	for (int i=0; i < 12 ;i++)
	{
		//Delete and replace dead particles
		if (particle[i]->isDead ())
		{
			delete particle[i];
			particle[i]= new Particle (mPosX_D,mPosY_D,mRenderer);
		}
	}

	//Show particles
	for (int i =0; i < 12 ; i++)
	{
		particle[i]->rendreParticle();
	}
}