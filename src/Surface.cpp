#include "Surface.h"

Surface::Surface(uint8** a_pData, int aW, int aH, uint8 aBytesPerPixel)
{
	_width = aW;
	_height = aH;
	_bytesPerPixel = aBytesPerPixel;

	_pPixelData = new uint8*[_height];
	for (int y=0; y<_height; ++y)
		_pPixelData[y] = new uint8[_width * _bytesPerPixel];		
	

	//memset(_pPixelData, 0, _width * _height * _bytesPerPixel);

	// copy
	if (a_pData)
	{
		for (int y=0; y<_height; ++y)
		{
			for (int x=0; x<_width; ++x)
			{
				_pPixelData[y][x] = (uint8)a_pData[y][x];
			}
		}
	}
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

uint8** Surface::GetPixels() const
{
	return _pPixelData;
}

GLuint Surface::CreateGLTexture()
{	
	GLuint glTexture;
	
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glEnable(GL_TEXTURE_2D);

	// get a handle to new texture
	glGenTextures(1, &glTexture);

	// Binds this texture handle so we can load the data into it
	glBindTexture(GL_TEXTURE_2D, glTexture);

	// Load texture data
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _pPixelData);

	// Texture properties
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return glTexture;
}

uint8 Surface::GetBytesPerPixel() const
{
	return _bytesPerPixel;
}

/**
 * Blit a surface into this one at position x,y.
 * Returns success / fail
 */
bool Surface::BlitSurface(const Surface* aSurface, int aOffsetX, int aOffsetY)
{
	if (_bytesPerPixel != aSurface->GetBytesPerPixel())
		throw "Can't combine surfaces of different colour depths";
	
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
	for (int y=0; y<aSurface->GetHeight(); ++y)
	{	
		for (int x=0; x<aSurface->GetWidth(); ++x)
		{
			_pPixelData[y + aOffsetY][x + aOffsetX] = aSurface->GetPixels()[y][x];
		}	
	}	

	return true;

}