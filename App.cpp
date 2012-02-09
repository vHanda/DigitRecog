#include "App.h"
#include <SDL/SDL_opengl.h>
#include <GL/gl.h>
#include "Engine/SDL/Font.h"
#include "Engine/SDL/SDL_SurfacePtr.h"

App::App()
{
}

App::~App()
{
}

void App::init_GL()
{
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
    glClearColor( 1.0, 1.0, 1.0, 1.0);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( 0, Engine::Width, Engine::Height, 0, -1, 1 );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    glEnable( GL_TEXTURE_2D );
    glEnable( GL_BLEND );
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void App::additional_init()
{
    m_State = state_loading;

    Font font("Ayu.ttf", 70);
    std::string s = "Training the Brain\nPlease Wait ...";
    SDL_SurfacePtr surf = font.render_Blended(s);
    m_LoadingImage.load( surf.get() );
}

void App::initGUI()
{
    //Title Image
    Font f("Ayu.ttf", 72);
    SDL_SurfacePtr surf= f.render_Blended("Digit Recognizer");
    m_TitleImage.load(surf.get());

    //Grid
    m_Grid.init();

    //Buttons
    Font font("Ayu.ttf", 50);
    m_Digits.reserve(10);

    for(unsigned int i=0; i<10; i++)
        m_Digits.push_back( new Digit_Button( this, &font, i) );

    m_pNoiseButton = std::auto_ptr<Noise_Button>( new Noise_Button(this, &font));
    m_pRecognizeButton = std::auto_ptr<Recognize_Button>( new Recognize_Button(this, &font) );
    m_pLabel = std::auto_ptr<Label>(new Label);

    //Set Positions
    int x = 40;
    int y = 80;
    for(int i=0; i<10; i++)
    {
        m_Digits[i].setPos(x,y);
        x += 40;
    }
    m_Grid.setPos(40, 130);
    m_pNoiseButton->setPos(270, 150);
    m_pRecognizeButton->setPos(270, 200);
    m_pLabel->setPos(270, 270);
}

void App::initNN()
{
    //Neural Network
    m_NN.addLayer( Grid::width * Grid::height ); //Input
    m_NN.addLayer(47); //Hidden
    m_NN.addLayer(47); //Hidden
    m_NN.addLayer(10); //Output

    //Train the NN
    m_NN.randomWeights();
    std::vector<float> input( Grid::width * Grid::height);
    std::vector<float> output(10);

    const float minError = 0.00001;
    float error = 1.0;
    while( error > minError )
    {
        error = 0;
        for(int i=0; i<10; i++)
        {
            m_Grid.setDigit(i);
            m_Grid.getInput(input);

            for(int j=0; j<10; j++)
                if( i == j )
                    output[j] = 1.0;
                else
                    output[j] = 0.0;

            float e = m_NN.train(input, output);
            error += e;
        }
        error /= 10;
        std::cout << error << std::endl;
    }
}
void App::render()
{
    glLoadIdentity();

    switch( m_State )
    {
    case state_normal :
        m_TitleImage.render(35, 5);
        m_Grid.render();
        for(int i=0; i<10; i++)
            m_Digits[i].render();
        m_pNoiseButton->render();
        m_pRecognizeButton->render();
        m_pLabel->render();
        break;

    case state_loading :
        m_LoadingImage.render(30, 130);
        break;
    }

}

void App::calc(float timeElapsed)
{
    switch( m_State )
    {
    case state_normal :
        m_Grid.update(timeElapsed);
        for(unsigned int i=0; i<m_Digits.size(); i++)
            m_Digits[i].update(timeElapsed);
        m_pNoiseButton->update(timeElapsed);
        m_pRecognizeButton->update(timeElapsed);
        break;

    case state_loading :
        static int first = true;
        if (first == true)
        {
            first = false;
            return;
        }
        initGUI();
        initNN();
        m_State = state_normal;
        break;
    }
}


void App::setDigit(int d)
{
    m_Grid.setDigit(d);
}
void App::addNoise()
{
    m_Grid.addNoise( 5 + (rand() % 10) );
}

struct Score {
    int num;
    float per;

    bool operator<(const Score & s) const
    { return per < s.per; }
};

void App::recognize()
{
    std::vector<float> input( Grid::width * Grid::height);
    std::vector<float> output(10);

    m_Grid.getInput(input);
    m_NN.run(input, output);

    std::vector<Score> sc(10);
    for(int i=0; i<10; i++)
    {
        Score s;
        s.num = i;
        s.per = output[i];
        sc[i] = s;
    }
    std::sort( sc.rbegin(), sc.rend() );

    std::string s("Analysis : \n");
    for(int i=0; i<3; i++)
    {
        s += "#";
        s += '0' + sc[i].num;
        s += " -- ";
        s += toString(sc[i].per*100);
        s += "%\n";
    }
    m_pLabel->set(s);
}
