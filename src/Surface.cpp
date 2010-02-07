#include "Surface.h"

Surface::Surface(uint8* a_pData, int aW, int aH, int aBPP)
{	
	long numBytes = aW * aH * aBPP;
	_pPixelData = (uint8*)malloc(numBytes);	

	if (a_pData)		
	{	
		memcpy(&_pPixelData[0], &a_pData[0], numBytes);	
	}
	else
	{
		// we can initialise a NULL surface too, just set to all one colour
		memset(_pPixelData, 0, numBytes);
	}

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

long Surface::GetArea() const
{
	return _width * _height;
}

uint8* Surface::GetPixels() const
{
	return _pPixelData;
}


int Surface::GetBytesPerPixel() const
{
	return _bytesPerPixel;
}

void Surface::FlipY()
{	
	long numBytes = _width * _height * _bytesPerPixel;

	uint8* flipped = new uint8[numBytes];

	for (long y=0; y<_height; ++y)
	{		
		memcpy(&flipped[y * _width * _bytesPerPixel], &_pPixelData[(_height - y - 1) * _width * _bytesPerPixel], _width * _bytesPerPixel);	
	}

	delete[] _pPixelData;
	_pPixelData = flipped;
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
	
	if (_bytesPerPixel != aSurface->GetBytesPerPixel())
		throw "Trying to blit surfaces of different colour depths";

	if (	aOffsetX + aSurface->GetWidth() > GetWidth()
		||  aOffsetY + aSurface->GetHeight() > GetHeight() )
	{		
		// doesn't fit
		return false;
	}
	
	// copy pixels	
	for (long y=0; y<aSurface->GetHeight(); ++y)
	{			
		long destOffset = aOffsetX + ((aOffsetY+y) * _width);
		long srcOffset = y * aSurface->GetWidth();

		destOffset *= _bytesPerPixel;
		srcOffset *= _bytesPerPixel;

		memcpy(&_pPixelData[destOffset], &aSurface->GetPixels()[srcOffset], aSurface->GetWidth() * _bytesPerPixel);		
	}



	return true;

}