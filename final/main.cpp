
#include "Basic.h"
#include "Game.h"
#include "Player.h"
#include "TextRenderer.h"

//some code is based on Multi-Object, Multi-Texture Example by Stephen J. Guy, 2018

const char* INSTRUCTIONS = 
"***************\n"
"Final Project.\n"
"\n"
"Up/down/left/right - Moves.\n"
"***************\n";

std::string intro_text_1 = "Hello, My Friend: There is not much time left for me in this world.";
std::string intro_text_2 = "Don't be sad. I'm an old man now. ";
std::string intro_text_3 = "There is one last thing I ask from you: Please find my star.";
std::string intro_text_4 = "It's somewhere in my home. ";

int screenWidth = 800;
int screenHeight = 600;
float timePast = 0;
float lastTime = 0;

bool fullscreen = false;

//float rand01(){
//	return rand()/(float)RAND_MAX;
//}

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);
	Mix_Music *music = Mix_LoadMUS("audio/Saturn.mp3");
	Mix_PlayMusic(music, -1);

	if (MIX_INIT_MP3 != (Mix_Init(MIX_INIT_MP3))) {
		printf("mix init error: %s\n", Mix_GetError());
		return -1;
	}
	//Mix_Chunk *effect = NULL;
	//effect = Mix_LoadWAV( "effect.wav" );
	//Mix_PlayChannel( -1, effect, 0 );
//	if( Mix_PausedMusic() == 1 )
//	{
//		Mix_ResumeMusic();
//	}
//	else
//	{
//		Mix_PauseMusic();
//	}
//	Mix_HaltMusic();

	//Ask SDL to get a recent version of OpenGL (3.2 or greater)
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	//Create a window (offsetx, offsety, width, height, flags)
	SDL_Window* window = SDL_CreateWindow("Finding Star", 100, 100, screenWidth, screenHeight, SDL_WINDOW_OPENGL);

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

	//init screen start
	while (!quit)
	{
		bool next = false;
		while (SDL_PollEvent(&windowEvent))
		{
            if (windowEvent.type == SDL_QUIT || (windowEvent.type == SDL_KEYDOWN && windowEvent.key.keysym.sym == SDLK_ESCAPE)) quit = true;
			if (windowEvent.type == SDL_KEYDOWN && windowEvent.key.keysym.sym == SDLK_SPACE)
			{
				next = true;
			}
		}
        glClearColor(0, 0, 0, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        textRenderer.renderText("Finding Star", screenWidth/2.0f - 120, screenHeight/ 1.5f, 1.2, glm::vec3(1, 1, 1));
		textRenderer.renderText(intro_text_1, screenWidth / 2.0f - 250, screenHeight / 2.f, 0.5, glm::vec3(1, 1, 1));
		textRenderer.renderText(intro_text_2, screenWidth / 2.0f - 120, screenHeight / 2.2f, 0.5, glm::vec3(1, 1, 1));
		textRenderer.renderText(intro_text_3, screenWidth / 2.0f - 250, screenHeight / 2.4f, 0.5, glm::vec3(1, 1, 1));
		textRenderer.renderText(intro_text_4, screenWidth / 2.0f - 100, screenHeight / 2.8f, 0.5, glm::vec3(1, 1, 1));
        textRenderer.renderText("press space to start.", screenWidth/2.0f - 150, screenHeight/4.0f, 1, glm::vec3(0.8, 0.8, 1));
		if (next)
			break;
        SDL_GL_SwapWindow(window);
	}
	//init screen end

    //reference: https://learnopengl.com/Advanced-Lighting/Shadows/Shadow-Mapping
	//shadow init start
//    const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
//    unsigned int depthMapFBO;
//    glGenFramebuffers(1, &depthMapFBO);
//    // create depth texture
//    unsigned int depthMap;
//    glGenTextures(1, &depthMap);
//    glBindTexture(GL_TEXTURE_2D, depthMap);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
//    float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
//    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
//    // attach depth texture as FBO's depth buffer
//    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
//    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
//    glDrawBuffer(GL_NONE);
//    glReadBuffer(GL_NONE);
//    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    //shadow init end


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
            if (windowEvent.type == SDL_KEYDOWN && windowEvent.key.keysym.sym == SDLK_ESCAPE)
                quit = true; //Exit event loop
//            if (windowEvent.type == SDL_KEYDOWN && windowEvent.key.keysym.sym == SDLK_f)
//            { //If "f" is pressed
//                fullscreen = !fullscreen;
//                SDL_SetWindowFullscreen(window, fullscreen ? SDL_WINDOW_FULLSCREEN : 0); //Toggle fullscreen
//            }
            game.player.processEvent(windowEvent, deltaTime);
        }

		// Clear the screen to default color
		glClearColor(.2f, 0.4f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		game.update(deltaTime);

//shadow begin
//        glm::mat4 lightProjection, lightView;
//        glm::mat4 lightSpaceMatrix;
//        float near_plane = 1.0f, far_plane = 7.5f;
//        //lightProjection = glm::perspective(glm::radians(45.0f), (GLfloat)SHADOW_WIDTH / (GLfloat)SHADOW_HEIGHT, near_plane, far_plane); // note that if you use a perspective projection matrix you'll have to change the light position as the current light position isn't enough to reflect the whole scene
//        lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
//        lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
//        lightSpaceMatrix = lightProjection * lightView;
//        // render scene from light's point of view
//        simpleDepthShader.use();
//        simpleDepthShader.setMat4("lightSpaceMatrix", lightSpaceMatrix);
//
//        glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
//        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
//        glClear(GL_DEPTH_BUFFER_BIT);
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, woodTexture);
//        renderScene(simpleDepthShader);
//        glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//        // reset viewport
//        glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//shadow end

		game.draw();

		if (game.win())
        {
            textRenderer.renderText("The End.", screenWidth/2.0f - 80, screenHeight/2.0f, 1.2, glm::vec3(0.8, 1, 0.8));
        }
        else
        {
			textRenderer.renderText(".", screenWidth/2.0f, screenHeight/2.0f, 1, glm::vec3(1, 1, 1));
		}

		SDL_GL_SwapWindow(window); // Double buffering
	}

    //Clean up
    TTF_Quit();
    SDL_DestroyWindow(window);
	SDL_GL_DeleteContext(context);

	//Mix_FreeChunk( effect );
	Mix_FreeMusic( music );
	Mix_CloseAudio();

	SDL_Quit();
	return 0;
}
