#ifndef GRID_H
#define GRID_H

#include <memory>
#include "Engine/GL/glTex.h"
#include <boost/ptr_container/ptr_vector.hpp>

class Grid
{
private:
    std::auto_ptr<glTex> m_pBlack;
    std::auto_ptr<glTex> m_pWhite;

    static const int grid_white = 0;
    static const int grid_black = 1;

    std::vector< std::vector<int> > m_grid;
    SDL_Rect m_Rect;
    SDL_Surface * createSurface(int insideColor, int outsideColor);
public:

    static const int width = 7;
    static const int height = 10;

    Grid();
    virtual ~Grid();

    void init();
    void deinit();

    void render();
    void update(float timeElapsed);

    void setDigit(int d);
    void getInput(std::vector<float> & input);
    void addNoise(int n);
    void setPos(int x, int y) { m_Rect.x = x; m_Rect.y = y; }
};

#endif // GRID_H
