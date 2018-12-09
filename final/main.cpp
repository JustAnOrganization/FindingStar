
#include "Game.h"
#include "Basic.h"
#include "Player.h"
#include "TextRenderer.h"

//some code is based on Multi-Object, Multi-Texture Example by Stephen J. Guy, 2018

const char* INSTRUCTIONS = 
"***************\n"
"Final Project.\n"
"\n"
"Up/down/left/right - Moves.\n"
"***************\n";

int screenWidth = 800;
int screenHeight = 600;
float timePast = 0;
float lastTime = 0;

bool fullscreen = false;

float rand01(){
	return rand()/(float)RAND_MAX;
}

int main(int argc, char *argv[]){
	SDL_Init(SDL_INIT_VIDEO);  //Initialize Graphics (for OpenGL)

	//Ask SDL to get a recent version of OpenGL (3.2 or greater)
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	//Create a window (offsetx, offsety, width, height, flags)
	SDL_Window* window = SDL_CreateWindow("Game Game", 100, 100, screenWidth, screenHeight, SDL_WINDOW_OPENGL);

	//Create a context to draw in
	SDL_GLContext context = SDL_GL_CreateContext(window);

	//Load OpenGL extentions with GLAD
	if (gladLoadGLLoader(SDL_GL_GetProcAddress)){
		printf("\nOpenGL loaded\n");
		printf("Vendor:   %s\n", glGetString(GL_VENDOR));
		printf("Renderer: %s\n", glGetString(GL_RENDERER));
		printf("Version:  %s\n\n", glGetString(GL_VERSION));
	}
	else {
		printf("ERROR: Failed to initialize OpenGL context.\n");
		return -1;
	}

	TextRenderer textRenderer;
	textRenderer.init();

    Game game(screenWidth, screenHeight);
    game.initialize();
	
	//Event Loop (Loop forever processing each event as fast as possible)
	SDL_Event windowEvent;
	SDL_SetHintWithPriority(SDL_HINT_MOUSE_RELATIVE_MODE_WARP, "1", SDL_HINT_OVERRIDE);
	SDL_SetRelativeMouseMode(SDL_TRUE);

	bool quit = false;
	while (!quit){
        //deltaTime
        lastTime = timePast;
        timePast = SDL_GetTicks() / 1000.f;
        float deltaTime = timePast - lastTime;

		while (SDL_PollEvent(&windowEvent))
        {  //inspect all events in the queue
            if (windowEvent.type == SDL_QUIT) quit = true;
            //List of keycodes: https://wiki.libsdl.org/SDL_Keycode - You can catch many special keys
            //Scancode referes to a keyboard position, keycode referes to the letter (e.g., EU keyboards)
            if (windowEvent.type == SDL_KEYUP && windowEvent.key.keysym.sym == SDLK_ESCAPE)
                quit = true; //Exit event loop
            if (windowEvent.type == SDL_KEYUP && windowEvent.key.keysym.sym == SDLK_f)
            { //If "f" is pressed
                fullscreen = !fullscreen;
                SDL_SetWindowFullscreen(window, fullscreen ? SDL_WINDOW_FULLSCREEN : 0); //Toggle fullscreen
            }
            game.player.processEvent(windowEvent, deltaTime);
        }

		// Clear the screen to default color
		glClearColor(.2f, 0.4f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		game.update(deltaTime);

		//subtitle
		textRenderer.renderText("To Be Continued.. :)", 25.0f, 25.0f, 1, glm::vec3(1, 1, 1));

		SDL_GL_SwapWindow(window); // Double buffering
	}

    //Clean up
    TTF_Quit();
    SDL_DestroyWindow(window);
	SDL_GL_DeleteContext(context);
	SDL_Quit();
	return 0;
}
