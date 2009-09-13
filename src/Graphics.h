#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "Types.h"
#include "Platform.h"
#include "Image.h"

class Graphics
{
public:
	Graphics();
	~Graphics();

	void DrawImage(const Image* a_pImg, float aX, float aY);

private :
	GLuint _boundTexture;
};


#endif

