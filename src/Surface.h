#ifndef SURFACE_H
#define SURFACE_H

#include "Types.h"
#include "Graphics.h"

class Surface
{
public:

	Surface(uint8** a_pData, int aW, int aH, uint8 aBytesPerPixel);

	int GetWidth() const;
	int GetHeight() const;
	uint8 GetBytesPerPixel() const;
	uint8** GetPixels() const;

	bool BlitSurface(const Surface* aSurface, int aOffsetX, int aOffsetY);


	void Destroy();

	GLuint CreateGLTexture();

protected:
	~Surface();	// force heap alloc

private:
	int		_width;
	int		_height;
	uint8	_bytesPerPixel;
	uint8	**_pPixelData;
};

#endif