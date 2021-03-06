// Graphics.cpp
// Singleton
// Handle the initialization of the graphics related SDL libraries
// and their release
// Also handles texture and text loading

#include "Graphics.h"

//Initializing to NULL
Graphics* Graphics::sInstance = nullptr;

//Initializing to false
bool Graphics::sInitialized = false;

Graphics* Graphics::Instance() 
{
	//Create a new instance if no instance was created before
	if (sInstance == nullptr)
		sInstance = new Graphics();

	return sInstance;
}

void Graphics::Release() 
{
	delete sInstance;
	sInstance = nullptr;

	sInitialized = false;
}

bool Graphics::Initialized() 
{
	return sInitialized;
}

Graphics::Graphics() 
{
	sInitialized = Init();
}

Graphics::~Graphics() 
{
	SDL_DestroyWindow(mWindow);
	mWindow = nullptr;

	SDL_DestroyRenderer(mRenderer);
	mRenderer = nullptr;

	//Closing all open SDL graphic libraries
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

bool Graphics::Init() 
{
	//Initialize SDL Video and Audio and handling initialization errors
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) 
	{
		printf("SDL Initialization Error: %s\n", SDL_GetError());
		return false;
	}

	//Creating the window 
	mWindow = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	//Handling with window creation errors
	if (mWindow == nullptr) 
	{
		printf("Window Creation Error: %s\n", SDL_GetError());
		return false;
	}

	//Creating the renderer
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);

	//Handling with the renderer creation errors
	if (mRenderer == nullptr) 
	{
		printf("Renderer Creation Error: %s\n", SDL_GetError());
		return false;
	}

	//Setting with window creation errors 
	SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0xFF);

	//Initializing the SDL_image library and handling initialization errors
	int flags = IMG_INIT_PNG;
	if (!(IMG_Init(flags) & flags)) 
	{
		printf("IMG Initialization Error: %s\n", IMG_GetError());
		return false;
	}

	//Initializing the SDL_ttf library and handling initialization errors
	if (TTF_Init() == -1) 
	{
		printf("TTF Initialization Error: %s\n", TTF_GetError());
		return false;
	}

	//return true if no errors occurred during initialization
	return true;
}

SDL_Texture* Graphics::LoadTexture(std::string path) 
{
	SDL_Texture* tex = nullptr;

	//load the image onto a surface
	SDL_Surface* surface = IMG_Load(path.c_str());
	//Handling image loading errors
	if (surface == nullptr) 
	{
		printf("Image Load Error: Path(%s) - Error(%s)\n", path.c_str(), IMG_GetError());
		return tex;
	}

	//Color key image
	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0xFF, 0));
	//Converting the surface into a texture to be able to render it using the renderer
	tex = SDL_CreateTextureFromSurface(mRenderer, surface);
	//Handling texture creation errors
	if (tex == nullptr) 
	{
		printf("Create Texture Error: %s\n", SDL_GetError());
		return tex;
	}

	//free the surface since only the texture is needed
	SDL_FreeSurface(surface);

	return tex;
}

SDL_Texture* Graphics::CreateTextTexture(TTF_Font* font, std::string text, SDL_Color color) 
{
	//Render the text onto a surface using the provided font and color
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
	//Handling font rendering errors
	if (surface == nullptr) 
	{
		printf("Text Render Error: %s\n", TTF_GetError());
		return nullptr;
	}

	//Converting the surface into a texture to be able to render it using the renderer
	SDL_Texture* tex = SDL_CreateTextureFromSurface(mRenderer, surface);
	//Handle texture creation errors
	if (tex == nullptr) 
	{
		printf("Text Texture Creation Error: %s\n", SDL_GetError());
		return nullptr;
	}

	//free the surface since only the texture is needed
	SDL_FreeSurface(surface);

	return tex;
}

void Graphics::ClearBackBuffer() 
{
	SDL_RenderClear(mRenderer);
}

void Graphics::DrawTexture(SDL_Texture* tex, SDL_Rect* clip, SDL_Rect* rend, float angle, SDL_RendererFlip flip) 
{
	SDL_RenderCopyEx(mRenderer, tex, clip, rend, angle, NULL, flip);
}

void Graphics::Render() 
{
	SDL_RenderPresent(mRenderer);
}