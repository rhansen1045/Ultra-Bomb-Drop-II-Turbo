bomb: source/Level.cpp source/Level.h source/LevelTest.cpp
	g++ -o bomb source/Level.cpp source/LevelTest.cpp -Wall -I. -I/Library/Frameworks/SDL.framework/Headers -lSDLmain -lSDL -lSDL_image -framework Cocoa
