#include "ResourceManager.h"
#include <vector>


#include <iostream>
#include <fstream>
#include "../third_party/PicoPNG/picopng.h"

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
	//Surface* pMaster = new Surface(NULL, maxSize.x, maxSize.y);

	// order by size	
	/*
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
	*/
	// test code
	//pMaster->BlitSurface(sortedSurfaces[0], 0, 0);

	
	ImageByName::const_iterator it = _loadedImages.begin();
	Image* pTestImg = it->second;

	SurfaceByName::const_iterator it2 = _loadedSurfaces.begin();
	Surface* pTestSurface = it2->second;


	// flip because OpenGL has inverted y axis	
	pTestSurface->FlipY();

	pTestImg->_textureX = 0.0f;
	pTestImg->_textureY = 0.0f;
	pTestImg->_textureW = 1.0f;
	pTestImg->_textureH = 1.0f;
	pTestImg->_width = pTestSurface->GetWidth();//sortedSurfaces[0]->GetWidth();
	pTestImg->_height = pTestSurface->GetHeight();//sortedSurfaces[0]->GetHeight();

	pTestImg->_texture = pTestSurface->CreateGLTexture();//sortedSurfaces[0]->CreateGLTexture();

}


// from picoPNG...
void loadFile(std::vector<unsigned char>& buffer, const std::string& filename) //designed for loading files from hard disk in an std::vector
{
	std::ifstream file(filename.c_str(), std::ios::in|std::ios::binary|std::ios::ate);

	//get filesize
	std::streamsize size = 0;
	if(file.seekg(0, std::ios::end).good()) size = file.tellg();
	if(file.seekg(0, std::ios::beg).good()) size -= file.tellg();

	//read contents of the file into the vector
	if(size > 0)
	{
	buffer.resize((size_t)size);
	file.read((char*)(&buffer[0]), size);
	}
	else buffer.clear();
}

/* Read a PNG file. */
Surface* ResourceManager::PngToSurface(const char *aFile_name)  
{
	//load and decode
	std::vector<unsigned char> buffer, image;
	loadFile(buffer, aFile_name);
	unsigned long w, h;
	int error = decodePNG(image, w, h, buffer.empty() ? 0 : &buffer[0], (unsigned long)buffer.size());
	
	// image now contains 32 bit png... that was easier than libPNG :)

	if(error != 0)
		return NULL;
	
	return new Surface(&image[0], w, h, 4);
}

