// Introduction lab that covers:
// * C++
// * SDL
// * 2D graphics
// * Plotting pixels
// * Video memory
// * Color representation
// * Linear interpolation
// * glm::vec3 and std::vector

#include "SDL.h"
#include <iostream>
#include <glm/glm.hpp>
#include <vector>
#include "SDLauxiliary.h"

using namespace std;
using glm::vec3;

// --------------------------------------------------------
// GLOBAL VARIABLES

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Surface* screen;

// --------------------------------------------------------
// FUNCTION DECLARATIONS

void Draw();

void Interpolate( vec3 a, vec3 b, vector<vec3>& result );
// --------------------------------------------------------
// FUNCTION DEFINITIONS

int main( int argc, char* argv[] )
{
	screen = InitializeSDL( SCREEN_WIDTH, SCREEN_HEIGHT );

	while( NoQuitMessageSDL() )
	{
		Draw();
	}
	SDL_SaveBMP( screen, "screenshot.bmp" );
	return 0;
}

void Draw()
{	
	vec3 topLeft(1,0,0); // red
	vec3 topRight(0,0,1); // blue
	vec3 bottomLeft(1,1,0); // yellow
	vec3 bottomRight(0,1,0); // green
	vector<vec3> leftSide( SCREEN_HEIGHT );
	vector<vec3> rightSide( SCREEN_HEIGHT );
	Interpolate( topLeft, bottomLeft, leftSide );
	Interpolate( topRight, bottomRight, rightSide );
	for( int y=0; y<SCREEN_HEIGHT; ++y )
	{

		vector<vec3> row(SCREEN_WIDTH);
		Interpolate(leftSide[y], rightSide[y], row);
		for( int x=0; x<SCREEN_WIDTH; ++x )
		{
			PutPixelSDL( screen, x, y, row[x] );
		}
	}

	if( SDL_MUSTLOCK(screen) )
		SDL_UnlockSurface(screen);

	SDL_UpdateRect( screen, 0, 0, 0, 0 );
}

void Interpolate( vec3 a, vec3 b, vector<vec3>& result){


	int size = result.size();

	if(size == 1){
		result[0] = a;
		return;
	}

	float r_step = (b.x-a.x)/(size-1);
	float g_step = (b.y-a.y)/(size-1);
	float b_step = (b.z-a.z)/(size-1);

	for(int i = 0; i<size; i++){
		result[i].x = a.x + r_step*i;
		result[i].y = a.y + g_step*i;
		result[i].z = a.z + b_step*i;
	}

}