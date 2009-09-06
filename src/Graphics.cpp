#include "Graphics.h"


GLuint boundTexture = 0;


void gfxDrawTexture(GLuint texture, float x, float y)
{
	if (boundTexture != texture)
	{
		glBindTexture(GL_TEXTURE_2D, texture);
		boundTexture = texture;
	}


	

	//GLfloat vertices = 
	//{
	//	x - (w/2),

	//}	


}