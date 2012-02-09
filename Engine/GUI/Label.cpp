#include "Label.h"

Label::Label()
{
    m_Font.load("Ayu.ttf", 30);
    set("Press - \nNoise or Recognize\n or a Digit");
}

Label::~Label()
{
    //dtor
}

void Label::set(const std::string & s)
{
    SDL_SurfacePtr surf = m_Font.render_Blended(s);
    m_pTex = std::auto_ptr<glTex>( new glTex(surf.get()) );
}

void Label::render() const
{
    m_pTex->render(m_Rect.x, m_Rect.y);
}
