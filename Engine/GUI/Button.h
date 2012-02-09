#ifndef BUTTON_H
#define BUTTON_H

#include <SDL/SDL.h>

class Button
{
private :
    enum state {
        state_normal = 0,
        state_clicked
    };
    state m_State;
    SDL_Rect m_Rect;
public:
    Button(const SDL_Rect & r);
    Button();
    virtual ~Button();

    void render();
    void update(float timeElapsed);

    virtual void renderNormal() = 0;
    virtual void renderClicked() = 0;
    virtual void onClick() = 0;

    void setRect(const SDL_Rect & r) { m_Rect = r; }
    SDL_Rect getRect() const { return m_Rect; }
};

#endif // BUTTON_H
