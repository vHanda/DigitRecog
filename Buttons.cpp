#include "Buttons.h"
#include "App.h"
#include <sstream>

//Digit Button
Digit_Button::Digit_Button(App * app, Font * pFont, int num)
: m_pApp(app), m_iNum(num)
{
    std::stringstream ss;
    ss << num;
    load( ss.str(), pFont);
}

Digit_Button::~Digit_Button()
{}

void Digit_Button::onClick()
{
    m_pApp->setDigit(m_iNum);
}

//Noise Button
Noise_Button::Noise_Button(App * app, Font * pFont)
 : m_pApp(app)
{
    load("Noise", pFont);
}

Noise_Button::~Noise_Button()
{}

void Noise_Button::onClick()
{
    m_pApp->addNoise();
}

//Recognize Button
Recognize_Button::Recognize_Button(App * app, Font * pFont)
: m_pApp(app)
{
    load("Recognize", pFont);
}

Recognize_Button::~Recognize_Button()
{}

void Recognize_Button::onClick()
{
    m_pApp->recognize();
}
