#ifndef LTEXTURE_HPP
#define LTEXTURE_HPP

#include <string>
#include <SDL_rect.h>
#include <SDL_render.h>

class LTexture {

public:					
	
	LTexture(SDL_Renderer*);
	~LTexture();

	bool loadfromFile (std::string path);
	void free();

	//Renders texture at given point
	void renderLText (int x, int y, SDL_Rect *clip = nullptr); 
	
	int getWidth();
	int getHeight();

	//Image dimensions
	int mWidth;
	int mHeight;

	void setRenderer(SDL_Renderer*);

private:
	//The actual hardware texture
	SDL_Texture* mTexture;
	SDL_Renderer* m_renderer;
};


#endif