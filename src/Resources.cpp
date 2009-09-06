#include "Resources.h"


Sprite* PngToSprite(char *file_name)
{
	Surface* surface = PngToSurface(file_name);
	
 	Sprite* sprite = new Sprite();
	sprite->texture = surface->CreateGLTexture();
	sprite->width = surface->GetWidth();
	sprite->height = surface->GetHeight();

	sprite->textureX = 0.0f;
	sprite->textureY = 0.0f;
	sprite->textureW = 1.0f;
	sprite->textureH = 1.0f;

	return sprite;
}

/* Read a PNG file. */
Surface* PngToSurface(char *file_name)  
{
	unsigned int sig_read = 8;
	FILE *fp;

	if (! (fp = fopen(file_name, "rb")) )
	  return NULL;

	// is png?
	png_bytep header = (png_bytep)malloc(sig_read);
	fread(header, 1, sig_read, fp);
	if ( png_sig_cmp(header, 0, sig_read) )
		return NULL;

	/* Create and initialize the png_struct with the desired error handler
	* functions.  If you want to use the default stderr and longjump method,
	* you can supply NULL for the last three parameters.  We also supply the
	* the compiler header file version, so that we know if the application
	* was compiled with a compatible version of the library.  REQUIRED
	*/
	png_structp png_ptr = png_create_read_struct
       (PNG_LIBPNG_VER_STRING, NULL,
        NULL, NULL);
    if (!png_ptr)
        return (ERROR);

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
    {
        png_destroy_read_struct(&png_ptr,
           (png_infopp)NULL, (png_infopp)NULL);
        return (ERROR);
    }

    png_infop end_info = png_create_info_struct(png_ptr);
    if (!end_info)
    {
        png_destroy_read_struct(&png_ptr, &info_ptr,
          (png_infopp)NULL);
        return (ERROR);
    }

	/* Set error handling if you are using the setjmp/longjmp method (this is
	* the normal method of doing things with libpng).  REQUIRED unless you
	* set up your own error handlers in the png_create_read_struct() earlier.
	*/

	if (setjmp(png_jmpbuf(png_ptr)))
	{
	  /* Free all of the memory associated with the png_ptr and info_ptr */
	  png_destroy_read_struct(&png_ptr, &info_ptr, png_infopp_NULL);
	  fclose(fp);
	  /* If we get here, we had a problem reading the file */
	  return NULL;// (ERROR);
	}

	/* Set up the input control if you are using standard C streams */
	png_init_io(png_ptr, fp);

	/* If we have already read some of the signature */
	png_set_sig_bytes(png_ptr, sig_read);

	/* Read png data into info structure */
	png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, png_voidp_NULL);

	/* At this point you have read the entire image */
	png_uint_32 height = png_get_image_height(png_ptr, info_ptr);
	png_uint_32 width = png_get_image_width(png_ptr, info_ptr);
	int bit_depth = png_get_bit_depth(png_ptr, info_ptr);
	int color_type = png_get_color_type(png_ptr, info_ptr);

	png_bytep* row_pointers = png_get_rows(png_ptr, info_ptr);	


	Surface* surface = new Surface();

	surface->CreateSurface(width, height, row_pointers);
	
	/* clean up after the read, and free any memory allocated - REQUIRED */
	png_destroy_read_struct(&png_ptr, &info_ptr, png_infopp_NULL);

	/* close the file */
	fclose(fp);

	/* that's it */
	
	return surface;
}
