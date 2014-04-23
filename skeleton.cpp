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
int t;
vector<vec3> stars( 1000 );
SDL_Surface* screen;

// --------------------------------------------------------
// FUNCTION DECLARATIONS

void Draw();
void Update();
void Interpolate( vec3 a, vec3 b, vector<vec3>& result );
// --------------------------------------------------------
// FUNCTION DEFINITIONS

int main( int argc, char* argv[] )
{	
	t = SDL_GetTicks();
	screen = InitializeSDL( SCREEN_WIDTH, SCREEN_HEIGHT );
	for(int i = 0; i<stars.size(); i++){
		stars[i].x = float(rand()) / float(RAND_MAX) * (1-(-1)) -1;
		stars[i].y = float(rand()) / float(RAND_MAX) * (1-(-1)) -1;
		stars[i].z = float(rand()) / float(RAND_MAX);
	}
	while( NoQuitMessageSDL() )
	{
		Update();
		Draw();
	}
	SDL_SaveBMP( screen, "screenshot.bmp" );
	return 0;
}

void Draw()
{	
	SDL_FillRect( screen, 0, 0 );

	if( SDL_MUSTLOCK(screen) )
	SDL_LockSurface(screen);
	vec3 white(1, 1, 1);
	for( size_t s=0; s<stars.size(); ++s )
		{	
			float f = SCREEN_HEIGHT/2;
			float u = f*(stars[s].x/stars[s].z) + SCREEN_HEIGHT/2;
			float v = f*(stars[s].y/stars[s].z) + SCREEN_HEIGHT/2;
			PutPixelSDL( screen, u, v, white );
		}
	if( SDL_MUSTLOCK(screen) )
	SDL_UnlockSurface(screen);
	SDL_UpdateRect( screen, 0, 0, 0, 0 );
}

void Update(){
	int t2 = SDL_GetTicks();
	float dt = float(t2-t);
	t = t2;
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