bomb: source/Level.cpp source/Level.h source/main.cpp
	g++ -o bomb source/Level.cpp source/main.cpp -Wall -I. -I/Library/Frameworks/SDL.framework/Headers -lSDLmain -lSDL -lSDL_image -framework Cocoa
