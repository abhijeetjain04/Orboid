#include <SDL_image.h>
#include "LTexture.hpp"

LTexture::LTexture (SDL_Renderer* renderer)
{
	mTexture = nullptr;
	mWidth = 0;
	mHeight = 0;
	m_renderer = renderer;
}

LTexture::~LTexture ()
{
	free();
}

bool LTexture::loadfromFile( std::string path )
{
	free();

	SDL_Texture *newTexture = nullptr;
	SDL_Surface *loadedSurface = IMG_Load (path.c_str ());
	SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ));
	newTexture = SDL_CreateTextureFromSurface(m_renderer,loadedSurface);

	mWidth = loadedSurface->w;
	mHeight = loadedSurface->h;

	SDL_FreeSurface (loadedSurface);

	mTexture = newTexture;
	return mTexture != nullptr;
}

void LTexture::free()
{
	if(mTexture != nullptr){
		SDL_DestroyTexture(mTexture);
		mTexture = nullptr;
	}
	mWidth = 0;
	mHeight = 0;
}

void LTexture::renderLText (int x, int y, SDL_Rect *clip)
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

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

void LTexture::setRenderer(SDL_Renderer* renderer){
	m_renderer = renderer;
}