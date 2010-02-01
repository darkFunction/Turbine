#ifndef IMAGE_H
#define IMAGE_H

//#include "Graphics.h"
#include <String>
#include "Types.h"
#include "Platform.h"

class Image
{

public:

	Image();
	~Image();

	GLuint _texture;

	float _textureX;
	float _textureY;
	float _textureW;
	float _textureH;

	std::string _pPathName;
	
	uint16 _width;
	uint16 _height;
};

#endif