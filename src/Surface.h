#ifndef SURFACE_H
#define SURFACE_H

#include "Globals.h"
#include "Platform.h"

class Surface
{

public:

	Surface();
	~Surface();

	void CreateSurface(uint16 width, uint16 height, void* pData);	
	GLuint CreateGLTexture();
	uint16 GetWidth();
	uint16 GetHeight();


private:

	uint8* pixelData;
	uint16 width;
	uint16 height;

};


#endif