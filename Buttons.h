#ifndef BUTTONS_H
#define BUTTONS_H

#include "Engine/GUI/LabeledButton.h"

class App;

class Digit_Button : public LabeledButton
{
private :
    App * m_pApp;
    int m_iNum;
public :
    Digit_Button(App * app, Font * pFont, int num);
    virtual ~Digit_Button();
    void onClick();
};

class Noise_Button : public LabeledButton
{
private :
    App * m_pApp;
public :
    Noise_Button(App * app, Font * pFont);
    virtual ~Noise_Button();
    void onClick();
};

class Recognize_Button : public LabeledButton
{
private :
    App * m_pApp;
public :
    Recognize_Button(App * app, Font * pFont);
    virtual ~Recognize_Button();
    void onClick();
};

#endif // BUTTONS_H
