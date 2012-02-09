#include "glTex.h"
#include "../SDL/SDL_SurfacePtr.h"

glTex::glTex()
{
    m_Data = 0;
    m_iHeight = 0;
    m_iWidth = 0;

    m_iActualHeight = 0;
    m_iActualWidth = 0;
}

glTex::glTex(const std::string & fileName)
{
    load(fileName);
}

glTex::glTex(SDL_Surface * surface)
{
    load(surface);
}

glTex::~glTex()
{
    glDeleteTextures(1, &m_Data);
}

void glTex::load(const std::string & fileName)
{
    SDL_SurfacePtr surf = load_image(fileName.c_str());
    load(surf.get());
}

void glTex::load(SDL_Surface * surface)
{
    //Remove existing texture
    //if( m_Data != 0 )
    //    glDeleteTextures(1, &m_Data);

    SDL_SurfacePtr image = convertSurface(surface);

    m_iWidth = surface->w;
    m_iHeight = surface->h;

    m_iActualWidth = image->w;
    m_iActualHeight = image->h;

    // Create an OpenGL texture for the image
    glGenTextures(1, &m_Data);
    glBindTexture(GL_TEXTURE_2D, m_Data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D,
             0,
             GL_RGBA,
             image->w, image->h,
             0,
             GL_RGBA,
             GL_UNSIGNED_BYTE,
             image->pixels);
    return;
}

void glTex::renderi(float x, float y) const
{
    glBindTexture( GL_TEXTURE_2D, m_Data );

    //glRotatef(0, 0.0, 0.00, 1.0f);
    glTranslatef(x, y, 0.0f);
    //glScalef(1.0, 1.0, 1.0);

    glBegin(GL_QUADS);

        glTexCoord2f(0,0);
        glVertex3f( 0, 0, 0 );

        glTexCoord2f( 1.0, 0);
        glVertex3f( aw(), 0, 0 );

        glTexCoord2f( 1.0, 1.0);
        glVertex3f( aw(), ah(), 0 );

        glTexCoord2f(0, 1.0);
        glVertex3f( 0, ah(), 0 );
    glEnd();
}

void glTex::render(float x, float y) const
{
    glPushMatrix();
    glLoadIdentity();

    renderi(x,y);

    glPopMatrix();
}

//Converting normal surface into a surface of the power of two.
int power_of_two(int input)
{
    int value = 1;
    while ( value < input )
        value <<= 1;
    return value;
}

SDL_Surface * convertSurface(SDL_Surface * surface)
{
    SDL_Surface * pImage;

    /* Use the surface width and height expanded to powers of 2 */
    int w = power_of_two(surface->w);
    int h = power_of_two(surface->h);

    pImage = SDL_CreateRGBSurface(
            SDL_SWSURFACE,
            w, h,
            32,
#if SDL_BYTEORDER == SDL_LIL_ENDIAN /* OpenGL RGBA masks */
            0x000000FF,
            0x0000FF00,
            0x00FF0000,
            0xFF000000
#else
            0xFF000000,
            0x00FF0000,
            0x0000FF00,
            0x000000FF
#endif
            );

    // Save the alpha blending attributes
    Uint32 saved_flags;
    Uint8  saved_alpha;
    saved_flags = surface->flags & (SDL_SRCALPHA|SDL_RLEACCELOK);
    saved_alpha = surface->format->alpha;
    if ( (saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA ) {
        SDL_SetAlpha(surface, 0, 0);
    }

    /* Copy the surface into the GL texture image */
    SDL_Rect area;
    area.x = 0;
    area.y = 0;
    area.w = surface->w;
    area.h = surface->h;
    SDL_BlitSurface(surface, &area, pImage, &area);

    // Restore the alpha blending attributes
    if ( (saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA ) {
        SDL_SetAlpha(surface, saved_flags, saved_alpha);
    }
    return pImage;
}
