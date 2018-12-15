main:main.cpp glad/glad.c Player.cpp Model.cpp ModelImporter.cpp Utils.cpp Skybox.cpp Collision.cpp Animation.cpp
	g++ -std=c++11 main.cpp glad/glad.c Player.cpp Model.cpp ModelImporter.cpp Game.cpp TextRenderer.cpp Utils.cpp Skybox.cpp Collision.cpp Animation.cpp -o game -lSDL2 -lSDL2main -lSDL2_ttf -lSDL2_mixer -I/usr/local/Cellar/sdl2/2.0.8/include/SDL2/ -I/usr/local/Cellar/sdl2_ttf/2.0.14/include/SDL2/ -I/usr/local/Cellar/sdl2_mixer/2.0.4/include/SDL2/ -framework OpenGL

clean:
	rm game