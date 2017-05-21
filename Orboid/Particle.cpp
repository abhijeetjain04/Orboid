#include "Particle.hpp"
#include "LTexture.hpp"

#include <cstdlib>

Particle :: Particle ( int x, int y, SDL_Renderer* render )
{
	//Set offsets
	mPosX_P = x + (rand() % 10);
	mPosY_P = y + (rand() % 10);

	//Initialize animation
	mFrame = rand () % 3;

	mRedTexture = new LTexture(render);
	mGreenTexture = new LTexture(render);
	mBlueTexture = new LTexture(render);
	mShimmerTexture = new LTexture(render);


	mRedTexture->loadfromFile( "Assets/red_p.bmp" );
	mGreenTexture->loadfromFile( "Assets/green_p.bmp" ) ;
	mBlueTexture->loadfromFile( "Assets/blue_p.bmp" ) ;
	mShimmerTexture->loadfromFile( "Assets/shimmer_p.bmp" );

	switch (rand () % 3)
	{
	case 0 : mLTexture_P = mRedTexture; 
		break;
	case 1: mLTexture_P = mGreenTexture;
		break;
	case 2: mLTexture_P = mBlueTexture;
		break;
	}
}

Particle::~Particle(){
	mRedTexture->free();
	mGreenTexture->free();
	mBlueTexture->free();
	mShimmerTexture->free();
}

void Particle :: rendreParticle ()
{
	 //Show image
	mLTexture_P->renderLText(mPosX_P,mPosY_P);

	//Show shimmer
	if (mFrame % 2 == 0)
	{
		mShimmerTexture->renderLText(mPosX_P,mPosY_P);
	}

	// ANIMATE
	mFrame++;		
}

bool Particle::isDead ()
{
	return mFrame > 2;
}

void Particle::setRenderer(SDL_Renderer* rendere){
	mLTexture_P->setRenderer(rendere);
}
