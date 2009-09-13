#include "Graphics.h"


Graphics::Graphics()
{
	_boundTexture = 0;
}

Graphics::~Graphics()
{

}

void Graphics::DrawImage(const Image* a_pImg, float aX, float aY)
{
	GLuint aTextureName = a_pImg->_texture;

	if (_boundTexture != aTextureName)
	{
		glBindTexture(GL_TEXTURE_2D, aTextureName);
		_boundTexture = aTextureName;
	}


	//GLfloat vertices = 
	//{
	//	x - (w/2),

	//}	


}
