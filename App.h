#ifndef APP_H
#define APP_H

#include "Engine/Engine.h"
#include "Grid.h"
#include "Buttons.h"
#include <boost/ptr_container/ptr_vector.hpp>
#include "Engine/GUI/Label.h"
#include "Engine/AI/NeuralNetwork/NeuralNetwork.h"

class App : public Engine
{
private :
    //Gui
    Grid m_Grid;
    boost::ptr_vector<Digit_Button> m_Digits;
    std::auto_ptr<Noise_Button> m_pNoiseButton;
    std::auto_ptr<Recognize_Button> m_pRecognizeButton;
    std::auto_ptr<Label> m_pLabel;
    glTex m_TitleImage;
    glTex m_LoadingImage;

    //Neural Network
    NeuralNetwork m_NN;

    void initGUI();
    void initNN();

    enum state {
        state_loading=0,
        state_normal=1
    };
    state m_State;
public:
    App();
    virtual ~App();

    void additional_init();
    void init_GL();
    void render();
    void calc(float timeElapsed);

    void setDigit(int d);
    void addNoise();
    void recognize();
};

template <typename T>
inline std::string toString(const T & t)
{
    std::stringstream ss;
    ss << t;
    return ss.str();
}

#endif // APP_H
