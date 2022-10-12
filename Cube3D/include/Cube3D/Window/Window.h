#pragma once
#include <Cube3D/Math/ORect.h>



class Window
{
public:
	Window();

	// need a method to get window size for viewport size
	ORect getInnerSize();

	void makeCurrentContext();
	void present(bool vsync);

	void setFocus(bool focus);

	// events
	//virtual void onFocus();
	//virtual void onKillFocus();

	~Window();

	bool inFocus = true;

private:
	void* m_handle = nullptr;
	void* m_context = nullptr;
	
}; 

