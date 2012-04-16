#include <SDL/SDL.h>
#include <SDL_image/SDL_image.h>

#include <stdio.h>
#include <string>


#include "Level.h"

using namespace std;

//The surfaces
SDL_Surface *dots = NULL;
SDL_Surface *screen = NULL;

//The event structure
SDL_Event event;

//The portions of the sprite map to be blitted
SDL_Rect clip[ 4 ];

SDL_Surface *load_image( std::string filename )
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;
    
    //The optimized surface that will be used
    SDL_Surface* optimizedImage = NULL;
    
    //Load the image
    loadedImage = IMG_Load( filename.c_str() );
    
    //If the image loaded
    if( loadedImage != NULL )
    {
        //Create an optimized surface
        optimizedImage = SDL_DisplayFormat( loadedImage );
        
        //Free the old surface
        SDL_FreeSurface( loadedImage );
        
        //If the surface was optimized
        if( optimizedImage != NULL )
        {
            //Color key surface
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
        }
    }
    
    //Return the optimized surface
    return optimizedImage;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    //Holds offsets
    SDL_Rect offset;
    
    //Get offsets
    offset.x = x;
    offset.y = y;
    
    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}


//Screen attributes
const int SCREEN_WIDTH = 176;
const int SCREEN_HEIGHT = 176;
const int SCREEN_BPP = 32;

bool load_files()
{
    //Load the sprite map
    dots = load_image( "media/tiles1.png" );
    
    //If there was an problem loading the sprite map
    if( dots == NULL )
    {
        return false;
    }
    
    //If eveything loaded fine
    return true;
}

bool quit = false;
void clean_up()
{
    //Free the sprite map
    SDL_FreeSurface( dots );
    
    //Quit SDL
    SDL_Quit();
}

int main( int argc, char* args[] ) {
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }
    
    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
    
    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        return false;
    }
    
    //Set the window caption
    SDL_WM_SetCaption( "Split the dots", NULL );
    
    load_files();
    
    //Clip range for the top left
    clip[ 0 ].x = 0;
    clip[ 0 ].y = 0;
    clip[ 0 ].w = 16;
    clip[ 0 ].h = 16;
    
    //Clip range for the top right
    clip[ 1 ].x = 0;
    clip[ 1 ].y = 16;
    clip[ 1 ].w = 16;
    clip[ 1 ].h = 16;
    
    //Clip range for the bottom left
    clip[ 2 ].x = 0;
    clip[ 2 ].y = 32;
    clip[ 2 ].w = 16;
    clip[ 2 ].h = 16;
    
    /*
    //Clip range for the bottom right
    clip[ 3 ].x = 0;
    clip[ 3 ].y = 48;
    clip[ 3 ].w = 16;
    clip[ 3 ].h = 16;
    */

    SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
    
    //Apply the sprites to the screen
    /*
    apply_surface( 0, 0, dots, screen, &clip[ 0 ] );
    apply_surface( 540, 0, dots, screen, &clip[ 1 ] );
    apply_surface( 0, 380, dots, screen, &clip[ 2 ] );
    apply_surface( 540, 380, dots, screen, &clip[ 3 ] );
    */
    Level* lvl = new Level();
    
    lvl->generate();
    
    
    for(int i = 0; i < LEVEL_ROW; ++i) {
        for(int j = 0; j < LEVEL_COL; ++j) {
            Tile tile = lvl->get_tile(j, i);
            if(tile == GROUND) {
                apply_surface( i*16, j*16, dots, screen, &clip[ 2 ] );

                printf("o");
            } else if(tile == SOLID) {
                apply_surface( i*16, j*16, dots, screen, &clip[ 0 ] );

                printf("*");
            } else if(tile == BREAK) {
                apply_surface( i*16, j*16, dots, screen, &clip[ 1 ] );

                printf("B");
            }
        }
        printf("\n");
    }
    
    SDL_Flip( screen);
    
    //While the user hasn't quit
    while( quit == false )
    {
        //While there's events to handle
        while( SDL_PollEvent( &event ) )
        {
            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
        }
    }
    
    //Free the images and quit SDL
    clean_up();
    
    return 0;
    
}