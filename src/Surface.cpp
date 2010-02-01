#include "Surface.h"

Surface::Surface(uint8* a_pData, int aW, int aH, int aBPP)
{	
	long numBytes = aW * aH * aBPP;
	_pPixelData = (uint8*)malloc(numBytes);	

	// flip because OpenGL has inverted y axis	
	for (long i=0; i<numBytes; i += aBPP)
		memcpy(&_pPixelData[i], &a_pData[numBytes-i-aBPP], aBPP);	

	_width = aW;
	_height = aH;
	_bytesPerPixel = aBPP;
}

void Surface::Destroy()
{
	delete this;
}

Surface::~Surface()
{
	delete[] _pPixelData;
}

int Surface::GetWidth() const
{
	return _width;
}

int Surface::GetHeight() const
{
	return _height;
}

uint8* Surface::GetPixels() const
{
	return _pPixelData;
}


int Surface::GetBytesPerPixel() const
{
	return _bytesPerPixel;
}


GLuint Surface::CreateGLTexture()
{	
	GLuint glTexture[1];
	
	glEnable(GL_TEXTURE_2D);

	// get a handle to new texture
	glGenTextures(1, &glTexture[0]);

	// Binds this texture handle so we can load the data into it
	glBindTexture(GL_TEXTURE_2D, glTexture[0]);

	// Load texture data
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _pPixelData);

	// Texture properties
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return glTexture[0];
}

/**
 * Blit a surface into this one at position x,y.
 * Returns success / fail
 */
bool Surface::BlitSurface(const Surface* aSurface, int aOffsetX, int aOffsetY)
{
	
	if (	aOffsetX < 0
		||	aOffsetY < 0
		||  aOffsetX > GetWidth()
		||  aOffsetY > GetHeight() )
	{
		throw "Trying to blit surface outside bounds";
	}

	if (	aOffsetX + aSurface->GetWidth() > GetWidth()
		||  aOffsetY + aSurface->GetHeight() > GetHeight() )
	{		
		// doesn't fit
		return false;
	}
	
	// copy pixels	
	/*
	for (int y=0; y<aSurface->GetHeight(); ++y)
	{		
		for (int x=0; x<aSurface->GetWidth(); ++x)
		{
			_pPixelData[y + aOffsetY][x + aOffsetX] = aSurface->GetPixels()[y][x];
		}	
	}
	*/

	return true;

}