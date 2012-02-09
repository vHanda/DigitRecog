#include "LabeledButton.h"
#include <iostream>

LabeledButton::LabeledButton()
{
}

LabeledButton::LabeledButton(const std::string & s, Font * f, int size)
{
    load(s,f,size);
}

LabeledButton::~LabeledButton()
{
}

void LabeledButton::renderNormal()
{
    m_pNormalImage->render(getRect().x, getRect().y);
}

void LabeledButton::renderClicked()
{
    m_pClickedImage->render(getRect().x, getRect().y);
}


void LabeledButton::load(const std::string & s, Font * f, int size)
{
    m_pNormalImage =  std::auto_ptr<glTex>(new glTex(f->render_Blended(s)));
    m_pClickedImage = std::auto_ptr<glTex>(new glTex(f->render_Blended(s)));
}

void LabeledButton::setPos(int x, int y)
{
    SDL_Rect r = getRect();
    r.x = x;
    r.y = y;
    r.w = m_pNormalImage->w();
    r.h = m_pNormalImage->h();

    setRect(r);
}
