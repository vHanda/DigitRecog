#ifndef _MOUSE_
#define _MOUSE_

class Mouse {
	static int xpos,ypos;
	static bool button[3];
public :
	Mouse();
	~Mouse() {}

	void onMouseMotion(int x, int y, int state, int xrel, int yrel);
	void onMouseDown(int x, int y, int _button);
	void onMouseUp(int x, int y, int _button);

	void getPos(int &x, int &y) const
	{ x = xpos; y = ypos; }
	bool isDown(int b) const
	{ return button[b]; }

	static Mouse * getInstance() { static Mouse m; return &m; }
};

#define gMOUSE Mouse::getInstance()

#endif
