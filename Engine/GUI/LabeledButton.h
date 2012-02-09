#ifndef LABELEDBUTTON_H
#define LABELEDBUTTON_H

#include "Button.h"
#include <string>
#include <memory>
#include "../GL/glTex.h"
#include "../SDL/Font.h"

class LabeledButton : public Button
{
private:
    std::auto_ptr<glTex> m_pNormalImage;
    std::auto_ptr<glTex> m_pClickedImage;
public:
    LabeledButton();
    LabeledButton(const std::string & s, Font * f, int size=-1);
    virtual ~LabeledButton();

    void load(const std::string & s, Font * f, int size=-1);

    virtual void renderNormal();
    virtual void renderClicked();
    virtual void onClick() = 0;

    void setPos(int x, int y);
};

#endif // LABELEDBUTTON_H
