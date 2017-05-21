#include "ShowMenuImage.hpp"
#include <SDL_image.h>

ShowMenuImage :: ShowMenuImage ()
{
	mTexture = nullptr;
	mWidth = 0;
	mHeight =0;
}

ShowMenuImage :: ~ShowMenuImage()
{
	free ();
}

bool ShowMenuImage ::loadMenuImage ( std :: string path )
{
	free ();

	SDL_Texture *newTexture = nullptr;
	SDL_Surface *loadedSurface = IMG_Load (path.c_str ());

	newTexture = SDL_CreateTextureFromSurface(m_renderer,loadedSurface);

	mWidth = loadedSurface->w;
	mHeight = loadedSurface->h;

	SDL_FreeSurface (loadedSurface);

	mTexture = newTexture ;
	return mTexture != nullptr;
}

void ShowMenuImage :: free ()
{
	SDL_DestroyTexture(mTexture);
	mTexture = nullptr;
	mWidth = 0;
	mHeight =0;
}

void ShowMenuImage::setRenderer(SDL_Renderer* renderer){
	m_renderer = renderer;
}

void ShowMenuImage::setDifficulty(int* var){
	mDifficulty = var;
}

void ShowMenuImage::setGameStarted(bool* var){
	mGameStarted = var;
}

void ShowMenuImage::setFinalScreen(bool* var){
	mFinalScreen = var;
}

void ShowMenuImage::setStoryScreen(bool* var){
	mStoryScreen = var;
}

void ShowMenuImage::setTitleScreen(bool* var){
	mTitleScreen = var;
}

void ShowMenuImage::setDifficultyScreen(bool* var){
	mDifficultyScreen = var;
}

void ShowMenuImage::setQuit (bool *var)
{
	mQuit =var;
}

void ShowMenuImage :: renderMenuText (int x, int y, SDL_Rect *clip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = {x,y,mWidth,mHeight};

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h =clip->h;
	}
	SDL_RenderCopy (m_renderer,mTexture,clip,&renderQuad);
}

void ShowMenuImage :: MenuHandleEvent( SDL_Event &e)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0 && e.key.keysym.sym == SDLK_s && *mTitleScreen == true)
	{	
		while (1)
		{
			SDL_RenderClear(m_renderer);
			*mTitleScreen = false;
			*mDifficultyScreen = true;
			break;
		}
	}

	if (e.type == SDL_KEYDOWN && e.key.repeat == 0 && (e.key.keysym.sym == SDLK_m ||e.key.keysym.sym == SDLK_h||e.key.keysym.sym == SDLK_e)&& *mDifficultyScreen==true)
	{	

		SDL_RenderClear(m_renderer);
		if (e.key.keysym.sym == SDLK_e )
		{
			*mDifficulty =4;
			*mStoryScreen =true;
			*mDifficultyScreen = false;
		}

		if (e.key.keysym.sym == SDLK_m )
		{
			*mDifficulty =6;
			*mStoryScreen =true;
			*mDifficultyScreen = false;
		}

		if (e.key.keysym.sym == SDLK_h )
		{
			*mDifficulty =8;
			*mStoryScreen =true;
			*mDifficultyScreen = false;	
		}		
	}

	if (e.type == SDL_KEYDOWN && e.key.repeat == 0 && e.key.keysym.sym == SDLK_k && *mStoryScreen==true )
	{
		while (1)
		{
			SDL_RenderClear(m_renderer);
			*mGameStarted = true;
			*mStoryScreen =false;
			break;
		}
	}

	if (e.type == SDL_KEYDOWN && e.key.repeat == 0 &&( e.key.keysym.sym == SDLK_y||e.key.keysym.sym == SDLK_n)&& *mFinalScreen==true)
	{	
		while (1)
		{
			if (e.key.keysym.sym == SDLK_y )
			{
				SDL_RenderClear(m_renderer);
				*mTitleScreen =true;
				*mFinalScreen = false;
				break;
			}

			if (e.key.keysym.sym == SDLK_n )
			{
				*mQuit = true;
				break;
			}	
	}
}
}