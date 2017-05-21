#ifndef DOT_HPP
#define DOT_HPP

#include "Particle.hpp"
#include "LTexture.hpp"

#include <SDL_events.h>
#include <SDL_mixer.h>
#include <SDL_render.h>


//The dot that will move around on the screen

class Dot {

	public:
		int DOT_WIDTH;
		int DOT_HEIGHT;
		static const int DOT_VEL = 50;

		Dot (int x, int y, SDL_Renderer* render);
		~Dot ();

	void handleEvent (SDL_Event &e);
	void Move();
	//Shows the dot on the screen
	void renderDot();					

	// OFFSETS OF THE DOT
	int mPosX_D, mPosY_D;					 

	// VELOCITY OF THE DOT
	int mVelX_D, mVelY_D;

	void setDifficulty(int*);
	void setGameStarted(bool*);
	void setFinalScreen(bool*);

	void setRenderer(SDL_Renderer*);

private:
	// THE PARTICLES
	Particle* particle [12];

	LTexture *DotTexture;
	Mix_Chunk *mScore;

	int *mDifficulty;
	bool *mGameStarted;
	bool *mFinalScreen;

	// SHOW THE PARTICLES
	void renderParticles();			

	SDL_Renderer* mRenderer;
};


#endif