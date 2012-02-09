#include "Mouse.h"

int Mouse::xpos;
int Mouse::ypos;
bool Mouse::button[3];

Mouse::Mouse()
{
	xpos = 0;
	ypos = 0;
	button[0] = false;
	button[1] = false;
	button[2] = false;
}

void Mouse::onMouseMotion(int x, int y, int state, int xrel, int yrel)
{
	xpos = x;
	ypos = y;
	//button = state;
}
void Mouse::onMouseDown(int x, int y, int _button)
{
	xpos = x;
	ypos = y;
	button[ _button ] = true;
}

void Mouse::onMouseUp(int x, int y, int _button)
{
	xpos = x;
	ypos = y;
	button[ _button ] = false;
}
