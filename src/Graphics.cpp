#include "Graphics.h"


Graphics::Graphics()
{
	_boundTexture = 0;
	_aspectRatio = (SCREENWIDTH / SCREENHEIGHT);

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
    glBlendFunc(GL_ONE, GL_SRC_COLOR);

	glDisable(GL_DEPTH_TEST);	

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW); 	
}

void Graphics::DrawImage(const Image* a_pImg, float aX, float aY)
{
	GLuint aTextureName = a_pImg->_texture;
	if (_boundTexture != aTextureName)
	{
		glBindTexture(GL_TEXTURE_2D, aTextureName); 
		_boundTexture = aTextureName;	
	}

	float w = a_pImg->_width;
	float h = a_pImg->_height;
	static const float vertices[] =  
	{
		-0.5f * w,	 0.5f * h,  0,
		 0.5f * w,	 0.5f * h,  0,
		-0.5f * w,	-0.5f * h,  0,
		 0.5f * w,	-0.5f * h,  0		 
	};

	static const GLfloat texCoords[] =
	{
        0.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f
		/*a_pImg->_textureX, a_pImg->_textureH,
        a_pImg->_textureW, a_pImg->_textureH,
        a_pImg->_textureX, a_pImg->_textureY,
        a_pImg->_textureW, a_pImg->_textureY
		*/
    };

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);	

	glVertexPointer(3, GL_FLOAT, 0, &vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, &texCoords);	

	static float x =0;
	static float y = 0;
	y -= 0.5f;
	x += 0.5f;
	glTranslatef(x, y, 0.0f);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);			

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
