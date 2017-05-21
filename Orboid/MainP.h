# include <SDL.h>
# include <SDL_image.h>
# include <stdio.h>
# include <SDL_mixer.h>
# include <string>
#include "Constants.h"

# ifndef MainP1
# define MainP1

class LTexture;
class Particle;
class Dot;
class Paddle;

bool titlescreen = true;
bool difficultyscreen = false;
bool storyscreen = false;
bool gameStarted = false;
bool finalscreen = false;

bool init ();
bool loadMedia ();
void close ();

SDL_Window *Window = nullptr;
SDL_Renderer *Renderer = nullptr;
SDL_Surface *screensurface = nullptr;
Mix_Music *Music = nullptr;

SDL_Texture *background = nullptr;


LTexture Paddle_R;
LTexture Paddle_B;
LTexture RedTexture;
LTexture GreenTexture;
LTexture BlueTexture;
LTexture ShimmerTexture;

ShowMenuImage Title;
ShowMenuImage StartGame;
ShowMenuImage DifficultyImage;
ShowMenuImage StoryImage;
ShowMenuImage FinalImage;

# endif Mainp1