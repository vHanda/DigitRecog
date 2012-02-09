#include "Grid.h"
#include <algorithm>
#include "Engine/SDL/SDL_SurfacePtr.h"
#include <iostream>

Grid::Grid()
{
    //ctor
}

Grid::~Grid()
{
    //dtor
}

void Grid::init()
{
    //Create black and white images
    SDL_SurfacePtr pBlack = createSurface( 0x000000FF, 0x000000FF );
    m_pBlack = std::auto_ptr<glTex>( new glTex(pBlack.get()) );

    SDL_SurfacePtr pWhite = createSurface( 0xFFFFFFFF, 0x00000080 );
    m_pWhite = std::auto_ptr<glTex>( new glTex(pWhite.get()) );

    //Fill grid with white
    m_grid.resize(height, std::vector<int>(width, grid_white) );
}

void Grid::deinit()
{
}

void Grid::render()
{
    int x=0;
    int y=0;
    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
            glLoadIdentity();
            glTranslatef(m_Rect.x, m_Rect.y, 0.0f);

            if( m_grid[i][j] == grid_black )
                m_pBlack->renderi(x, y);
            else
                m_pWhite->renderi(x,y);

            x += m_pBlack->w();
            //std::cout << x << " " << y << std::endl;
        }
        x = 0;
        y += m_pBlack->h();
    }
}

void Grid::update(float timeElapsed)
{
}

SDL_Surface * Grid::createSurface(int insideColor, int outsideColor)
{
    int w = 30;
    int h = 30;

    SDL_Surface * pSurf = SDL_CreateRGBSurface(
                            SDL_SWSURFACE,
                            w, h,
                            32,
                            0xFF000000,
                            0x00FF0000,
                            0x0000FF00,
                            0x000000FF
                            );
    assert(pSurf != NULL);
    SDL_FillRect( pSurf, NULL, outsideColor );

    float ratio = .05;
    int innerW = w * ratio;
    int innerH = h * ratio;
    SDL_Rect r = {innerW, innerH , w-(innerW*2), h-(innerH*2)};
    SDL_FillRect( pSurf, &r, insideColor );

    return pSurf;
}

void Grid::getInput(std::vector<float> & input)
{
    input.resize( height * width );
    for(int i=0; i<height; i++)
        for(int j=0; j<width; j++)
            input[i*width + j] = m_grid[i][j];
}

void Grid::addNoise(int n)
{
    for(unsigned int i=0; i<m_grid.size(); i++)
        for(unsigned int j=0; j<m_grid[0].size(); j++)
        {
            if( rand() % 100 < n )
                m_grid[i][j] = grid_black;
        }
}
void Grid::setDigit(int d)
{

    if( d < 0 || d > 9 )
        return;

    switch( d )
    {
    case 0 :
    {
        int line[height][width] =
        { { 0, 1, 1, 1, 1, 1, 0 },
          { 1, 1, 0, 0, 0, 1, 1 },
          { 1, 0, 0, 0, 0, 0, 1 },
          { 1, 0, 0, 0, 0, 0, 1 },
          { 1, 0, 0, 0, 0, 0, 1 },
          { 1, 0, 0, 0, 0, 0, 1 },
          { 1, 0, 0, 0, 0, 0, 1 },
          { 1, 0, 0, 0, 0, 0, 1 },
          { 1, 1, 0, 0, 0, 1, 1 },
          { 0, 1, 1, 1, 1, 1, 0 }, };
        for(int i=0; i<height; i++)
            m_grid[i] = std::vector<int>( line[i], line[i]+width );
        return;
    }
    case 1 :
    {
        int line[height][width] =
        { { 0, 0, 0, 1, 0, 0, 0 },
          { 0, 0, 1, 1, 0, 0, 0 },
          { 0, 1, 0, 1, 0, 0, 0 },
          { 0, 0, 0, 1, 0, 0, 0 },
          { 0, 0, 0, 1, 0, 0, 0 },
          { 0, 0, 0, 1, 0, 0, 0 },
          { 0, 0, 0, 1, 0, 0, 0 },
          { 0, 0, 0, 1, 0, 0, 0 },
          { 0, 0, 0, 1, 0, 0, 0 },
          { 1, 1, 1, 1, 1, 1, 1 }, };
        for(int i=0; i<height; i++)
            m_grid[i] = std::vector<int>( line[i], line[i]+width );
        return;
    }
    case 2 :
    {
        int line[height][width] =
        { { 0, 0, 1, 1, 0, 0, 0 },
          { 0, 1, 0, 0, 1, 0, 0 },
          { 1, 0, 0, 0, 0, 1, 0 },
          { 0, 0, 0, 0, 0, 0, 1 },
          { 0, 0, 0, 0, 0, 1, 0 },
          { 0, 0, 0, 0, 1, 0, 0 },
          { 0, 0, 0, 1, 0, 0, 0 },
          { 0, 0, 1, 0, 0, 0, 0 },
          { 0, 1, 0, 0, 0, 0, 0 },
          { 1, 1, 1, 1, 1, 1, 1 }, };
        for(int i=0; i<height; i++)
            m_grid[i] = std::vector<int>( line[i], line[i]+width );
        return;
    }
    case 3 :
    {
        int line[height][width] =
        { { 0, 0, 1, 1, 1, 0, 0 },
          { 0, 1, 0, 0, 0, 1, 0 },
          { 1, 0, 0, 0, 0, 0, 1 },
          { 0, 0, 0, 0, 0, 0, 1 },
          { 0, 0, 1, 1, 1, 1, 0 },
          { 0, 0, 0, 0, 0, 1, 0 },
          { 0, 0, 0, 0, 0, 0, 1 },
          { 1, 0, 0, 0, 0, 0, 1 },
          { 0, 1, 0, 0, 0, 1, 0 },
          { 0, 0, 1, 1, 1, 0, 0 }, };
        for(int i=0; i<height; i++)
            m_grid[i] = std::vector<int>( line[i], line[i]+width );
        return;
    }
    case 4 :
    {
        int line[height][width] =
        { { 0, 0, 0, 0, 1, 0, 0 },
          { 0, 0, 0, 1, 1, 0, 0 },
          { 0, 0, 1, 0, 1, 0, 0 },
          { 0, 1, 0, 0, 1, 0, 0 },
          { 1, 0, 0, 0, 1, 0, 0 },
          { 1, 1, 1, 1, 1, 1, 1 },
          { 0, 0, 0, 0, 1, 0, 0 },
          { 0, 0, 0, 0, 1, 0, 0 },
          { 0, 0, 0, 0, 1, 0, 0 },
          { 0, 0, 0, 0, 1, 0, 0 }, };
        for(int i=0; i<height; i++)
            m_grid[i] = std::vector<int>( line[i], line[i]+width );
        return;
    }
    case 5 :
    {
        int line[height][width] =
        { { 1, 1, 1, 1, 1, 1, 0 },
          { 1, 0, 0, 0, 0, 0, 0 },
          { 1, 0, 0, 0, 0, 0, 0 },
          { 1, 0, 0, 0, 0, 0, 0 },
          { 1, 1, 1, 1, 0, 0, 0 },
          { 0, 0, 0, 0, 1, 0, 0 },
          { 0, 0, 0, 0, 0, 1, 0 },
          { 0, 0, 0, 0, 0, 1, 0 },
          { 0, 0, 0, 0, 1, 0, 0 },
          { 1, 1, 1, 1, 0, 0, 0 }, };
        for(int i=0; i<height; i++)
            m_grid[i] = std::vector<int>( line[i], line[i]+width );
        return;
    }
    case 6 :
    {
        int line[height][width] =
        { { 0, 0, 0, 0, 1, 1, 0 },
          { 0, 0, 0, 1, 0, 0, 0 },
          { 0, 0, 1, 0, 0, 0, 0 },
          { 0, 1, 0, 0, 0, 0, 0 },
          { 1, 0, 0, 0, 1, 0, 0 },
          { 1, 0, 0, 1, 0, 1, 0 },
          { 0, 1, 1, 0, 0, 0, 1 },
          { 0, 1, 0, 0, 0, 0, 1 },
          { 0, 0, 1, 0, 0, 1, 0 },
          { 0, 0, 0, 1, 1, 0, 0 }, };
        for(int i=0; i<height; i++)
            m_grid[i] = std::vector<int>( line[i], line[i]+width );
        return;
    }
    case 7 :
    {
        int line[height][width] =
        { { 1, 1, 1, 1, 1, 1, 1 },
          { 0, 0, 0, 0, 0, 0, 1 },
          { 0, 0, 0, 0, 0, 1, 1 },
          { 0, 0, 0, 0, 1, 1, 0 },
          { 0, 0, 0, 0, 1, 0, 0 },
          { 0, 0, 0, 1, 1, 0, 0 },
          { 0, 0, 1, 1, 0, 0, 0 },
          { 0, 1, 1, 0, 0, 0, 0 },
          { 0, 1, 0, 0, 0, 0, 0 },
          { 1, 1, 0, 0, 0, 0, 0 }, };
        for(int i=0; i<height; i++)
            m_grid[i] = std::vector<int>( line[i], line[i]+width );
        return;
    }
    case 8 :
    {
        int line[height][width] =
        { { 0, 0, 1, 1, 1, 0, 0 },
          { 0, 1, 0, 0, 0, 1, 0 },
          { 1, 0, 0, 0, 0, 0, 1 },
          { 1, 0, 0, 0, 0, 0, 1 },
          { 0, 1, 1, 1, 1, 1, 0 },
          { 0, 1, 1, 1, 1, 1, 0 },
          { 1, 0, 0, 0, 0, 0, 1 },
          { 1, 0, 0, 0, 0, 0, 1 },
          { 0, 1, 0, 0, 0, 1, 0 },
          { 0, 0, 1, 1, 1, 0, 0 }, };
        for(int i=0; i<height; i++)
            m_grid[i] = std::vector<int>( line[i], line[i]+width );
        return;
    }
    case 9 :
    {
        int line[height][width] =
        { { 0, 0, 1, 1, 0, 0, 0 },
          { 0, 1, 0, 0, 1, 0, 0 },
          { 1, 0, 0, 0, 0, 1, 0 },
          { 1, 0, 0, 0, 0, 1, 1 },
          { 0, 1, 0, 0, 1, 0, 1 },
          { 0, 0, 1, 1, 0, 0, 1 },
          { 0, 0, 0, 0, 0, 0, 1 },
          { 0, 0, 0, 0, 0, 1, 0 },
          { 0, 0, 0, 0, 1, 0, 0 },
          { 0, 1, 1, 1, 0, 0, 0 }, };
        for(int i=0; i<height; i++)
            m_grid[i] = std::vector<int>( line[i], line[i]+width );
        return;
    }
    }
}

