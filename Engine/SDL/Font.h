#ifndef FONT_H
#define FONT_H

#include <SDL/SDL_ttf.h>
#include <string>

class Font
{
private:
    TTF_Font * m_pFont;
    SDL_Color m_Color;
    int m_iLineSpacing;

    enum type {
        type_solid=0,
        type_shaded=1,
        type_blended=2
    };

    SDL_Surface * render_ml(const std::string & text, const SDL_Color & c, type t);
    SDL_Surface * render_sl(const std::string & text, const SDL_Color & c, type t);
public:
    Font();
    Font(const std::string & fileName, int size);
    virtual ~Font();

    void load(const std::string & fileName, int size);

    //Rendering
    SDL_Surface * render_Solid(const std::string & text);
    SDL_Surface * render_Shaded(const std::string & text);
    SDL_Surface * render_Blended(const std::string & text);
    SDL_Surface * render_Solid(const std::string & text, const SDL_Color & c);
    SDL_Surface * render_Shaded(const std::string & text, const SDL_Color & c);
    SDL_Surface * render_Blended(const std::string & text, const SDL_Color & c);

    //Set
    void setLineSpacing( int space ) { m_iLineSpacing = space; }
    void setDefaultColor(const SDL_Color & c) { m_Color = c;}
};

#endif // FONT_H
