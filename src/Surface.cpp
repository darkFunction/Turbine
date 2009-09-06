#include "Surface.h"

Surface::Surface()
{

}

Surface::~Surface()
{
	delete pixelData;
}
// todo: add to surface etc
void Surface::CreateSurface(uint16 width, uint16 height, void *pData)
{
	this->width = width;
	this->height = height;

	pixelData = new uint8[width * height * 4];
	//pixelData = (uint8 *)pData;

	//memset(pixelData, 0, width * height * 4);

}

uint16 Surface::GetWidth()
{
	return width;
}

uint16 Surface::GetHeight()
{
	return height;
}

GLuint Surface::CreateGLTexture()
{
	// TODO: make sure pixelData width and height are both powers of 2
	//		 and not bigger than max width or height

	GLuint glTexture;
	
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glEnable(GL_TEXTURE_2D);

	// get a handle to new texture
	glGenTextures(1, &glTexture);

	// Binds this texture handle so we can load the data into it
	glBindTexture(GL_TEXTURE_2D, glTexture);

	/*
		glTexImage2D loads the texture data into the texture object.
		void glTexImage2D( GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height,
						   GLint border, GLenum format, GLenum type, const GLvoid *pixels );
		target must be GL_TEXTURE_2D.
		level specify the mipmap level we want to upload.
		internalformat and format must be the same. Here we use GL_RGBA for 4 component colors (r,g,b,a).
		  We could use GL_RGB, GL_ALPHA, GL_LUMINANCE, GL_LUMINANCE_ALPHA to use different color component combinations.
		width, height specify the size of the texture. Both of the dimensions must be power of 2.
		border must be 0.
		type specify the format of the data. We use GL_UNSIGNED_BYTE to describe a color component as an unsigned byte.
		  So a pixel is described by a 32bits integer.
		  We could also use GL_UNSIGNED_SHORT_5_6_5, GL_UNSIGNED_SHORT_4_4_4_4, and GL_UNSIGNED_SHORT_5_5_5_1
		  to specify the size of all 3 (or 4) color components. If we used any of these 3 constants,
		  a pixel would then be described by a 16bits integer.
	*/
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, MAX_TEXTURE_WIDTH, MAX_TEXTURE_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixelData);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixelData);

		/*
		glTexParameter is used to set the texture parameters
		void glTexParameter(GLenum target, GLenum pname, GLfloat param);
		target must be GL_TEXTURE_2D.
		pname is the parameter name we want to modify.
		  If pname is GL_TEXTURE_MIN_FILTER, param is used to set the way the texture is rendered when made smaller.
		  We can tell OpenGL to interpolate between the pixels in a mipmap level but also between different mipmap levels.
		  We are not using mipmap interpolation here because we didn't defined the mipmap levels of our texture.

		  If pname is GL_TEXTURE_MAG_FILTER, param is used to set the way the texture is rendered when made bigger.
		  Here we can only tell OpenGL to interpolate between the pixels of the first mipmap level.

		  if pname is GL_TEXTURE_WRAP_S or GL_TEXTURE_WRAP_T, then param sets the way a texture tiles in both directions.
		  The default if GL_REPEAT to wrap the texture (repeat it). We could also set it to GL_CLAMP or GL_CLAMP_TO_EDGE
		  to clamp the texture.

		  On OpenGL ES 1.1 and 2.0, if pname is GL_GENERATE_MIPMAP, param tells OpenGL to create mipmap levels automatically.
	*/

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// clear surface, it's now on texture
	delete[] pixelData;


	return glTexture;

}