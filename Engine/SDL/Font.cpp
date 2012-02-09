#include "Font.h"
#include "../ErrorHandler.h"
#include "SDL_SurfacePtr.h"
#include <vector>
#include <cassert>
#include <boost/algorithm/string.hpp>
Font::Font()
{
    m_pFont = NULL;
    m_Color.r = 0;
    m_Color.g = 0;
    m_Color.b = 0;
    m_iLineSpacing = 2;
}

Font::Font(const std::string & fileName, int size)
{
    m_pFont = NULL;
    m_Color.r = 0;
    m_Color.g = 0;
    m_Color.b = 0;
    m_iLineSpacing = 2;

    load(fileName, size);
}

Font::~Font()
{
    if( m_pFont != NULL )
        TTF_CloseFont(m_pFont);
}

void Font::load(const std::string & fileName, int size)
{
    if( m_pFont != NULL )
        TTF_CloseFont(m_pFont);

    m_pFont = TTF_OpenFont(fileName.c_str(), size);
    if( m_pFont == NULL )
        G_THROW("Font couldn't be opened - " + fileName);
}

//Rendering
SDL_Surface * Font::render_Solid(const std::string & text)
{
    return render_Solid(text, m_Color);
}
SDL_Surface * Font::render_Shaded(const std::string & text)
{
    return render_Shaded(text, m_Color);
}
SDL_Surface * Font::render_Blended(const std::string & text)
{
    return render_Blended(text, m_Color);
}

SDL_Surface * Font::render_Solid(const std::string & text, const SDL_Color & c)
{
    return render_ml(text, c, type_solid);
}

SDL_Surface * Font::render_Shaded(const std::string & text, const SDL_Color & c)
{
    return render_ml(text, c, type_shaded);
}
SDL_Surface * Font::render_Blended(const std::string & text, const SDL_Color & c)
{
    return render_ml(text, c, type_blended);
}

SDL_Surface * Font::render_sl(const std::string & text, const SDL_Color & c, type t)
{
    SDL_Surface * pImage;
    switch( t )
    {
    case type_solid :
        pImage = TTF_RenderText_Solid(m_pFont, text.c_str(), c);
        break;
    case type_shaded :
        assert(!"Shaded text not implemented !!");
        //pImage = TTF_RenderText_Shaded(m_pFont, text.c_str(), c);
        break;
    case type_blended :
        pImage = TTF_RenderText_Blended(m_pFont, text.c_str(), c);
        break;
    }
    return pImage;
}


SDL_Surface * Font::render_ml(const std::string & text, const SDL_Color & c, type t)
{
    std::vector<std::string> list;
    boost::split( list, text, boost::is_any_of("\n") );
    std::for_each(list.begin(), list.end(), std::mem_fun_ref(&std::string::empty) );

    //For single line
    if( list.size() == 1 )
        return render_sl(list[0], c, t);

    //For multiline

    //Get the total height and max width;
    int w=0,h=0;
    for(unsigned int i=0; i<list.size(); i++)
    {
        int a,b;
        TTF_SizeText( m_pFont, list[i].c_str(), &a, &b );
        h += b + m_iLineSpacing;
        if( a > w ) w = a;
    }

    //Create the surface and render the text on it
    SDL_Surface * surf = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32,0xFF000000,
                                        0x00FF0000, 0x0000FF00, 0x000000FF);
    SDL_Rect r;
    r.x = 0;
    r.y = 0;
    for(unsigned int i=0; i<list.size(); i++)
    {
        SDL_SurfacePtr temp = render_sl(list[i], c, t );
        temp->flags &= !SDL_SRCALPHA; // this is done because of how SDL_Blit Surface works.

        SDL_BlitSurface( temp.get(), NULL, surf, &r);
        r.y += temp->h + m_iLineSpacing;
    }
    return surf;
}


