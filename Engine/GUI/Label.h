#ifndef LABEL_H
#define LABEL_H

#include "../GL/glTex.h"
#include "../SDL/Font.h"
#include "../SDL/SDL_SurfacePtr.h"
#include <memory>

class Label
{
private :
    std::auto_ptr<glTex> m_pTex;
    Font m_Font;
    SDL_Rect m_Rect;
public:
    Label();
    virtual ~Label();

    void setPos(int x, int y) { m_Rect.x = x; m_Rect.y=y; }
    void set(const std::string & s);
    void render() const;
};

#endif // LABEL_H
