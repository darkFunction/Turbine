#include "Graphics.h"


Graphics::Graphics()
{
	_boundTexture = 0;

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
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrthof(-1.0f,									// Left
			  1.0f,									// Right
			 -1.0f / (SCREENWIDTH / SCREENHEIGHT),	// Bottom
			  1.0f / (SCREENWIDTH / SCREENHEIGHT),	// Top
			  0.01f,								// Near
			  2.0f);								// Far

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glViewport(0, 0, (int)SCREENWIDTH, (int)SCREENHEIGHT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	
	
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_SRC_COLOR);//glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA); //glBlendFunc(GL_ONE, GL_ONE);//GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);		
}

void Graphics::DrawImage(const Image* a_pImg, float aX, float aY)
{
	GLuint aTextureName = a_pImg->_texture;
	if (_boundTexture != aTextureName)
	{
		glBindTexture(GL_TEXTURE_2D, aTextureName); 
		_boundTexture = aTextureName;	
	}

	static const float vertices[] =  
	{
		-0.25f,	0.25f,	0.0f,
		 0.25,	0.25f,	0.0f,
		-0.25,	-0.25f, 0.0f,
		 0.25f,	-0.25f, 0.0f		 
	};

	static const GLfloat texCoords[] =
	{
        0.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f
    };

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);	

	glVertexPointer(3, GL_FLOAT, 0, &vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, &texCoords);

	static float f = 0;
	f+=1;
	glRotatef(f, 0, 1.0f, 0);
	//glTranslatef(0.5f, 0.5f, -0.5f);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);		

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
