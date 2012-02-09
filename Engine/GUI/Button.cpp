#include "Button.h"
#include "../Engine.h"
#include "../Math/Collision.h"
#include <iostream>

Button::Button(const SDL_Rect & r)
: m_Rect(r)
{
    m_State = state_normal;
}

Button::Button()
{
    m_Rect.x = m_Rect.y = m_Rect.w = m_Rect.h = 0;
    m_State = state_normal;
}

Button::~Button()
{
}

void Button::render()
{
    switch(m_State)
    {
    case state_normal :
        renderNormal();
        break;
    case state_clicked :
        renderClicked();
        break;
    }
}

void Button::update(float timeElapsed)
{
    Mouse * m = Mouse::getInstance();
    int x,y;
    m->getPos(x,y);

    if( ct_Rect_Point(m_Rect, Vec2D(x,y)) == false )
    {
        m_State = state_normal;
        return;
    }

    //State Changes
    if( m->isDown(1) )
    {
        m_State = state_clicked;
        return;
    }
    else
    {
        if( m_State == state_normal )
            return;

        if( m_State == state_clicked )
        {
            m_State = state_normal;
            onClick();
            return;
        }
    }

}
