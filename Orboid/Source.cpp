#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
# include "Source.hpp"

Source ::Source()
{
	titlescreen = true;
	difficultyscreen = false;
	storyscreen = false;
	gameStarted = false;
	finalscreen = false;
	quit = false;
				
	Window = nullptr;
	Renderer = nullptr;
	screensurface = nullptr;
	Music = nullptr;
	background = nullptr;
}

Source ::~Source ()
{
	close();
}

bool Source::init ()
{
	bool success = true;

	SDL_Init(SDL_INIT_VIDEO |  SDL_INIT_AUDIO);
	SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ); 
	Window = SDL_CreateWindow ( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN );
	screensurface = SDL_GetWindowSurface (Window);
	Renderer = SDL_CreateRenderer (Window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
	Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) ;
	SDL_SetRenderDrawColor(Renderer,0xFF, 0xFF, 0xFF, 0xFF);

	SDL_Surface* loadedsurface = IMG_Load ("Assets/background_image.png");
	background = SDL_CreateTextureFromSurface (Renderer,loadedsurface);

	SDL_FreeSurface(loadedsurface);

	SDL_RenderPresent(Renderer);

	menuImages.push_back(&Title);
	menuImages.push_back(&StartGame);
	menuImages.push_back(&DifficultyImage);
	menuImages.push_back(&StoryImage);
	menuImages.push_back(&FinalImage);

	for(unsigned i = 0;i < menuImages.size(); ++i){
		menuImages[i]->setDifficulty(&difficulty);
		menuImages[i]->setGameStarted(&gameStarted);
		menuImages[i]->setFinalScreen(&finalscreen);
		menuImages[i]->setStoryScreen(&storyscreen);
		menuImages[i]->setTitleScreen(&titlescreen);
		menuImages[i]->setDifficultyScreen(&difficultyscreen);
		menuImages[i]->setQuit(&quit);
		menuImages[i]->setRenderer(Renderer);
	}

	return success;
}

bool Source :: loadMedia ()
{
	bool success = true;
	Title.loadMenuImage("Assets/Title.png");
	DifficultyImage.loadMenuImage("Assets/difficultyscreen.png");
	StoryImage.loadMenuImage("Assets/story_image.png");
	FinalImage.loadMenuImage("Assets/final_image.png");

	Music = Mix_LoadMUS( "Assets/Background_Music _for_Games.MP3" );

	return success;
}

void Source:: close()
{
	//Menu loaded images
	Title.free();
	DifficultyImage.free();
	StoryImage.free();
	FinalImage.free();

	SDL_DestroyTexture(background);

	Mix_FreeMusic( Music );
	Music = NULL;

	//Destroy window	
	SDL_DestroyRenderer( Renderer );
	SDL_DestroyWindow( Window );
	Window = NULL;
	Renderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}


void Source ::execute ()
{
	init();
	loadMedia();

	Dot *dot = new Dot(400, 300, Renderer);
	dot->setDifficulty(&difficulty);
	dot->setGameStarted(&gameStarted);
	dot->setFinalScreen(&finalscreen);
	dot->setRenderer(Renderer);
	
	PaddleManager* paddleManager;
	paddleManager=PaddleManager::getInstance ();
	paddleManager->Initialize_Paddle(Renderer);
	paddleManager->setRenderer(Renderer);

	while (!quit)
	{
		//Background image
		SDL_RenderCopy(Renderer,background,NULL,NULL);

		if( Mix_PlayingMusic() == 0 )
		{
			Mix_PlayMusic( Music, -1 );
		}

		if(titlescreen)
		{
			// Menu render
			Title.renderMenuText (NULL,NULL);
			//StartGame.renderMenuText(300,450);
			SDL_RenderPresent(Renderer);
			while ((SDL_PollEvent (&e) !=0))
			{
				StartGame.MenuHandleEvent(e);
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}
			}
		}

		if (difficultyscreen)
		{
			DifficultyImage.renderMenuText(NULL,NULL);
			SDL_RenderPresent(Renderer);
			while ((SDL_PollEvent (&e) !=0))
			{
				DifficultyImage.MenuHandleEvent(e);
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}
			}
		}

		if (storyscreen)
		{
			StoryImage.renderMenuText(NULL,NULL);
			SDL_RenderPresent(Renderer);
			while ((SDL_PollEvent (&e) !=0))
			{
				StoryImage.MenuHandleEvent(e);
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}
			}	
		}
		
			while (gameStarted)
			{
				SDL_RenderCopy(Renderer,background,NULL,NULL);
				//Render objects
				dot->renderDot ();
				paddleManager->renderPaddles();

				while ((SDL_PollEvent (&e) !=0))
				{
					//Handle input for the dot
					dot->handleEvent(e);
					paddleManager->handleEvents(e);

					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
				}

				//Move the dot
				dot->Move();
				paddleManager->setDot(dot);
				paddleManager->movePaddles();
				paddleManager->collision_paddle(dot);

				//Update screen
				SDL_RenderPresent(Renderer);
				SDL_RenderClear(Renderer);
			}

		paddleManager->resetPaddles();

		if (finalscreen)
		{
			FinalImage.renderMenuText(NULL,NULL);
			SDL_RenderPresent(Renderer);
			
			while ((SDL_PollEvent (&e) !=0))
			{
				FinalImage.MenuHandleEvent(e);
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}	
			}
		}
	}
}
