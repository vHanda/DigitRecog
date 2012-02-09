#include "App.h"
int main( int argc, char** args )
{
	srand( SDL_GetTicks() );

	App engine;
	try
	{
        engine.set_caption("Initializing ... ");
        engine.init(500, 450);
        engine.set_caption("Digit Recognizer");
        engine.run();
	}
	catch(GameException & ge)
	{
	    handleException(ge);
        return 1;
	}
	return 0;
}

