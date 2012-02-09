#ifndef _GLTEX_H
#define _GLTEX_H

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <SDL/SDL_image.h>
#include <string>

class glTex {
private :
    GLuint m_Data;
    unsigned int m_iWidth;
    unsigned int m_iHeight;

    unsigned int m_iActualWidth;
    unsigned int m_iActualHeight;

public :
    glTex();
    glTex(const std::string & fileName);
    glTex(SDL_Surface * surface);
    ~glTex();

    void load(const std::string & fileName);
    void load(SDL_Surface * surf);

    void render(float x, float y) const;
    void renderi(float x, float y) const;

    unsigned int w() const { return m_iWidth; }
    unsigned int h() const { return m_iHeight; }

    unsigned int aw() const { return m_iActualWidth; }
    unsigned int ah() const { return m_iActualHeight; }
};

//Misc functions
SDL_Surface * convertSurface(SDL_Surface * surface);

#endif
