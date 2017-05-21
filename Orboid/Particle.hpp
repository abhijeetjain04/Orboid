#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include "LTexture.hpp"

class Particle {

public :

	//Initialize position and animation
	Particle (int x, int y, SDL_Renderer*);
	~Particle();

	//Shows the particle
	void rendreParticle ();
	bool isDead ();

	void setRenderer(SDL_Renderer*);


private :
	int mPosX_P, mPosY_P;
	int mFrame;

	//Type of particle
	LTexture *mLTexture_P;

	LTexture *mRedTexture;
	LTexture *mGreenTexture;
	LTexture *mBlueTexture;
	LTexture *mShimmerTexture;


};

#endif
