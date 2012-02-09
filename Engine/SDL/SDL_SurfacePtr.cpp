#include "../ErrorHandler.h"
#include "SDL_SurfacePtr.h"
#include <cassert>

SDL_SurfacePtr::SDL_SurfacePtr()
: ptr(NULL)
{}

SDL_SurfacePtr::SDL_SurfacePtr(SDL_Surface * surface)
: ptr(surface)
{}

SDL_SurfacePtr::SDL_SurfacePtr(const SDL_SurfacePtr & rhs)
{
    ptr = NULL;
    *this = rhs;
}

SDL_SurfacePtr::~SDL_SurfacePtr()
{
	SDL_FreeSurface( ptr );
}

bool operator ==(const SDL_SurfacePtr & lhs, const SDL_SurfacePtr & rhs)
{ return lhs.get() == rhs.get(); }

bool operator !=(const SDL_SurfacePtr & lhs, const SDL_SurfacePtr & rhs)
{ return lhs.get() != rhs.get(); }

//
// Load Image
//
SDL_Surface *load_image(const std::string & filename)
{
    SDL_Surface* loadedImage = NULL;

    SDL_Surface* optimizedImage = NULL;

    //Load the image
    loadedImage = IMG_Load( filename.c_str() );
    if(loadedImage == NULL)
        G_THROW(filename + " couldn't be loaded");

    //If the image loaded
    if( loadedImage != NULL )
    {
        //Create an optimized surface
        optimizedImage = SDL_DisplayFormatAlpha( loadedImage );
        if(optimizedImage == NULL)
            G_THROW("ImageFile " + filename + " couldn't be converted");
        //Free the old surface
        SDL_FreeSurface( loadedImage );
    }

    return optimizedImage;
}
