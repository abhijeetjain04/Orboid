# ifndef SOURCE_HPP
# define SOURCE_HPP

#include <SDL_mixer.h>
#include <string>

#include "PaddleManager.hpp"
#include "Dot.hpp"
#include "ShowMenuImage.hpp"

#include<vector>

class Source {

public :
	Source ();
	~Source ();
	void execute ();

private:
	int difficulty ;
	SDL_Event e;

bool titlescreen ;
bool difficultyscreen ;
bool storyscreen ;
bool gameStarted ;
bool finalscreen ;
bool quit ;

bool init ();

bool loadMedia ();

void close ();

SDL_Window *Window;
SDL_Renderer *Renderer;
SDL_Surface *screensurface;
Mix_Music *Music ;
SDL_Texture *background;

ShowMenuImage Title;
ShowMenuImage StartGame;
ShowMenuImage DifficultyImage;
ShowMenuImage StoryImage;
ShowMenuImage FinalImage;

std::vector<ShowMenuImage*> menuImages;

};

# endif 