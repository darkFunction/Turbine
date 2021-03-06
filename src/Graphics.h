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

	void DrawImage(const Image* a_pImg, float aX, float aY, float aAngle);

private :
	GLuint _boundTexture;
	float _aspectRatio;

	void InitOGLES_2D();
	void InitOGLES_3D();
};


#endif

