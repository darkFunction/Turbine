#include "Graphics.h"


Graphics::Graphics()
{
	_boundTexture = 0;
	_aspectRatio = ((float)SCREENWIDTH / SCREENHEIGHT);

	InitOGLES_2D();
}

Graphics::~Graphics()
{

}


void Graphics::InitOGLES_3D()
{
	// TODO:

}

void Graphics::InitOGLES_2D()
{		
	glViewport(0, 0, (GLsizei)SCREENWIDTH, (GLsizei)SCREENHEIGHT);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// just make 1 unit == 1 pixel for ease, and make top left (0,0)
	glOrthof(0.0f, (GLfloat)SCREENWIDTH, (GLfloat)-SCREENHEIGHT, 0.0f, -1.0f, 1.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);				 
    glEnable(GL_TEXTURE_2D);							 
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDisable(GL_DEPTH_TEST);	

	glEnable(GL_CULL_FACE);
	//glFrontFace(GL_CW); 	
}

void Graphics::DrawImage(const Image* a_pImg, float aX, float aY)
{
	GLuint aTextureName = a_pImg->_texture;
	if (_boundTexture != aTextureName)
	{
		glBindTexture(GL_TEXTURE_2D, aTextureName); 
		_boundTexture = aTextureName;	
	}

	float hw = a_pImg->_width * 0.5f;
	float hh = a_pImg->_height * 0.5f;	
	float vertices[] =  
	{
		-hw,	 -hh,  0,
		 hw,	 -hh,  0,
		-hw,	  hh,  0,
		 hw,	  hh,  0		 
	};
		
	GLfloat texCoords[] =
	{ 
		a_pImg->_textureX,						a_pImg->_textureY - a_pImg->_textureH,
		a_pImg->_textureX + a_pImg->_textureW,  a_pImg->_textureY - a_pImg->_textureH,
		a_pImg->_textureX,						a_pImg->_textureY,
		a_pImg->_textureX + a_pImg->_textureW,	a_pImg->_textureY		
    };

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);	

	glVertexPointer(3, GL_FLOAT, 0, &vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, &texCoords);	

	glTranslatef(aX, -aY, 0.0f);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);			

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
