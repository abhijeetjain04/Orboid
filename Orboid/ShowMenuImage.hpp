#ifndef SHOWMENUIMAGE_HPP
#define SHOWMENUIMAGE_HPP

#include <string>
#include <SDL_events.h>
#include <SDL_rect.h>
#include <SDL_render.h>

class ShowMenuImage {				
public:					
	 ShowMenuImage();
	~ShowMenuImage();

	bool loadMenuImage (std::string path);
	void free();
	void MenuHandleEvent (SDL_Event &e); 

	//Renders texture at given point
	void renderMenuText (int x, int y, SDL_Rect *clip = nullptr); 

	//Image dimensions
	int mWidth;
	int mHeight;

	void setRenderer(SDL_Renderer* renderer);

	void setDifficulty(int* var);
	void setGameStarted(bool* var);
	void setFinalScreen(bool* var);
	void setStoryScreen(bool* var);
	void setTitleScreen(bool* var);
	void setDifficultyScreen(bool* var);
	void setQuit (bool *var);

private:
	//The actual hardware texture
	SDL_Texture *mTexture;
	SDL_Renderer* m_renderer;

	int *mDifficulty;
	bool *mGameStarted, *mFinalScreen, *mStoryScreen, *mTitleScreen, *mDifficultyScreen, *mQuit;

};

#endif