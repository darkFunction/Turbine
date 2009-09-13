#include "ResourceManager.h"
#include <vector>


using namespace std;

// takes ownership of image data
Image* ResourceManager::LoadImage(const string &aPath)
{
	Surface* pSurface = PngToSurface(aPath.c_str());
	_loadedSurfaces.insert(SurfaceNamePair(aPath, pSurface));
	
	Image* pImage = new Image();
	pImage->_pPathName = aPath;
	_loadedImages.insert(ImageNamePair(aPath, pImage));

	return pImage;
}

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{
	for (ImageByName::const_iterator it = _loadedImages.begin(); it != _loadedImages.end(); )
	{
		delete it->second;
		_loadedImages.erase(it);
	}

	for (SurfaceByName::const_iterator it = _loadedSurfaces.begin(); it != _loadedSurfaces.end();)
	{
		it->second->Destroy();
		_loadedSurfaces.erase(it);
	}
	
}

void ResourceManager::GenerateTextures(const Vector2i &maxSize)
{ 
	Surface* pMaster = new Surface(NULL, maxSize.x, maxSize.y, 4);


	// order by size
	vector<Surface*> sortedSurfaces;
	for (SurfaceByName::const_iterator it = _loadedSurfaces.begin(); it != _loadedSurfaces.end(); ++it)
	{
		sortedSurfaces.push_back(it->second);
	}

	for (uint16 i=0; i<sortedSurfaces.size()-1; ++i)
	{
		Surface *s = sortedSurfaces[i];
		int area1 = s->GetWidth() * s->GetHeight();
		s++;
		int area2 = s->GetWidth() * s->GetHeight();

		if (area1 < area2)
		{
			Surface* temp = sortedSurfaces[i];
			sortedSurfaces[i] = s;
			s = temp;
		}

	}

	// test code
	pMaster->BlitSurface(sortedSurfaces[0], 0, 0);

	// just test master surface as image for now
	ImageByName::const_iterator it = _loadedImages.begin();
	Image* pTestImg = it->second;

	return;

	
	pTestImg->_textureX = 0.0f;
	pTestImg->_textureY = 0.0f;
	pTestImg->_textureW = 1.0f;
	pTestImg->_textureH = 1.0f;
	pTestImg->_width = sortedSurfaces[0]->GetWidth();
	pTestImg->_height = sortedSurfaces[0]->GetHeight();

	pTestImg->_texture = sortedSurfaces[0]->CreateGLTexture();





}



/* Read a PNG file. */
Surface* ResourceManager::PngToSurface(const char *aFile_name)  
{
	unsigned int sig_read = 8;
	FILE *fp;

	if (! (fp = fopen(aFile_name, "rb")) )
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

	Surface* pSurface = new Surface(row_pointers, width, height, 4);
	
	/* clean up after the read, and free any memory allocated - REQUIRED */
	png_destroy_read_struct(&png_ptr, &info_ptr, png_infopp_NULL);

	/* close the file */
	fclose(fp);

	/* that's it */
	return pSurface;
}
