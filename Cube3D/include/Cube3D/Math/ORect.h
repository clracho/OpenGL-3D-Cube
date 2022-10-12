#pragma once
#include <Cube3D/Prerequisites.h>

//ORect handles the size of the viewport

class ORect
{
public:
	// constructor:
	ORect()
	{

	}
	ORect(i32 width, i32 height) :width(width), height(height) {

	}
	ORect(i32 left, i32 top, i32 width, i32 height) :left(left), top(top), width(width), height(height) {

	}
	ORect(const ORect& rect) :left(rect.left), top(rect.top), width(rect.width), height(rect.height) {

	}
	// destructor not used for any purpose







public:
	i32 width = 0, height = 0, left = 0, top = 0;
};
